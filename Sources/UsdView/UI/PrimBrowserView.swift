/* ----------------------------------------------------------------
 * :: :  O  P  E  N  U  S  D  :                                  ::
 * ----------------------------------------------------------------
 * Licensed under the terms set forth in the LICENSE.txt file, this
 * file is available at https://openusd.org/license.
 *
 *                                        Copyright (C) 2016 Pixar.
 *         Copyright (C) 2024 Wabi Foundation. All Rights Reserved.
 * ----------------------------------------------------------------
 *  . x x x . o o o . x x x . : : : .    o  x  o    . : : : .
 * ---------------------------------------------------------------- */

import Foundation
import PixarUSD
import SwiftCrossUI


// MARK: - Prim Entry

/// A single row in the prim browser, derived from a traversed USD prim.
public struct PrimEntry: Identifiable, Hashable
{
  public var id: String { path }

  /// Full USD path, e.g. "/World/DefaultDomeLight".
  public let path: String
  /// Last component only, e.g. "DefaultDomeLight".
  public let name: String
  /// Schema type name, e.g. "DomeLight", "Sphere". Empty prims show "-".
  public let typeName: String
  /// Hierarchy nesting depth: root children = 0, their children = 1, …
  public let depth: Int
  /// Whether the prim has any children in the traversal list.
  public let hasChildren: Bool
  /// Whether the prim is visible or not.
  public let isVisible: Bool

  /// Traverse `stage` once and produce a flat, depth-ordered list of entries.
  public static func from(stage: UsdStage) -> [PrimEntry]
  {
    let prims = Array(stage.traverse())

    // Which paths have at least one child?
    var childSet: Set<String> = []
    for prim in prims
    {
      let p = prim.path.string
      if let lastSlash = p.lastIndex(of: "/")
      {
        let parent = String(p[p.startIndex ..< lastSlash])
        if !parent.isEmpty { childSet.insert(parent) }
      }
    }

    return prims.map
    { prim in
      let p = prim.path.string
      // depth = number of "/" separators minus the leading root slash
      let depth = max(0, p.filter { $0 == "/" }.count - 1)
      return PrimEntry(
        path: p,
        name: prim.name.string,
        typeName: prim.typeName.isEmpty ? "-" : prim.typeName.string,
        depth: depth,
        hasChildren: childSet.contains(p),
        isVisible: prim.isActive()
      )
    }
  }
}


// MARK: - Prim Browser Panel

/// Left-hand pane of the UsdView split layout.
/// Shows a scrollable table of prims with "Prim Name / Type / Vis" columns.
public struct PrimBrowserView: View
{
  public let prims: [PrimEntry]
  @Binding public var selectedPath: String?

  /// Paths whose children are currently hidden.
  @State private var collapsedPaths: Set<String> = []

  private let typeColWidth: CGFloat = 84
  private let visColWidth:  CGFloat = 32

  /// `prims`, minus any whose nearest collapsed ancestor hides them.
  /// The collapsed prim itself always stays visible so it can be re-expanded.
  private var visiblePrims: [PrimEntry]
  {
    guard !collapsedPaths.isEmpty else { return prims }

    return prims.filter
    { entry in
      for collapsed in collapsedPaths
      {
        if entry.path != collapsed, entry.path.hasPrefix(collapsed + "/")
        {
          return false
        }
      }
      return true
    }
  }

  private struct VisibleRow: Identifiable, Hashable
  {
    let entry: PrimEntry
    let isAlternate: Bool
    var id: String { entry.id }
  }

  private var visibleRows: [VisibleRow]
  {
    visiblePrims.enumerated().map { offset, entry in
      VisibleRow(entry: entry, isAlternate: offset % 2 == 1)
    }
  }

  public var body: some View
  {
    VStack(spacing: 0)
    {
      PrimBrowserHeader(
        typeColWidth: typeColWidth,
        visColWidth:  visColWidth
      )

      Divider()

      ScrollView {
        VStack(spacing: 0) {
          ForEach(visibleRows) { row in
            VStack(spacing: 0) {
              PrimBrowserRow(
                entry: row.entry,
                isSelected: selectedPath == row.entry.path,
                isCollapsed: collapsedPaths.contains(row.entry.path),
                isAlternate: row.isAlternate,
                typeColWidth: typeColWidth,
                visColWidth:  visColWidth,
                onToggleDisclosure: { toggleCollapsed(row.entry.path) },
                onSelect: { selectedPath = row.entry.path }
              )

              Divider()
            }
          }
        }
      }
    }
  }

  private func toggleCollapsed(_ path: String)
  {
    if collapsedPaths.contains(path)
    {
      collapsedPaths.remove(path)
    }
    else
    {
      collapsedPaths.insert(path)
    }
  }
}


// MARK: - Header Row

struct PrimBrowserHeader: View
{
  let typeColWidth: CGFloat
  let visColWidth:  CGFloat

  private let nameLeadingInset: CGFloat = 43

