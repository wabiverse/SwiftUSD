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

#if LOW_LEVEL_LINKAGE
  /**
   * todo, figure out low level linkage strategy in swift.
   */
  func defineEnvSetting(_ name: ArHttpEnvSetting, value: String, description: String)
  {
    var val: Pixar.TfEnvSetting.AtomicValue = .init()
    var envVar: Pixar.TfEnvSetting<std.string> = .init(&val, value, name.rawValue, description)

    func _Tf_RegistryFunctionNAME(_: Pixar.Tf_EnvSettingRegistry, _: OpaquePointer)
    {
      Pixar.TfGetEnvSetting(envVar)
    }

    let _tfRegistryInit = Pixar.Arch_PerLibInit<Pixar.Tf_RegistryStaticInit>()
  }

  func _Tf_RegistryAddNAME(_: Pixar.Tf_EnvSettingRegistry)
  {
    Tf_RegistryInit.Add(
      "arHttp",
      _Tf_RegistryFunctionNAME as RegistrationFunctionType<Pixar.Tf_EnvSettingRegistry, OpaquePointer>,
      "Tf_EnvSettingRegistry"
    )
  }

  public enum ArchInitializer
  {
    @used @section("__DATA,pxrctor") private static let arch_ctor_NAME = Pixar.Arch_ConstructorEntry(
      function: _Tf_RegistryAddNAME,
      version: 0,
      priority: TF_REGISTRY_PRIORITY
    )
  }
#endif /* LOW_LEVEL_LINKAGE */
