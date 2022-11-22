cmake_minimum_required(VERSION 3.0…3.16)
project(vivoe-lite)
add_custom_target(vivoe-lite)
add_dependencies(vivoe-lite hmi-display)

include(scripts/cmake/version.cmake)
include(scripts/cmake/dds.cmake)
include(scripts/cmake/cpp.cmake)
include(scripts/cmake/cpack.cmake)
include(scripts/cmake/doxygen.cmake)

include_directories(${CMAKE_SOURCE_DIR}/hmi-display)

if (ENABLE_OSMSCOUT)
    # lots of warnings and all warnings as errors
    Message(STATUS "Building OSM Scout into BMS")
    add_compile_options(-DENABLE_OSMSCOUT)
endif()

execute_process(COMMAND ../update.sh)
# add_subdirectory(dds)
add_subdirectory(video)
add_subdirectory(hmi-display)

## Here you can set the default 'dummy' camer feed images
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

option(BUILD_TESTS "Build the tests" OFF)

if (BUILD_TESTS)
# ------------------------------------------------------------------------------
# Tests
# ------------------------------------------------------------------------------
include(CTest)
include(FindPkgConfig)

# ------------------------------------------------------------------------------
# Includes
# ------------------------------------------------------------------------------

include_directories(include)
if (ENABLE_OSMSCOUT)
	include_directories(${CMAKE_BINARY_DIR}/external/libosmscout/src/libosmscout/include)
	include_directories(${CMAKE_BINARY_DIR}/external/libosmscout/src/libosmscout-map/include)
	include_directories(${CMAKE_BINARY_DIR}/external/libosmscout/src/libosmscout-map-cairo/include)
	include_directories(${CMAKE_BINARY_DIR}/external/libosmscout/build/libosmscout/include)
	include_directories(${CMAKE_BINARY_DIR}/external/libosmscout/build/libosmscout-map/include)
	include_directories(${CMAKE_BINARY_DIR}/external/libosmscout/build/libosmscout-map-cairo/include)
	include_directories(${PROJECT_SOURCE_DIR}/../libosmscout/libosmscout/include)
	include_directories(${PROJECT_SOURCE_DIR}/../libosmscout/libosmscout-map/include)
	include_directories(${PROJECT_SOURCE_DIR}/../libosmscout/libosmscout-map-cairo/include)
endif()
include_directories(${CMAKE_BINARY_DIR}/external/vivoe-media-framework/src)
include_directories(${CMAKE_BINARY_DIR}/external/libnmea/src/include)
include_directories(SYSTEM ${CMAKE_BINARY_DIR}/include)

# project(test_catch)
# add_library(test_catch STATIC test/test.cset(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if (MSYS)
else()
    find_package(Protobuf REQUIRED)
    include_directories(${Protobuf_INCLUDE_DIRS})
    include_directories(${CMAKE_CURRENT_BINARY_DIR})
    protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROJECT_SOURCE_DIR}/hmi-display/config.proto)
endif()

add_library(business_logic STATIC ${PROTO_SRCS} hmi-display/events_gva.cc hmi-display/hmi_gva.cc hmi-display/hmi_gva_helpers.cc hmi-display/screen_gva.cc hmi-display/renderer_gva.cc hmi-display/renderer.cc hmi-display/renderer_cairo.cc hmi-display/common/log_gva.cc hmi-display/view_gva.cc hmi-display/renderer_map.cc hmi-display/config_reader.cc )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w -std=c++11")
set(EXTRA_LIBS "")
if (ENABLE_OSMSCOUT)
	set(EXTRA_LIBS libosmscout)
	include_directories(${CMAKE_BINARY_DIR}/external/libosmscout/src/libosmscout/include)
	include_directories(${CMAKE_BINARY_DIR}/external/libosmscout/src/libosmscout-map/include)
	include_directories(${CMAKE_BINARY_DIR}/external/libosmscout/src/libosmscout-map-cairo/include)
	include_directories(${CMAKE_BINARY_DIR}/external/libosmscout/build/libosmscout/include)
	include_directories(${CMAKE_BINARY_DIR}/external/libosmscout/build/libosmscout-map/include)
	include_directories(${CMAKE_BINARY_DIR}/external/libosmscout/build/libosmscout-map-cairo/include)
        SET(OSMSCOUT_LIBS ${CMAKE_BINARY_DIR}/external/libosmscout/build/libosmscout ${CMAKE_BINARY_DIR}/external/libosmscout/build/libosmscout-map ${CMAKE_BINARY_DIR}/external/libosmscout/build/libosmscout-map-cairo)