  var body: some View
  {
    HStack(spacing: 0)
    {
      Text("PRIM NAME")
        .frame(maxWidth: .infinity, alignment: .leading)
        .padding(.leading, Int(nameLeadingInset))

      Text("TYPE")
        .frame(width: typeColWidth, alignment: .leading)

      Text("VIS")
        .frame(width: visColWidth, alignment: .center)
        .padding(.trailing, 6)
    }
    .font(.system(size: 10, weight: .bold))
    .foregroundColor(Color(white: 0.55))
    .frame(height: 28)
    .background(Color(white: 0.07))
    .overlay(alignment: .bottom) {
      Rectangle()
        .fill(Color.purple.opacity(0.35))
        .frame(height: 1)
    }
  }
}


// MARK: - Prim Row

struct PrimBrowserRow: View
{
  let entry:        PrimEntry
  let isSelected:   Bool
  let isCollapsed:  Bool
  let isAlternate:  Bool
  let typeColWidth: CGFloat
  let visColWidth:  CGFloat
  let onToggleDisclosure: () -> Void
  let onSelect: () -> Void

  private let rowHeight:   CGFloat = 24
  private let indentStep:  CGFloat = 14
  private let accentWidth: CGFloat = 3

  @State private var isHovered: Bool = false

  private var rowBackground: Color
  {
    if isSelected  { return Color.purple.opacity(0.28) }
    if isHovered   { return Color(white: 1.0, opacity: 0.06) }
    if isAlternate { return Color(white: 1.0, opacity: 0.028) }
    return Color.clear
  }

  var body: some View
  {
    let glyph = PrimBrowserRow.typeGlyph(for: entry.typeName)

    HStack(spacing: 0)
    {
      Spacer()
        .frame(width: CGFloat(entry.depth) * indentStep + CGFloat(6))

      Text(entry.hasChildren ? (isCollapsed ? "▸" : "▾") : "")
        .font(.system(size: 9, weight: .bold))
        .frame(width: 12, height: rowHeight, alignment: .center)
        .foregroundColor(entry.hasChildren ? Color.purple.opacity(0.85) : Color.clear)
        .onTapGesture
        {
          if entry.hasChildren { onToggleDisclosure() }
        }

      Spacer().frame(width: 5)

      Text(glyph.symbol)
        .font(.system(size: 10, weight: .semibold))
        .foregroundColor(glyph.tint.opacity(isSelected ? 1.0 : 0.8))
        .frame(width: 16, height: rowHeight, alignment: .center)

      Spacer().frame(width: 4)

      HStack(spacing: 0)
      {
        Text(entry.name)
          .font(.system(size: 12, weight: .bold))
          .foregroundColor(isSelected ? Color.white : Color(white: 0.85))
          .lineLimit(1)
          .frame(maxWidth: .infinity, alignment: .leading)

        Text(entry.typeName)
          .font(.system(size: 11))
          .foregroundColor(glyph.tint.opacity(0.65))
          .lineLimit(1)
          .frame(width: typeColWidth, alignment: .leading)

        Text(entry.isVisible ? "●": "○")
          .font(.system(size: 10))
          .foregroundColor(
            entry.isVisible
              ? Color(red: 0.55, green: 0.85, blue: 0.62)
              : Color(white: 0.35)
          )
          .frame(width: visColWidth, alignment: .center)
          .padding(.trailing, 6)
      }
      .onTapGesture { onSelect() }
    }
    .frame(height: rowHeight)
    .background(
      Rectangle()
        .fill(rowBackground)
        .onHover { hovering in isHovered = hovering }
    )
    .overlay(alignment: .leading) {
      Rectangle()
        .fill(isSelected ? Color.purple : Color.clear)
        .frame(width: accentWidth)
    }
  }

  /// Maps a USD schema type name to a small glyph & tint so prim categories
  /// (geometry / lights / shading / grouping) are distinguishable at a glance.
  private static func typeGlyph(for typeName: String) -> (symbol: String, tint: Color)
  {
    switch typeName
    {
      case "Xform":
        return ("📦", Color(red: 0.58, green: 0.68, blue: 0.85))

      case "Sphere":
        return ("🔵", Color(red: 0.46, green: 0.80, blue: 0.88))

      case "Cube":
        return ("🧊", Color(red: 0.46, green: 0.80, blue: 0.88))

      case "Mesh", "Cylinder", "Cone", "Capsule", "Plane", "Points":
        return ("🔺", Color(red: 0.46, green: 0.80, blue: 0.88))

      case "Material":
        return ("🎨", Color(red: 0.95, green: 0.66, blue: 0.36))

      case "Shader", "NodeGraph":
        return ("✨", Color(red: 0.96, green: 0.82, blue: 0.42))

      case "DomeLight", "DistantLight", "SphereLight", "RectLight",
           "DiskLight", "CylinderLight", "GeometryLight":
        return ("💡", Color(red: 0.99, green: 0.86, blue: 0.48))

      case "Scope":
        return ("🗂", Color(white: 0.6))

      case "-":
        return ("◦", Color(white: 0.4))

      default:
        return ("◦", Color(white: 0.55))
    }
  }
}
