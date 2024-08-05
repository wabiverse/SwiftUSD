/* ----------------------------------------------------------------
 * :: :  M  E  T  A  V  E  R  S  E  :                            ::
 * ----------------------------------------------------------------
 * Licensed under the terms set forth in the LICENSE.txt file, this
 * file is available at https://openusd.org/license.
 *
 *                                        Copyright (C) 2016 Pixar.
 *         Copyright (C) 2024 Wabi Foundation. All Rights Reserved.
 * ----------------------------------------------------------------
 *  . x x x . o o o . x x x . : : : .    o  x  o    . : : : .
 * ---------------------------------------------------------------- */

import ArgumentParser
import Foundation

/// An extension to the `AsyncParsableCommand` API with custom error handling.
protocol AsyncCommand: AsyncParsableCommand
{
  /// Implement this instead of `validate()` to get custom Swift Bundler error handling.
  func wrappedValidate() throws

  /// Implement this instead of `run()` to get custom Swift Bundler error handling.
  func wrappedRun() async throws
}

extension AsyncCommand
{
  func wrappedValidate() {}
}

extension AsyncCommand
{
  func run() async
  {
    do
    {
      try await wrappedRun()
    }
    catch
    {
      log.error("\(error.localizedDescription)")
      log.debug("Error details: \(error)")
      if log.logLevel > .debug
      {
        print("")
        log.info("Use -v to get more error details")
      }
      Foundation.exit(1)
    }
  }

  func validate()
  {
    do
    {
      try wrappedValidate()
    }
    catch
    {
      if let error = error as? ValidationError
      {
        log.error("\(error)")
      }
      else
      {
        log.error("\(error.localizedDescription)")
      }
      Foundation.exit(1)
    }
  }
}
