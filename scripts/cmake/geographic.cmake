
ExternalProject_Add(
    geographiclib
    GIT_REPOSITORY      https://github.com/geographiclib/geographiclib
    GIT_SHALLOW         5
    GIT_TAG             main
    GIT_CONFIG          fetch.recurseSubmodules=true
    CONFIGURE_COMMAND   bash -c "mkdir -p build && cd build && cmake .."
    PREFIX              ${CMAKE_BINARY_DIR}/external/geographiclib/prefix
    TMP_DIR             ${CMAKE_BINARY_DIR}/external/geographiclib/tmp
    STAMP_DIR           ${CMAKE_BINARY_DIR}/external/geographiclib/stamp
    DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/external/geographiclib/download
    SOURCE_DIR          ${CMAKE_BINARY_DIR}/external/geographiclib/src
    INSTALL_DIR         ${CMAKE_BINARY_DIR}/external/geographiclib/install
    SOURCE_SUBDIR       ""
    BUILD_IN_SOURCE     TRUE
    BUILD_COMMAND       bash -c "cd build && make $(nproc)"
    INSTALL_COMMAND     bash -c "cd build && make DESTDIR=${CMAKE_BINARY_DIR}/external/install install"
    TEST_COMMAND        ""
    UPDATE_DISCONNECTED 1
    BUILD_ALWAYS        0
)

set(GEOGRAPHIC_INCLUDE_DIRS ${CMAKE_BINARY_DIR}/external/install/usr/local/include)
set(GEOGRAPHIC_LIBARAIES GeographicLib)