import Foundation
import PixarUSD

extension UsdView
{
  /**
   * Declaratively author Universal Scene Description,
   * in a similiar fashion to how one may interface with
   * APIs such as SwiftUI, and save the stage to disk. */
  func declareScene()
  {
    USDStage("\(documentsDirPath())/DeclarativePixarUSD", ext: .usda)
    {
      USDPrim("DeclarativeScene")
      {
        USDPrim("Sun", type: .distantLight)
        {
          USDPrim("Hello", type: .xform)
          {
            USDPrim("World", type: .sphere)
            USDPrim("Box", type: .cube)
          }

          USDPrim("RandomCone", type: .cone)
        }
      }
    }
    .set(doc: "SwiftUSD v\(Pixar.version) | Declarative API")
    .save()
  }
}
