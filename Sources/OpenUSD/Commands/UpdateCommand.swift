/* ----------------------------------------------------------------
 * :: :  M  E  T  A  V  E  R  S  E  :                            ::
 * ----------------------------------------------------------------
 * This software is Licensed under the terms of the Apache License,
 * version 2.0 (the "Apache License") with the following additional
 * modification; you may not use this file except within compliance
 * of the Apache License and the following modification made to it.
 * Section 6. Trademarks. is deleted and replaced with:
 *
 * Trademarks. This License does not grant permission to use any of
 * its trade names, trademarks, service marks, or the product names
 * of this Licensor or its affiliates, except as required to comply
 * with Section 4(c.) of this License, and to reproduce the content
 * of the NOTICE file.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND without even an
 * implied warranty of MERCHANTABILITY, or FITNESS FOR A PARTICULAR
 * PURPOSE. See the Apache License for more details.
 *
 * You should have received a copy for this software license of the
 * Apache License along with this program; or, if not, please write
 * to the Free Software Foundation Inc., with the following address
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 *         Copyright (C) 2024 Wabi Foundation. All Rights Reserved.
 * ----------------------------------------------------------------
 *  . x x x . o o o . x x x . : : : .    o  x  o    . : : : .
 * ---------------------------------------------------------------- */

import ArgumentParser
import Foundation

/**
 * The subcommand for changing the pixar
 * usd version for a specified package.
 */
struct UpdateCommand: AsyncCommand
{
  static var configuration = CommandConfiguration(
    commandName: "update",
    abstract: "Update the OpenUSD version in the current package."
  )

  /// Arguments in common with the run command.
  @OptionGroup
  var arguments: UpdateArguments

  init()
  {
    _arguments = OptionGroup()
  }

  init(arguments: OptionGroup<UpdateArguments>)
  {
    _arguments = arguments
  }

  static func validateArguments(_: UpdateArguments) -> Bool
  {
    // Validate parameters
    true
  }

  func wrappedRun() async throws
  {
    // get the package directory.
    var packageDirectory = URL(fileURLWithPath: ".")
    if let selectedPackage = arguments.packageDirectory
    {
      packageDirectory = selectedPackage
    }

    // get the package directory path.
    let pkgDir = packageDirectory.path

    // remove possibly existing openusd directory.
    if FileManager.default.fileExists(atPath: "\(pkgDir)/.build/OpenUSD", isDirectory: nil)
    {
      try FileManager.default.removeItem(atPath: "\(pkgDir)/.build/OpenUSD")
    }

    // Start timing
    let elapsed = try await Stopwatch.time
    {
      // 1. clone pixar official openusd repository.
      try Command.git.run(with: ["clone", "https://github.com/PixarAnimationStudios/OpenUSD.git", "\(pkgDir)/.build/OpenUSD"])

      // 2. update all usd source in this package, in parallel.
      async let bse = try Pxr.base.enumerate(packagePath: pkgDir)
      async let img = try Pxr.imaging.enumerate(packagePath: pkgDir)
      async let usd = try Pxr.usd.enumerate(packagePath: pkgDir)
      async let uim = try Pxr.usdImaging.enumerate(packagePath: pkgDir)

      // 3. wait for all usd source to be updated.
      let _ = try await [bse, img, usd, uim]
    }

    // Output the time elapsed and app bundle location
    log.info("done in \(elapsed.secondsString). usd source updated at '\(pkgDir)'.")
  }
}

/**
 * The Pixar packages to update.
 */
public enum Pxr: String, CaseIterable
{
  /** The pxr.base package. */
  case base
  /** The pxr.imaging package. */
  case imaging
  /** The pxr.usd package. */
  case usd
  /** The pxr.usdImaging imaging package. */
  case usdImaging

