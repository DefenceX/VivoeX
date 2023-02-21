
include(ExternalProject)

message (STATUS "Added libnmea to external submodules")

# ------------------------------------------------------------------------------
# libnema
# ------------------------------------------------------------------------------
ExternalProject_Add(
    libnmea
    URL                 https://sourceforge.net/projects/nmea/files/NmeaLib/nmea-0.5.x/nmealib-0.5.3.zip
    # DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    PREFIX              ${CMAKE_BINARY_DIR}/external/libnmea/prefix
    TMP_DIR             ${CMAKE_BINARY_DIR}/external/libnmea/tmp
    STAMP_DIR           ${CMAKE_BINARY_DIR}/external/libnmea/stamp
    DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/external/libnmea/download
    SOURCE_DIR          ${CMAKE_BINARY_DIR}/external/libnmea/src
    BUILD_IN_SOURCE     TRUE
    CONFIGURE_COMMAND   ""
    BUILD_COMMAND       make
    INSTALL_COMMAND     "" 
    UPDATE_DISCONNECTED 1
    BUILD_ALWAYS        0
)


set(NEMA_INCLUDER_DIRS "${CMAKE_BINARY_DIR}/external/install/Program Files (x86)/GeographicLib/include")
