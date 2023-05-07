# ------------------------------------------------------------------------------
# mediax
# ------------------------------------------------------------------------------
ExternalProject_Add(
    libmediax
    GIT_REPOSITORY      https://github.com/DefenceX/MediaX
    GIT_SHALLOW         1
    CMAKE_ARGS          -DEXAMPLES=OFF
	# GIT_TAG             v0.5.0
	GIT_TAG             main
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
