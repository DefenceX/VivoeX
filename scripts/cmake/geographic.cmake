
include(ExternalProject)

message (STATUS "Added geographiclib to external submodules")

ExternalProject_Add(
    geographiclib
    GIT_REPOSITORY      https://github.com/geographiclib/geographiclib
    GIT_SHALLOW         1
    GIT_TAG             main
    GIT_CONFIG          fetch.recurseSubmodules=true
    CMAKE_ARGS          -DCMAKE_UNITY_BUILD=YES
    PREFIX              ${CMAKE_BINARY_DIR}/external/geographiclib/prefix
    TMP_DIR             ${CMAKE_BINARY_DIR}/external/geographiclib/tmp
    STAMP_DIR           ${CMAKE_BINARY_DIR}/external/geographiclib/stamp
    DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/external/geographiclib/download
    SOURCE_DIR          ${CMAKE_BINARY_DIR}/external/geographiclib/src
    INSTALL_DIR         ${CMAKE_BINARY_DIR}/external/geographiclib/install
    BUILD_COMMAND       make $(nproc)
    INSTALL_COMMAND     make DESTDIR=${CMAKE_BINARY_DIR}/external/install install
    TEST_COMMAND        ""
    UPDATE_DISCONNECTED 1
    BUILD_ALWAYS        0
)

set(GEOGRAPHIC_INCLUDE_DIRS ${CMAKE_BINARY_DIR}/external/install/usr/local/include)
set(GEOGRAPHIC_LIBARAIES GeographicLib)