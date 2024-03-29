
include(ExternalProject)

message (STATUS "Added libnmea to external submodules")

# ------------------------------------------------------------------------------
# libnema
# ------------------------------------------------------------------------------
ExternalProject_Add(
    libnmea
    GIT_REPOSITORY      https://github.com/DefenceX/nmealib
    GIT_TAG             master
    CMAKE_ARGS          -DCMAKE_INSTALL_LIBDIR=${CMAKE_INSTALL_LIBDIR}
    PREFIX              ${CMAKE_BINARY_DIR}/external/libnmea/prefix
    TMP_DIR             ${CMAKE_BINARY_DIR}/external/libnmea/tmp
    STAMP_DIR           ${CMAKE_BINARY_DIR}/external/libnmea/stamp
    DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/external/libnmea/download
    SOURCE_DIR          ${CMAKE_BINARY_DIR}/external/libnmea/src
    BINARY_DIR          ${CMAKE_BINARY_DIR}/external/libnmea/build
    INSTALL_COMMAND     make DESTDIR=${CMAKE_BINARY_DIR}/external/install install
    UPDATE_DISCONNECTED 1
)
include_directories(/usr/lib/x86_64-linux-gnu)

if (MSYS)
  set(NMEA_INCLUDE_DIR "${CMAKE_BINARY_DIR}/external/libnmea/src/include")
  set(NMEA_LIBRARY_DIR "${CMAKE_BINARY_DIR}/external/install/Program Files (x86)/nmea/lib")
else()
  set(NMEA_INCLUDE_DIR ${CMAKE_BINARY_DIR}/external/libnmea/src/include)
  set(NMEA_LIBRARY_DIR ${CMAKE_BINARY_DIR}/external/install/usr/local/lib)
endif()
