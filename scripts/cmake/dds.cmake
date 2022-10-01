include(ExternalProject)

if (NOT DDS)
    set(DDS "CYCLONE") # Default option for DDS if not specified
endif()

message(STATUS "Setting DDS to ${DDS}")

if (DDS EQUAL "FASTDDS")
# ------------------------------------------------------------------------------
# Fast-DDS
# ------------------------------------------------------------------------------

if (HMI_ONLY)
# Dummy the targets our for quicker build
add_custom_target(Fast_CDR)
add_custom_target(foonathan_memory_vendor)
add_custom_target(Fast_DDS)
endif()

message(STATUS "SUBPROJECT_NAME = fastdds")
set(BUILD_DOCUMENTATION OFF CACHE BOOL "Disable build documentation")
set(DDS_STACK = "Fast_DDS")


ExternalProject_Add(
    Fast_CDR
    GIT_REPOSITORY      https://github.com/eProsima/Fast-CDR.git
    GIT_TAG             "v1.0.21"
    GIT_SHALLOW         5
    GIT_CONFIG          fetch.recurseSubmodules=true
    CMAKE_ARGS          "--build . --target install"
    PREFIX              ${CMAKE_BINARY_DIR}/external/Fast-CDR/prefix
    TMP_DIR             ${CMAKE_BINARY_DIR}/external/Fast-CDR/tmp
    STAMP_DIR           ${CMAKE_BINARY_DIR}/external/Fast-CDR/stamp
    DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/external/Fast-CDR/download
    SOURCE_DIR          ${CMAKE_BINARY_DIR}/external/Fast-CDR/src
    BINARY_DIR          ${CMAKE_BINARY_DIR}/external/Fast-CDR/build
    SOURCE_SUBDIR       ""
    INSTALL_COMMAND     cd ${CMAKE_BINARY_DIR}/external/Fast-CDR/build; sudo make build
    TEST_COMMAND        ""
    UPDATE_DISCONNECTED 1
    BUILD_ALWAYS        0
)
ExternalProject_Add(
    foonathan_memory_vendor
    GIT_REPOSITORY      https://github.com/eProsima/foonathan_memory_vendor.git
    GIT_TAG             "v1.1.0"
    GIT_SHALLOW         5
    GIT_CONFIG          fetch.recurseSubmodules=true
    CMAKE_ARGS          "--build . --target install"
    PREFIX              ${CMAKE_BINARY_DIR}/external/foonathan_memory_vendor/prefix
    TMP_DIR             ${CMAKE_BINARY_DIR}/external/foonathan_memory_vendor/tmp
    STAMP_DIR           ${CMAKE_BINARY_DIR}/external/foonathan_memory_vendor/stamp
    DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/external/foonathan_memory_vendor/download
    SOURCE_DIR          ${CMAKE_BINARY_DIR}/external/foonathan_memory_vendor/src
    BINARY_DIR          ${CMAKE_BINARY_DIR}/external/foonathan_memory_vendor/build
    SOURCE_SUBDIR        "../src"
    INSTALL_COMMAND     cd ${CMAKE_BINARY_DIR}/external/foonathan_memory_vendor/build; sudo make build
    TEST_COMMAND        ""
    UPDATE_DISCONNECTED 1
    BUILD_ALWAYS        0
)
ExternalProject_Add(
    ${DDS_STACK}
    GIT_REPOSITORY      https://github.com/eProsima/Fast-DDS
    GIT_TAG             v2.3.0
    GIT_SHALLOW         5
    GIT_CONFIG          fetch.recurseSubmodules=true
    CMAKE_ARGS          "--build . --target install"
    PREFIX              ${CMAKE_BINARY_DIR}/external/Fast-DDS/prefix
    TMP_DIR             ${CMAKE_BINARY_DIR}/external/Fast-DDS/tmp
    STAMP_DIR           ${CMAKE_BINARY_DIR}/external/Fast-DDS/stamp
    DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/external/Fast-DDS/download
    SOURCE_DIR          ${CMAKE_BINARY_DIR}/external/Fast-DDS/src
    BINARY_DIR          ${CMAKE_BINARY_DIR}/external/Fast-DDS/build
    SOURCE_SUBDIR        "../src"
    INSTALL_COMMAND     ""
    TEST_COMMAND        ""
    UPDATE_DISCONNECTED 1
    BUILD_ALWAYS        0
)
endif()

if ("${DDS}" STREQUAL "CYCLONE")
# ------------------------------------------------------------------------------
# Cyclone-DDS
# ------------------------------------------------------------------------------
set(DDS_STACK "cycloneDds")

if (HMI_ONLY)
# Dummy the targets our for quicker build
add_custom_target(${DDS_STACK})
endif()

ExternalProject_Add(
    ${DDS_STACK}
    GIT_REPOSITORY      https://github.com/eclipse-cyclonedds/cyclonedds
    GIT_TAG             "0.10.2"
    GIT_SHALLOW         5
    GIT_CONFIG          fetch.recurseSubmodules=true
    CMAKE_ARGS          "--build . --target install"
    PREFIX              ${CMAKE_BINARY_DIR}/external/cyclonedds/prefix
    TMP_DIR             ${CMAKE_BINARY_DIR}/external/cyclonedds/tmp
    STAMP_DIR           ${CMAKE_BINARY_DIR}/external/cyclonedds/stamp
    DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/external/cyclonedds/download
    SOURCE_DIR          ${CMAKE_BINARY_DIR}/external/cyclonedds/src
    BINARY_DIR          ${CMAKE_BINARY_DIR}/external/cyclonedds/build
    SOURCE_SUBDIR       ""
    INSTALL_COMMAND     cd ${CMAKE_BINARY_DIR}/external/cyclonedds/build; sudo make build
    TEST_COMMAND        ""
    UPDATE_DISCONNECTED 1
    BUILD_ALWAYS        0
)

endif()

