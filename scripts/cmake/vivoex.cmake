# ------------------------------------------------------------------------------
# mediax
# ------------------------------------------------------------------------------
ExternalProject_Add(
    vivoe_media
    GIT_REPOSITORY      https://github.com/DefenceX/MediaX
    GIT_SHALLOW         1
	GIT_TAG             v0.5.0
	CMAKE_ARGS          -DCMAKE_INSTALL_PREFIX:PATH=/opt/gva/libs
    PREFIX              ${CMAKE_BINARY_DIR}/external/mediax/prefix
    TMP_DIR             ${CMAKE_BINARY_DIR}/external/mediax/tmp
    STAMP_DIR           ${CMAKE_BINARY_DIR}/external/mediax/stamp
    DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/external/mediax/download
    SOURCE_DIR          ${CMAKE_BINARY_DIR}/external/mediax/src
    BINARY_DIR          ${CMAKE_BINARY_DIR}/external/mediax/build
    INSTALL_COMMAND     make DESTDIR=${CMAKE_BINARY_DIR}/external/install install
    UPDATE_DISCONNECTED 1
)

set(MEDIA_INCLUDE_DIR ${CMAKE_BINARY_DIR}/external/mediax/src)
