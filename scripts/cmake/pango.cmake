
include(ExternalProject)

message (STATUS "Added libpango to external submodules")

# ------------------------------------------------------------------------------
# libpango
# ------------------------------------------------------------------------------
ExternalProject_Add(
    libpango
    GIT_REPOSITORY      https://github.com/GNOME/pango
    GIT_SHALLOW         1
    CMAKE_ARGS          -DCMAKE_UNITY_BUILD=YES
    GIT_TAG             main
    PREFIX              ${CMAKE_BINARY_DIR}/external/libpango/prefix
    TMP_DIR             ${CMAKE_BINARY_DIR}/external/libpango/tmp
    STAMP_DIR           ${CMAKE_BINARY_DIR}/external/libpango/stamp
    DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/external/libpango/download
    SOURCE_DIR          ${CMAKE_BINARY_DIR}/external/libpango/src
    CONFIGURE_COMMAND   cd ${CMAKE_BINARY_DIR}/external/libpango/src && meson --prefix=${CMAKE_BINARY_DIR}/external/install build
    BUILD_IN_SOURCE     TRUE
    BUILD_COMMAND       cd ${CMAKE_BINARY_DIR}/external/libpango/src/build && ninja
    INSTALL_COMMAND     cd ${CMAKE_BINARY_DIR}/external/libpango/src/build && ninja install
    UPDATE_DISCONNECTED 1
    BUILD_ALWAYS        0
)

set(PANGO_INCLUDE_DIRS ${CMAKE_BINARY_DIR}/external/install/lib/${ARCH}-linux-gnu)
set(PANGO_LIBARARY_DIRS ${CMAKE_BINARY_DIR}/external/install/lib/${ARCH}-linux-gnu)
set(PANGO_LIBARAIES pango pangocairo)