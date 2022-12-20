# ------------------------------------------------------------------------------
# cairo
# ------------------------------------------------------------------------------
ExternalProject_Add(
    libcairo
    GIT_REPOSITORY      https://github.com/freedesktop/cairo
    GIT_SHALLOW         1
    CMAKE_ARGS          -DCMAKE_UNITY_BUILD=YES
    GIT_TAG             master
    PREFIX              ${CMAKE_BINARY_DIR}/external/libcairo/prefix
    TMP_DIR             ${CMAKE_BINARY_DIR}/external/libcairo/tmp
    STAMP_DIR           ${CMAKE_BINARY_DIR}/external/libcairo/stamp
    DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/external/libcairo/download
    SOURCE_DIR          ${CMAKE_BINARY_DIR}/external/libcairo/src
    CONFIGURE_COMMAND   cd ${CMAKE_BINARY_DIR}/external/libcairo/src && ./autogen.sh --prefix=${CMAKE_BINARY_DIR}/external/install/opt/cairo/lib --enable-glesv3
    BUILD_IN_SOURCE     TRUE
    BUILD_COMMAND       make $(nproc)
    INSTALL_COMMAND     make install
    UPDATE_DISCONNECTED 1
    BUILD_ALWAYS        0
)

set(CAIRO_INCLUDE_DIRS ${CMAKE_BINARY_DIR}/external/install/opt/cairo/lib/lib)
set(CAIRO_LIBARAIES osmscout_import cairo)