endif()
add_dependencies(business_logic libnmea hmi-video vivoe-media ${EXTRA_LIBS})
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
pkg_check_modules(CAIRO REQUIRED cairo)
pkg_check_modules(PANGO REQUIRED pango)
pkg_check_modules(SWSCALE REQUIRED libswscale)

link_directories(${CMAKE_BINARY_DIR}/external/libnmea/build/src ${OSMSCOUT_LIBS})
target_link_libraries(business_logic ${Protobuf_LIBRARIES} ${GTK3_LIBRARIES} ${CAIRO_LIBRARIES} ${PANGO_LIBRARIES} ${SWSCALE_LIBRARIES} X11 pthread Geographic nmealib osmscout osmscout_map osmscout_map_cairo)
target_compile_definitions(business_logic PRIVATE VIRTUAL=virtual MAIN=unittest_main)
target_include_directories(business_logic PUBLIC ${GTK3_INCLUDE_DIRS} ${CAIRO_INCLUDE_DIRS} ${PANGO_INCLUDE_DIRS} ${SWSCALE_INCLUDE_DIRS} nmealib vivoe-media video hmi-display hmi-display/common )

macro(do_test str)
    add_executable(test_${str} test/test_${str}.cc)
    add_test(test_${str} test_${str})
    target_link_libraries(test_${str}  ${Protobuf_LIBRARIES} test_catch business_logic)
    link_directories(${CMAKE_CURRENT_SOURCE_DIR}/build/nmealib/src ${CMAKE_CURRENT_SOURCE_DIR}/build/include)
    add_dependencies(test_${str} libnmea)
    target_compile_definitions(test_${str} PRIVATE VIRTUAL=virtual)
endmacro(do_test)

do_test(events)
do_test(log)
#do_test(hmi)
endif (BUILD_TESTS)

# Install DDS
file(GLOB DDS_LIBS ${CMAKE_BINARY_DIR}/external/cyclonedds/build/lib/*.so*)

# Install binaries with external libs
file(WRITE ${CMAKE_BINARY_DIR}/gva.log "")
install(FILES ${CMAKE_BINARY_DIR}/gva.log DESTINATION "/var/log" PERMISSIONS OWNER_WRITE OWNER_READ GROUP_WRITE GROUP_READ WORLD_READ WORLD_WRITE)
install(FILES ${CMAKE_BINARY_DIR}/external/vivoe-media-framework/build/libvivoe-media.so DESTINATION "/opt/gva/libs")
install(FILES ${CMAKE_BINARY_DIR}/etc/ld.so.conf.d/vivoe-lite.conf DESTINATION "/etc/ld.so.conf.d") 
install(FILES ${CMAKE_BINARY_DIR}/etc/profile.d/vivoe-lite.sh DESTINATION "/etc/profile.d")
install(FILES ${CMAKE_BINARY_DIR}/external/libnmea/build/src/libnmealib.so 
              ${CMAKE_BINARY_DIR}/external/vivoe-media-framework/build/libvivoe-media.so
              ${CMAKE_BINARY_DIR}/external/vivoe-media-framework/build/libvivoe-media.so.1
              ${DDS_LIBS}
        DESTINATION "/opt/gva/libs" PERMISSIONS OWNER_WRITE OWNER_READ OWNER_EXECUTE GROUP_WRITE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_WRITE WORLD_EXECUTE)

# Images
install(FILES  ${IMAGE_PATH}/FrontRight.png 
               ${IMAGE_PATH}/FrontCenter.png 
               ${IMAGE_PATH}/FrontLeft.png 
               ${IMAGE_PATH}/Right.png 
               ${IMAGE_PATH}/Rear.png 
               ${IMAGE_PATH}/Left.png 
               ${IMAGE_PATH}/Quad.png DESTINATION "/opt/gva/hmi/images")

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