  /**
   * List the given package path, updating the source files for this
   * package from upstream pixar, and return a list of updated files.
   */
  public func enumerate(packagePath: String) async throws -> [URL]
  {
    // ------------- list all files in the directory -------------

    guard let list = FileManager.default.enumerator(atPath: "\(packagePath)/.build/OpenUSD/pxr/\(rawValue)")
    else { log.critical("Failed to list \(rawValue) directory."); return [] }

    // ---------------- process each file in list ----------------

    return try list.compactMap
    { pxrPath in

      // ----------- determine target and source paths -----------

      let suffix = path(from: pxrPath).split(separator: "pxr/\(rawValue)/").last ?? ""
      let source = URL(fileURLWithPath: ".build/OpenUSD/pxr/\(rawValue)/\(path(from: pxrPath))")
      var target = (suffix.split(separator: "/").first ?? "").capitalized

      ensureCasing(for: &target)

      // --------------------- skipped source --------------------

      if source.path.contains("testenv") ||
        source.path.lowercased().contains("cmakelists") ||
        source.path.lowercased().contains("pch.h")
      { return nil }

      // --------------- create target directories ---------------

      try createTargetDirectories(packagePath: packagePath, target: target)
      try createPythonDirectories(packagePath: packagePath, target: target)

      // ------ copy source files to dest (Sources/Target/*) -----

      if ["cpp", "cc", "c", "cxx"].contains(source.pathExtension)
      {
        if source.lastPathComponent.contains("wrap") || source.lastPathComponent.contains("module")
        {
          let dest = URL(fileURLWithPath: "\(packagePath)/Python/Py\(target)/\(source.lastPathComponent)")

          // move wrap and module files to Python/PyTarget/*
          try? FileManager.default.removeItem(at: dest)
          try FileManager.default.moveItem(at: source, to: dest)
          log.info("updating python module: \(dest.path)")
          updateSource(fileURL: dest)

          return dest
        }
        else
        {
          let dest = URL(fileURLWithPath: "\(packagePath)/Sources/\(target)/\(source.lastPathComponent)")

          // move source files to Sources/Target/*
          try? FileManager.default.removeItem(at: dest)
          try FileManager.default.moveItem(at: source, to: dest)
          log.info("updating source: \(dest.path)")
          updateSource(fileURL: dest)

          return dest
        }
      }

      // ----- copy headers (Sources/Target/include/Target/*) -----

      if ["h", "hpp", "hxx"].contains(source.pathExtension)
      {
        let dest = URL(fileURLWithPath: "\(packagePath)/Sources/\(target)/include/\(target)/\(source.lastPathComponent)")

        try? FileManager.default.removeItem(at: dest)
        try FileManager.default.moveItem(at: source, to: dest)
        log.info("updating header: \(dest.path)")
        updateSource(fileURL: dest)

        return dest
      }

      // ----------------------------------------------------------

      return nil
    }
  }

  private func updateSource(fileURL: URL)
  {
    do
    {
      let contents = try String(contentsOf: fileURL, encoding: .utf8)
      var pxrSrc = contents.replacingOccurrences(of: "pxr/pxr.h", with: "pxr/pxrns.h")

      /* apply patches to source files. */
      Patches.tbb.apply(to: &pxrSrc)

      /* 1. match includes such as:
       * #include "[pxr/base/tf]/token.h"
       * #include "[pxr/imaging/glf]/texture.h"
       * #include "[pxr/usd/sdf]/layer.h"
       * #include "[pxr/usdImaging/hd]/engine.h" */
      let includeMatch = /(?:\G(?!\A)\s*,\s*|\b(?:pxr\/base\/|pxr\/imaging\/|pxr\/usd\/|pxr\/usdImaging\/)+)(\w+)/
      while let match = try includeMatch.firstMatch(in: pxrSrc)
      {
        /* 2. replace include with capitalized version.
         * #include "[pxr/base/tf]/token.h"        -> #include "Tf/token.h"
         * #include "[pxr/imaging/glf]/texture.h"  -> #include "Glf/texture.h"
         * #include "[pxr/usd/sdf]/layer.h"        -> #include "Sdf/layer.h"
         * #include "[pxr/usdImaging/hd]/engine.h" -> #include "Hd/engine.h" */
        let include = pxrSrc[match.range]
        let newInclude = (include.split(separator: "/").last ?? "").capitalized
        pxrSrc = pxrSrc.replacingOccurrences(of: include, with: newInclude)
      }

      try pxrSrc.write(to: fileURL, atomically: true, encoding: .utf8)
    }
    catch
    {
      log.error("error: failed to update source '\(fileURL.path)'. \(error.localizedDescription).")
    }
  }

