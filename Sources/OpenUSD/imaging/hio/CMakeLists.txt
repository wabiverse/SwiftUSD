set(PXR_PREFIX pxr/imaging)
set(PXR_PACKAGE hio)

pxr_library(hio
    LIBRARIES
        arch
        js
        plug
        tf
        vt
        trace
        ar
        hf

    INCLUDE_DIRS
        ${Boost_INCLUDE_DIRS}

    PUBLIC_CLASSES
        fieldTextureData
        glslfx
        glslfxConfig
        image
        imageRegistry
        types

    PRIVATE_CLASSES
        debugCodes
        dictionary

    PUBLIC_HEADERS
        api.h

    PRIVATE_HEADERS
        rankedTypeMap.h
        stb/stb_image.h
        stb/stb_image_resize.h
        stb/stb_image_write.h

    CPPFILES
        stbImage.cpp
        OpenEXR/openexr-c.c

    RESOURCE_FILES
        plugInfo.json

    DOXYGEN_FILES
        overview.dox
)

target_compile_definitions(hio PRIVATE
    ILMTHREAD_THREADING_ENABLED
    OPENEXR_C_STANDALONE
    OPENEXR_EXPORT=static)
