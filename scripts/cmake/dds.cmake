include(ExternalProject)
include(FindPkgConfig)

if (NOT DDS)
    set(DDS "CYCLONE-CE") # Default option for DDS if not specified
endif()

message(STATUS "Setting DDS to ${DDS}")

if ("${DDS}" STREQUAL "FASTDDS")
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

# ------------------------------------------------------------------------------
# Cyclone-DDS
# ------------------------------------------------------------------------------
if ("${DDS}" STREQUAL "CYCLONE-CE")
set(DDS_STACK "CycloneDDS")

if (HMI_ONLY)
# Dummy the targets our for quicker build
add_custom_target(${DDS_STACK})
endif()

ExternalProject_Add(
    ${DDS_STACK}
    GIT_REPOSITORY      https://github.com/eclipse-cyclonedds/cyclonedds
    GIT_TAG             "0.10.2"
    GIT_SHALLOW         1
    GIT_CONFIG          fetch.recurseSubmodules=true
    CMAKE_ARGS          -DCMAKE_INSTALL_MESSAGE=LAZY -DCMAKE_INSTALL_LIBDIR=${CMAKE_INSTALL_LIBDIR}
    PREFIX              ${CMAKE_BINARY_DIR}/external/cyclonedds/prefix
    TMP_DIR             ${CMAKE_BINARY_DIR}/external/cyclonedds/tmp
    STAMP_DIR           ${CMAKE_BINARY_DIR}/external/cyclonedds/stamp
    DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/external/cyclonedds/download
    SOURCE_DIR          ${CMAKE_BINARY_DIR}/external/cyclonedds/src
    BINARY_DIR          ${CMAKE_BINARY_DIR}/external/cyclonedds/build
    INSTALL_DIR         ${CMAKE_BINARY_DIR}/external/install
    SOURCE_SUBDIR       ""
    INSTALL_COMMAND     make DESTDIR=${CMAKE_BINARY_DIR}/external/install install
    TEST_COMMAND        ""
    UPDATE_DISCONNECTED 1
    BUILD_ALWAYS        0
)

# Search for Ubuntu
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR}/external/install/usr/local/lib/cmake/CycloneDDS)
# Search for CentOS
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR}/external/install/usr/local/lib64/cmake/CycloneDDS)
set(CycloneDDS_DIR ${CMAKE_BINARY_DIR}/external/install/usr/local/lib64/cmake/CycloneDDS)

execute_process(COMMAND arch OUTPUT_VARIABLE AARCH ERROR_VARIABLE ERROR OUTPUT_STRIP_TRAILING_WHITESPACE)
if (${AARCH} STREQUAL "x86_64")
  set(CYCLONE_INSTALL_PATH /external/install/usr/local/lib64/cmake/CycloneDDS) # Intel
elseif(${AARCH} STREQUAL "aarch64")
  set(CYCLONE_INSTALL_PATH /external/install/usr/local/lib/aarch64-linux-gnu/cmake/CycloneDDS) # ARM (Raspberry Pi)
else()
  message(FATAL_ERROR "Unrecognised or unsupported processor architecture ${AARCH}!!! ${ERROR}")
endif()

message (STATUS "Detected Cyclone installed at ${CYCLONE_INSTALL_PATH}")

ExternalProject_Add(
    cyclonedds-cxx
    GIT_REPOSITORY      https://github.com/eclipse-cyclonedds/cyclonedds-cxx
    GIT_TAG             "0.10.2"
    GIT_SHALLOW         5
    GIT_CONFIG          fetch.recurseSubmodules=true
    CMAKE_ARGS          -DCMAKE_INSTALL_PREFIX=/usr/local -DCycloneDDS_DIR=${CMAKE_BINARY_DIR}${CYCLONE_INSTALL_PATH} -DCMAKE_INSTALL_LIBDIR=${CMAKE_INSTALL_LIBDIR} -DCMAKE_INSTALL_MESSAGE=LAZY 
    PREFIX              ${CMAKE_BINARY_DIR}/external/cyclonedds-cxx/prefix
    TMP_DIR             ${CMAKE_BINARY_DIR}/external/cyclonedds-cxx/tmp
    STAMP_DIR           ${CMAKE_BINARY_DIR}/external/cyclonedds-cxx/stamp
    DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/external/cyclonedds-cxx/download
    SOURCE_DIR          ${CMAKE_BINARY_DIR}/external/cyclonedds-cxx/src
    INSTALL_DIR         ${CMAKE_BINARY_DIR}/external/install
    BINARY_DIR          ${CMAKE_BINARY_DIR}/external/cyclonedds-cxx/build
    SOURCE_SUBDIR       ""
    INSTALL_COMMAND     make DESTDIR=${CMAKE_BINARY_DIR}/external/install install
    TEST_COMMAND        ""
    UPDATE_DISCONNECTED 1
    BUILD_ALWAYS        0
)

add_dependencies(cyclonedds-cxx ${DDS_STACK})

set(DDS_LIBRARY_DIRS"${CMAKE_BINARY_DIR}/external/cyclonedds/lib/")
set(DDS_LIBRARIES "ddsc cycloneddsidl dds_security_auth cycloneddsidl dds_security_ac dds_security_crypto")
set(DDS_INCLUDES "${CMAKE_BINARY_DIR}/external/cyclonedds/src/src")

endif()

if ("${DDS}" STREQUAL "OSPL-CE")
# ------------------------------------------------------------------------------
# Opensplice-DDS
# ------------------------------------------------------------------------------
set(DDS_STACK "OpenspliceDDS")

if (HMI_ONLY)
# Dummy the targets our for quicker build
add_custom_target(${DDS_STACK})
endif()

ExternalProject_Add(
    ${DDS_STACK}
    GIT_REPOSITORY      https://github.com/DefenceX/opensplice
    GIT_SHALLOW         5
    GIT_CONFIG          fetch.recurseSubmodules=true
    CONFIGURE_COMMAND   bash -c "cd ${CMAKE_BINARY_DIR}/external/opensplice/src && export GSOAPHOME=/usr/share/gsoap && source ./configure x86_64.linux-release"
    PREFIX              ${CMAKE_BINARY_DIR}/external/opensplice/prefix
    TMP_DIR             ${CMAKE_BINARY_DIR}/external/opensplice/tmp
    STAMP_DIR           ${CMAKE_BINARY_DIR}/external/opensplice/stamp
    DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/external/opensplice/download
    SOURCE_DIR          ${CMAKE_BINARY_DIR}/external/opensplice/src
    INSTALL_DIR         ${CMAKE_BINARY_DIR}/external/opensplice/install
    SOURCE_SUBDIR       ""
    BUILD_IN_SOURCE     TRUE
    BUILD_COMMAND       bash -c "cd ${CMAKE_BINARY_DIR}/external/opensplice/src && source ./configure x86_64.linux-release && make $(nproc) CFLAGS='-Wno-error -fPIC'"
    INSTALL_COMMAND     bash -c "cd ${CMAKE_BINARY_DIR}/external/opensplice/src && source ./configure x86_64.linux-release && make DESTDIR=${CMAKE_BINARY_DIR}/external/install install"
    TEST_COMMAND        ""
    UPDATE_DISCONNECTED 1
    BUILD_ALWAYS        0
)

set(DDS_LIBRARY_DIRS"${CMAKE_BINARY_DIR}/external/opensplice/lib/")
set(DDS_LIBRARIES "ddsc cycloneddsidl dds_security_auth cycloneddsidl dds_security_ac dds_security_crypto")
set(DDS_INCLUDES "${CMAKE_BINARY_DIR}/external/opensplice/src/src")

endif()

