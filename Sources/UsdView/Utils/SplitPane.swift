/* ----------------------------------------------------------------
 * :: :  O  P  E  N  U  S  D  :                                  ::
 * ----------------------------------------------------------------
 * Licensed under the terms set forth in the LICENSE.txt file, this
 * file is available at https://openusd.org/license.
 *
 *                   Copyright (C) 2016 Pixar. All Rights Reserved.
 *                              Copyright (C) 2024 Wabi Foundation.
 * ----------------------------------------------------------------
 *  . x x x . o o o . x x x . : : : .    o  x  o    . : : : .
 * ---------------------------------------------------------------- */

import SwiftCrossUI

/// Lays out its content side-by-side on screens with width to spare,
/// or stacked top-to-bottom on compact layouts (where portrait
/// layouts favor a vertical split).
struct SplitPane<Content: View>: View
{
  var spacing: Int
  @ViewBuilder var content: () -> Content

  var body: some View
  {
    if isCompactLayout
    {
      VStack(spacing: spacing) {
        content()
      }
    }
    else
    {
      HStack(spacing: spacing) {
        content()
      }
    }
  }
}
