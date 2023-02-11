# ------------------------------------------------------------------------------
# vivoe-media-framework
# ------------------------------------------------------------------------------
ExternalProject_Add(
    vivoe_media
    GIT_REPOSITORY      https://github.com/DefenceX/vivoe-media-framework
    GIT_SHALLOW         1
	GIT_TAG             v0.3.0
	CMAKE_ARGS          -DCMAKE_INSTALL_PREFIX:PATH=/opt/gva/libs
    PREFIX              ${CMAKE_BINARY_DIR}/external/vivoe-media-framework/prefix
    TMP_DIR             ${CMAKE_BINARY_DIR}/external/vivoe-media-framework/tmp
    STAMP_DIR           ${CMAKE_BINARY_DIR}/external/vivoe-media-framework/stamp
    DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/external/vivoe-media-framework/download
    SOURCE_DIR          ${CMAKE_BINARY_DIR}/external/vivoe-media-framework/src
    BINARY_DIR          ${CMAKE_BINARY_DIR}/external/vivoe-media-framework/build
    BUILD_COMMAND       bash -c "make $(nproc)"
    INSTALL_COMMAND     bash -c "make DESTDIR=${CMAKE_BINARY_DIR}/external/install install"
    UPDATE_DISCONNECTED 1
    BUILD_ALWAYS        0
)