  /**
   * Create target directories for the given package.
   */
  private func createTargetDirectories(packagePath: String, target: String) throws
  {
    // create target directory, if it doesn't exist.
    let targetDir = URL(fileURLWithPath: "\(packagePath)/Sources/\(target)")
    if FileManager.default.fileExists(atPath: targetDir.path, isDirectory: nil) == false
    {
      try FileManager.default.createDirectory(at: targetDir, withIntermediateDirectories: true, attributes: nil)
    }

    // create target include directory, if it doesn't exist.
    let targetIncDir = URL(fileURLWithPath: "\(packagePath)/Sources/\(target)/include/\(target)")
    if FileManager.default.fileExists(atPath: targetIncDir.path, isDirectory: nil) == false
    {
      try FileManager.default.createDirectory(at: targetIncDir, withIntermediateDirectories: true, attributes: nil)
    }
  }

  /**
   * Create python target directories for the given package.
   */
  private func createPythonDirectories(packagePath: String, target: String) throws
  {
    // create python target directory, if it doesn't exist.
    let targetPyDir = URL(fileURLWithPath: "\(packagePath)/Python/Py\(target)")
    if FileManager.default.fileExists(atPath: targetPyDir.path, isDirectory: nil) == false
    {
      try FileManager.default.createDirectory(at: targetPyDir, withIntermediateDirectories: true, attributes: nil)
    }

    // create python target include directory, if it doesn't exist.
    let targetPyIncDir = URL(fileURLWithPath: "\(packagePath)/Python/Py\(target)/include/Py\(target)")
    if FileManager.default.fileExists(atPath: targetPyIncDir.path, isDirectory: nil) == false
    {
      try FileManager.default.createDirectory(at: targetPyIncDir, withIntermediateDirectories: true, attributes: nil)
    }
  }

  /**
   * Get the path from the given enumerator element.
   */
  private func path(from enumerated: NSEnumerator.Element) -> String
  {
    enumerated as? String ?? ""
  }

  /**
   * Ensure the casing is correct for the given target.
   */
  private func ensureCasing(for target: inout String)
  {
    for suffix in ["imaging", "app", "utils", "st", "si", "mtlx", "gp", "proc", "vol", "skel"]
    {
      if target.contains(suffix)
      {
        target = target.replacingOccurrences(of: suffix, with: suffix.capitalized)
      }
    }

    if target.contains("Geom")
    {
      target = target.replacingOccurrences(of: "util", with: "Util")
    }

    if target.contains("Hgi")
    {
      target = target.replacingOccurrences(of: "metal", with: "Metal")
      target = target.replacingOccurrences(of: "gl", with: "GL")
      target = target.replacingOccurrences(of: "vulkan", with: "Vulkan")
      target = target.replacingOccurrences(of: "interop", with: "Interop")
    }

    if target.contains("Hio")
    {
      target = target.replacingOccurrences(of: "open", with: "Open")
      target = target.replacingOccurrences(of: "vdb", with: "VDB")
    }

    if target.contains("Px")
    {
      target = target.replacingOccurrences(of: "osd", with: "Osd")
    }

    if target.contains("Usd")
    {
      target = target.replacingOccurrences(of: "geom", with: "Geom")
      target = target.replacingOccurrences(of: "lux", with: "Lux")
      target = target.replacingOccurrences(of: "ri", with: "Ri")
      target = target.replacingOccurrences(of: "pxr", with: "Pxr")
      target = target.replacingOccurrences(of: "gl", with: "GL")
      target = target.replacingOccurrences(of: "render", with: "Render")
      target = target.replacingOccurrences(of: "hydra", with: "Hydra")
      target = target.replacingOccurrences(of: "viewq", with: "ViewQ")
    }

    if target.contains("Hd")
    {
      target = target.replacingOccurrences(of: "ar", with: "Ar")
    }
  }

  private enum Patches
  {
    case tbb

    public func apply(to source: inout String)
    {
      switch self
      {
        case .tbb: applyTBBPatch(to: &source)
      }
    }

