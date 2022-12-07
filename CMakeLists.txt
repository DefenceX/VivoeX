cmake_minimum_required(VERSION 3.0…3.16)
project(vivoe-lite)
add_custom_target(vivoe-lite)
add_dependencies(vivoe-lite hmi-display)

include(scripts/cmake/version.cmake)
include(scripts/cmake/dds.cmake)
include(scripts/cmake/cpp.cmake)
include(scripts/cmake/cpack.cmake)
include(scripts/cmake/doxygen.cmake)
include(scripts/cmake/dot.cmake)
include(scripts/cmake/gtest.cmake)
include(scripts/cmake/geographic.cmake)

include_directories(${CMAKE_SOURCE_DIR}/hmi-display)

if (ENABLE_OSMSCOUT)
    # lots of warnings and all warnings as errors
    Message(STATUS "Building OSM Scout into BMS")
    add_compile_options(-DENABLE_OSMSCOUT)
endif()

execute_process(COMMAND ../update.sh)
# add_subdirectory(dds)
add_subdirectory(test)
add_subdirectory(video)
add_subdirectory(hmi-display)

## Here you can set the default 'dummy' camera feed images
#set(IMAGE_PATH ${CMAKE_SOURCE_DIR}/images/uk)
set(IMAGE_PATH ${CMAKE_SOURCE_DIR}/images/au)

option(HMI_ONLY "only build HMI and Tools" OFF)

if (HMI_ONLY)
add_custom_target(libosmscout)
add_custom_target(libnmea)
else (HMI_ONLY)

if (ENABLE_OSMSCOUT)
	if (${CMAKE_SYSTEM_NAME} MATCHES "MSYS")
		message("libosmscout not currently supported under MSYS2...")
	else()
	# ------------------------------------------------------------------------------
	# libosmscout
	# ------------------------------------------------------------------------------
	set(OSMSCOUT_BUILD_TEST OFF CACHE BOOL "Disable build of test library")
	list(APPEND CMAKE_MODULE_PATH ../libosmscout/cmake)

	ExternalProject_Add(
	    libosmscout
	    GIT_REPOSITORY      https://github.com/Framstag/libosmscout
#	    GIT_TAG             1.1.0
	    GIT_SHALLOW         1
	    CMAKE_ARGS          "-DCMAKE_BUILD_TYPE=Release -DOSMSCOUT_BUILD_DOC_API=Off -DOSMSCOUT_BUILD_TESTS=Off -DOSMSCOUT_BUILD_GPX=Off -DOSMSCOUT_BUILD_MAP_AGG=Off -DOSMSCOUT_BUILD_MAP_SVG=Off -DOSMSCOUT_BUILD_MAP_OPENGL=Off -DOSMSCOUT_BUILD_MAP_QT=Off -D=OSMSCOUT_BUILD_CLIENT_QT=Off -DOSMSCOUT_BUILD_MAP_SVG=Off -DOSMSCOUT_BUILD_WEBPAGE=Off"
	    PREFIX              ${CMAKE_BINARY_DIR}/external/libosmscout/prefix
	    TMP_DIR             ${CMAKE_BINARY_DIR}/external/libosmscout/tmp
	    STAMP_DIR           ${CMAKE_BINARY_DIR}/external/libosmscout/stamp
	    DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/external/libosmscout/download
	    SOURCE_DIR          ${CMAKE_BINARY_DIR}/external/libosmscout/src
	    BINARY_DIR          ${CMAKE_BINARY_DIR}/external/libosmscout/build
	    CONFIGURE_COMMAND   cmake ../src -DOSMSCOUT_BUILD_DOC_API=OFF -DOSMSCOUT_BUILD_TESTS=OFF -DOSMSCOUT_BUILD_TOOL_OSMSCOUT2=OFF -DOSMSCOUT_BUILD_GPX=OFF -DOSMSCOUT_BUILD_MAP_AGG=OFF -DOSMSCOUT_BUILD_MAP_SVG=OFF -DOSMSCOUT_BUILD_MAP_OPENGL=OFF -DOSMSCOUT_BUILD_MAP_QT=OFF -DOSMSCOUT_BUILD_CLIENT_QT=OFF -DOSMSCOUT_BUILD_TOOL_STYLEEDITOR=OFF -DOSMSCOUT_BUILD_MAP_SVG=OFF -DOSMSCOUT_BUILD_WEBPAGE=OFF
	    BUILD_COMMAND       ${MAKE}
	    SOURCE_SUBDIR       "../src"
	    INSTALL_COMMAND     ""
	    TEST_COMMAND        ""
	    UPDATE_DISCONNECTED 1
	    BUILD_ALWAYS        0
	)
	endif()
endif()

# ------------------------------------------------------------------------------
# vivoe-media-framework
# ------------------------------------------------------------------------------
ExternalProject_Add(
    vivoe_media
    GIT_REPOSITORY      https://github.com/DefenceX/vivoe-media-framework
    GIT_SHALLOW         1
	GIT_TAG             main
	CMAKE_ARGS          -DCMAKE_INSTALL_PREFIX:PATH=/opt/gva/libs
    PREFIX              ${CMAKE_BINARY_DIR}/external/vivoe-media-framework/prefix
    TMP_DIR             ${CMAKE_BINARY_DIR}/external/vivoe-media-framework/tmp
    STAMP_DIR           ${CMAKE_BINARY_DIR}/external/vivoe-media-framework/stamp
    DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/external/vivoe-media-framework/download
    SOURCE_DIR          ${CMAKE_BINARY_DIR}/external/vivoe-media-framework/src
    BINARY_DIR          ${CMAKE_BINARY_DIR}/external/vivoe-media-framework/build
    INSTALL_COMMAND     ""
    UPDATE_DISCONNECTED 1
    BUILD_ALWAYS        0
)

