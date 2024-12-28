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

import Foundation
import PixarUSD

public enum ShadeColor: String, CaseIterable
{
  case red
  case orange
  case yellow
  case green
  case blue
  case purple
  case white
  case black

  public var vec3f: GfVec3f
  {
    switch self
    {
      case .red: GfVec3f(0.992, 0.207, 0.061)
      case .orange: GfVec3f(0.922, 0.501, 0.0)
      case .yellow: GfVec3f(0.950, 0.800, 0.0)
      case .green: GfVec3f(0.0, 0.766, 0.014)
      case .blue: GfVec3f(0.132, 0.218, 0.932)
      case .purple: GfVec3f(0.531, 0.122, 0.922)
      case .white: GfVec3f(0.8, 0.8, 0.8)
      case .black: GfVec3f(0.2, 0.2, 0.2)
    }
  }
}

/**
 * Create a material with a surface shader.
 *
 * - Parameter stage: The stage to create the material on.
 * - Parameter color: The diffuse color to set on the shader.
 * - Returns: The newly created material.
 */
public func matDef(_ stage: UsdStageRefPtr, color: ShadeColor = ShadeColor.white) -> UsdShade.Material
{
  let matName = "\(color.rawValue.capitalized)Material"

  let material = UsdShade.Material.define(stage, path: "/Materials/\(matName)")

  var pbrShader = UsdShade.Shader.define(stage, path: "/Materials/\(matName)/PBRShader")
  pbrShader.createIdAttr(.usdPreviewSurface)
  pbrShader.createInput(for: .diffuseColor, type: .color3f).set(color.vec3f)
  pbrShader.createInput(for: .roughness, type: .float).set(Float(0.4))
  pbrShader.createInput(for: .metallic, type: .float).set(Float(0.0))
  material.createSurfaceOutput().connectTo(source: pbrShader.connectableAPI(), at: .surface)

  return material
}

#if canImport(SwiftUI)
  import SwiftUI

  extension UsdView
  {
    func startColorAnimation()
    {
      Timer.scheduledTimer(withTimeInterval: 0.03, repeats: true)
      { _ in
        hue += 0.01
        if hue > 1.0 { hue = 0.0 }
        rgba = hueToRGBA(hue: hue)
      }
    }

    func hueToRGBA(hue: Double) -> (Double, Double, Double, Double)
    {
      let color = Color(hue: hue, saturation: 1.0, brightness: 1.0)
      var red: Double = 0, green: Double = 0, blue: Double = 0, alpha: Double = 0
      if let components = color.cgColor?.components, components.count >= 3
      {
        red = components[0]
        green = components[1]
        blue = components[2]
        alpha = Double(color.cgColor?.alpha ?? 1.0)
      }
      return (red, green, blue, alpha)
    }
  }
#endif // canImport(SwiftUI)
