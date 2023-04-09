# ------------------------------------------------------------------------------
# vivoe-media-framework
# ------------------------------------------------------------------------------
ExternalProject_Add(
    vivoe_media
    GIT_REPOSITORY      https://github.com/DefenceX/vivoe-media-framework
    GIT_SHALLOW         1
	GIT_TAG             main
	CMAKE_ARGS          -DCMAKE_INSTALL_PREFIX:PATH=/opt/gva/libs
    PREFIX              ${CMAKE_BINARY_DIR}/external/vivoe-media-framework/prefix
    TMP_DIR             ${CMAKE_BINARY_DIR}/external/vivoe-media-framework/tmp
    STAMP_DIR           ${CMAKE_BINARY_DIR}/external/vivoe-media-framework/stamp
    DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/external/vivoe-media-framework/download
    SOURCE_DIR          ${CMAKE_BINARY_DIR}/external/vivoe-media-framework/src
    BINARY_DIR          ${CMAKE_BINARY_DIR}/external/vivoe-media-framework/build
    INSTALL_COMMAND     make DESTDIR=${CMAKE_BINARY_DIR}/external/install install
    UPDATE_DISCONNECTED 1
)

set(MEDIA_INCLUDE_DIR ${CMAKE_BINARY_DIR}/external/vivoe-media-framework/src)
