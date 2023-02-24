
include(ExternalProject)

message (STATUS "Added geographiclib to external submodules")

ExternalProject_Add(
    geographiclib
    GIT_REPOSITORY      https://github.com/geographiclib/geographiclib
    GIT_SHALLOW         1
    GIT_TAG             v2.1.2
    GIT_CONFIG          fetch.recurseSubmodules=true
    CMAKE_ARGS          -DCMAKE_UNITY_BUILD=YES -DCMAKE_INSTALL_LIBDIR=${CMAKE_INSTALL_LIBDIR} 
    PREFIX              ${CMAKE_BINARY_DIR}/external/geographiclib/prefix
    TMP_DIR             ${CMAKE_BINARY_DIR}/external/geographiclib/tmp
    STAMP_DIR           ${CMAKE_BINARY_DIR}/external/geographiclib/stamp
    DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/external/geographiclib/download
    SOURCE_DIR          ${CMAKE_BINARY_DIR}/external/geographiclib/src
    INSTALL_DIR         ${CMAKE_BINARY_DIR}/external/geographiclib/install
    BUILD_COMMAND       make $(nproc)
    INSTALL_COMMAND     make DESTDIR=${CMAKE_BINARY_DIR}/external/install install
    UPDATE_DISCONNECTED 1
)

if (MSYS)
  set(GEOGRAPHIC_INCLUDE_DIRS "${CMAKE_BINARY_DIR}/external/install/Program Files (x86)/GeographicLib/include")
else()
  set(GEOGRAPHIC_INCLUDE_DIRS ${CMAKE_BINARY_DIR}/external/install/usr/local/include)
endif()

set(GEOGRAPHIC_LIBARAIES GeographicLib)