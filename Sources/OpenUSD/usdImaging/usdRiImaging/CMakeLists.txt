set(PXR_PREFIX pxr/usdImaging)
set(PXR_PACKAGE usdRiImaging)

pxr_library(usdRiImaging
    LIBRARIES
        gf
        tf
        plug
        trace
        vt
        work
        hd
        pxOsd
        sdf
        usd
        usdGeom
        usdLux
        usdShade
        usdImaging
        usdVol
        ar
        ${TBB_tbb_LIBRARY}

    INCLUDE_DIRS
        ${TBB_INCLUDE_DIRS}

    PUBLIC_CLASSES
        pxrBarnLightFilterAdapter
        pxrDisplayFilterAdapter
        pxrIntegratorAdapter
        pxrIntMultLightFilterAdapter
        pxrRodLightFilterAdapter
        pxrSampleFilterAdapter
        tokens

    PRIVATE_CLASSES
        pxrRenderTerminalHelper

    PRIVATE_HEADERS
        dataSourcePxrRenderTerminalPrims.h

    PUBLIC_HEADERS
        api.h
        version.h

    RESOURCE_FILES
        plugInfo.json
)

