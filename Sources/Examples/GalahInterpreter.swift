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

#if WITH_GALAH
  import Foundation
  import GalahInterpreter
  import PixarUSD

  func embedGalahInterpreter() throws
  {
    let interpreter = try Interpreter(
      """
      fn fibonacci(n: Int) -> Int 
      {
        if n == 1 || n == 2 
        {
          return 1
        } 
        else 
        {
          return fibonacci(n - 1) + fibonacci(n - 2)
        }
      }
      """
    )

    Msg.logger.info("successfully embedded the galah interpreter.")

    Msg.logger.info("running a test fibnonacci script in galah...")
    let result: Int = try interpreter.fibonacci(20)
    Msg.logger.info("got result: interpreter.fibonacci(20) = \(result)")
  }

  public enum GalahInterpreterExamples
  {
    static func run()
    {
      Msg.logger.info("running galah interpreter examples...")

      do
      {
        Msg.logger.info("embedding the galah interpreter...")
        try embedGalahInterpreter()
      }
      catch
      {
        Msg.logger.error("could not embed the galah interpreter: \(error.localizedDescription)")
      }

      Msg.logger.info("galah interpreter examples complete.")
    }
  }
#endif /* WITH_GALAH */