# ------------------------------------------------------------------------------
# libnema
# ------------------------------------------------------------------------------
ExternalProject_Add(
    libnmea
    GIT_REPOSITORY      https://github.com/DefenceX/nmealib
    GIT_SHALLOW         1
    CMAKE_ARGS          ""
    GIT_TAG             main
    PREFIX              ${CMAKE_BINARY_DIR}/external/libnmea/prefix
    TMP_DIR             ${CMAKE_BINARY_DIR}/external/libnmea/tmp
    STAMP_DIR           ${CMAKE_BINARY_DIR}/external/libnmea/stamp
    DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/external/libnmea/download
    SOURCE_DIR          ${CMAKE_BINARY_DIR}/external/libnmea/src
    BINARY_DIR          ${CMAKE_BINARY_DIR}/external/libnmea/build
    INSTALL_COMMAND     ""
    UPDATE_DISCONNECTED 1
    BUILD_ALWAYS        0
)

# # ------------------------------------------------------------------------------
# # Catch
# # ------------------------------------------------------------------------------
# list(APPEND CATCH_CMAKE_ARGS
#     "-DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}"
# )

# ExternalProject_Add(
#     catch
#     GIT_REPOSITORY      https://github.com/Bareflank/catch.git
#     GIT_TAG             v1.2
#     GIT_SHALLOW         1
#     CMAKE_ARGS          ${CATCH_CMAKE_ARGS}
#     PREFIX              ${CMAKE_BINARY_DIR}/external/catch/prefix
#     TMP_DIR             ${CMAKE_BINARY_DIR}/external/catch/tmp
#     STAMP_DIR           ${CMAKE_BINARY_DIR}/external/catch/stamp
#     DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/external/catch/download
#     SOURCE_DIR          ${CMAKE_BINARY_DIR}/external/catch/src
#     BINARY_DIR          ${CMAKE_BINARY_DIR}/external/catch/build
#     UPDATE_DISCONNECTED 1
# )
endif (HMI_ONLY)

# Install DDS
file(GLOB DDS_LIBS ${CMAKE_BINARY_DIR}/external/cyclonedds/build/lib/*.so*)

# Install binaries with external libs
file(WRITE ${CMAKE_BINARY_DIR}/gva.log "")
install(FILES ${CMAKE_BINARY_DIR}/gva.log DESTINATION "/var/log" PERMISSIONS OWNER_WRITE OWNER_READ GROUP_WRITE GROUP_READ WORLD_READ WORLD_WRITE)
install(FILES ${CMAKE_BINARY_DIR}/external/vivoe-media-framework/build/libvivoe-media.so DESTINATION "/opt/gva/libs")
install(FILES ${CMAKE_BINARY_DIR}/etc/ld.so.confcmake_minimum_required(VERSION 3.14)
.d/vivoe-lite.conf DESTINATION "/etc/ld.so.conf.d") 
install(FILES ${CMAKE_BINARY_DIR}/etc/profile.d/vivoe-lite.sh DESTINATION "/etc/profile.d")
install(FILES ${CMAKE_BINARY_DIR}/external/libnmea/build/src/libnmealib.so 
              ${CMAKE_BINARY_DIR}/external/vivoe-media-framework/build/libvivoe-media.so
              ${CMAKE_BINARY_DIR}/external/vivoe-media-framework/build/libvivoe-media.so.1
              ${CMAKE_BINARY_DIR}/external/geographiclib/src/build/src/libGeographicLib.so
              ${CMAKE_BINARY_DIR}/external/geographiclib/src/build/src/libGeographicLib.so.23
              ${CMAKE_BINARY_DIR}/external/geographiclib/src/build/src/libGeographicLib.so.23.0.1
              ${DDS_LIBS}
        DESTINATION "/opt/gva/libs" PERMISSIONS OWNER_WRITE OWNER_READ OWNER_EXECUTE GROUP_WRITE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_WRITE WORLD_EXECUTE)

# Images for dummy camera feeds
install(FILES  
    ${IMAGE_PATH}/FrontRight.png 
    ${IMAGE_PATH}/FrontCenter.png 
    ${IMAGE_PATH}/FrontLeft.png 
    ${IMAGE_PATH}/Right.png 
    ${IMAGE_PATH}/Rear.png 
    ${IMAGE_PATH}/Left.png 
    ${IMAGE_PATH}/Quad.png 
    DESTINATION "/opt/gva/hmi/images")

# All other images
install(FILES  
    ${CMAKE_SOURCE_DIR}/images/screen/DefenceX.png 
    DESTINATION "/opt/gva/hmi/images")

aux_source_directory(${CMAKE_SOURCE_DIR}/src src)

# include CMake module
include(scripts/cmake/cpplint.cmake)

# add all source code directories
cpplint_add_subdirectory(hmi-display)
cpplint_add_subdirectory(video)

# Uninstall target
if(NOT TARGET uninstall)
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/scripts/cmake/uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

  add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
endif()