    private func applyTBBPatch(to source: inout String)
    {
      source = source.replacingOccurrences(of: "<tbb/", with: "<OneTBB/tbb/")
      source = source.replacingOccurrences(of: "#include <OneTBB/tbb/task_scheduler_init.h>", with: "#if WITH_TBB_LEGACY\n#include <tbb/task_scheduler_init.h>\n#endif /* WITH_TBB_LEGACY */")

      let dispatcher = """
        PXR_NAMESPACE_OPEN_SCOPE

        #if !WITH_TBB_LEGACY
        class WorkDispatcher {
        public:
          /// Construct a new dispatcher.
          WORK_API WorkDispatcher();

          /// Wait() for any pending tasks to complete, then destroy the dispatcher.
          WORK_API ~WorkDispatcher();

          WorkDispatcher(WorkDispatcher const &) = delete;
          WorkDispatcher &operator=(WorkDispatcher const &) = delete;

        #ifdef doxygen

          /// Add work for the dispatcher to run.
          ///
          /// Before a call to Wait() is made it is safe for any client to invoke
          /// Run().  Once Wait() is invoked, it is \\b only safe to invoke Run() from
          /// within the execution of tasks already added via Run().
          ///
          /// This function does not block, in general.  It may block if concurrency
          /// is limited to 1.  The added work may be not yet started, may be started
          /// but not completed, or may be completed upon return.  No guarantee is
          /// made.
          template <class Callable, class A1, class A2, ... class AN>
          void Run(Callable &&c, A1 &&a1, A2 &&a2, ... AN &&aN);

        #else // doxygen

          template <class Callable> inline void Run(Callable &&c) {
            _tg.run(_InvokerTask<typename std::remove_reference<Callable>::type>(
                std::forward<Callable>(c), &_errors));
          }

          template <class Callable, class A0, class... Args>
          inline void Run(Callable &&c, A0 &&a0, Args &&...args) {
            Run(std::bind(std::forward<Callable>(c), std::forward<A0>(a0),
                          std::forward<Args>(args)...));
          }

        #endif // doxygen

          /// Block until the work started by Run() completes.
          WORK_API void Wait();

          /// Cancel remaining work and return immediately.
          ///
          /// Calling this function affects task that are being run directly
          /// by this dispatcher. If any of these tasks are using their own
          /// dispatchers to run tasks, these dispatchers will not be affected
          /// and these tasks will run to completion, unless they are also
          /// explicitly cancelled.
          ///
          /// This call does not block.  Call Wait() after Cancel() to wait for
          /// pending tasks to complete.
          WORK_API void Cancel();

        private:
          typedef tbb::concurrent_vector<TfErrorTransport> _ErrorTransports;

          // Function invoker helper that wraps the invocation with an ErrorMark so we
          // can transmit errors that occur back to the thread that Wait() s for tasks
          // to complete.
          template <class Fn> struct _InvokerTask {
            explicit _InvokerTask(Fn &&fn, _ErrorTransports *err)
                : _fn(std::move(fn)), _errors(err) {}

            explicit _InvokerTask(Fn const &fn, _ErrorTransports *err)
                : _fn(fn), _errors(err) {}

            void operator()() const {
              TfErrorMark m;
              _fn();
              if (!m.IsClean())
                WorkDispatcher::_TransportErrors(m, _errors);
            }

          private:
            Fn _fn;
            _ErrorTransports *_errors;
          };

          // Helper function that removes errors from \\p m and stores them in a new
          // entry in \\p errors.
          WORK_API static void _TransportErrors(const TfErrorMark &m,
                                                _ErrorTransports *errors);

          // Task group.
          tbb::task_group _tg;

          // The error transports we use to transmit errors in other threads back to
          // this thread.
          _ErrorTransports _errors;

          // Concurrent calls to Wait() have to serialize certain cleanup operations.
          std::atomic_flag _waitCleanupFlag;
        };
        #else /* WITH_TBB_LEGACY */

        /// \\class WorkDispatcher
        """

      source = source.replacingOccurrences(of: "PXR_NAMESPACE_OPEN_SCOPE\n\n/// \\class WorkDispatcher", with: dispatcher)
      source = source.replacingOccurrences(of: "};\n\n///////////////////////////////////////////////////////////////////////////////\n\nPXR_NAMESPACE_CLOSE_SCOPE", with: "};\n#endif /* !WITH_TBB_LEGACY */\n///////////////////////////////////////////////////////////////////////////////\n\nPXR_NAMESPACE_CLOSE_SCOPE")
    }
  }
}
