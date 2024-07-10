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

import Foundation
import PixarUSD

func stageCacheBind()
{
  /* Create new stage for this example. */

  let newStage: UsdStageRefPtr = Usd.Stage.createNew("\(documentsDirPath())/UsdStageCacheExample", ext: .usd)
  newStage.save()

  Msg.logger.info("created a new stage.")

  /* Create the cache and bind the cache context. */

  var stageCache = UsdStageCache()
  UsdStageCacheContext.bind(cache: &stageCache)

  Msg.logger.info("created a new usd stage cache, and bound it to a cache context.")

  Msg.logger.info("inserting stage into usd stage cache...")
  let stage = Usd.Stage.open("\(documentsDirPath())/UsdStageCacheExample", ext: .usd)
  Msg.logger.info("checking if usd stage cache contains stage: \(stageCache.contains(stage))")

  Msg.logger.info("attempting to retrieve stage from the cache.")
  let stage2 = Usd.Stage.open("\(documentsDirPath())/UsdStageCacheExample", ext: .usd)

  let id1 = stageCache.GetId(stage).ToLongInt()
  let id2 = stageCache.GetId(stage2).ToLongInt()
  Msg.logger.info("stage successfully retrieved from the cache: \(id1 == id2)")
}

public enum StageCacheExamples
{
  static func run()
  {
    Msg.logger.info("running scene cache examples...")

    stageCacheBind()

    Msg.logger.info("scene cache examples complete.")
  }
}
