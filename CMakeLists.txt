cmake_minimum_required(VERSION 3.0…3.16)
project(vivoe-lite)
add_custom_target(vivoe-lite)
add_dependencies(vivoe-lite hmi-display)

include(scripts/cmake/CMakeGraphVizOptions.cmake)
include(scripts/cmake/version.cmake)
include(scripts/cmake/dds.cmake)
include(scripts/cmake/cpp.cmake)
include(scripts/cmake/cpack.cmake)
include(scripts/cmake/cairo.cmake)
include(scripts/cmake/doxygen.cmake)
include(scripts/cmake/dot.cmake)
include(scripts/cmake/googletest.cmake)
include(scripts/cmake/geographic.cmake)
include(scripts/cmake/osmscout.cmake)
include(scripts/cmake/nema.cmake)
include(scripts/cmake/vivoe-media-framework.cmake)

## Update the version number everytime cmake is run, patch number can go up a lot
execute_process(COMMAND ../update.sh)

# add_subdirectory(dds)
add_subdirectory(test)
add_subdirectory(video)
add_subdirectory(hmi-display)

## Here you can set the default 'dummy' camera feed images
#set(IMAGE_PATH ${CMAKE_SOURCE_DIR}/images/uk)
set(IMAGE_PATH ${CMAKE_SOURCE_DIR}/images/au)

# Install DDS
file(GLOB_RECURSE DDS_LIBS ${CMAKE_BINARY_DIR}/external/install/usr/local/libcyclone*.so*)
# Install binaries with external libs
file(WRITE ${CMAKE_BINARY_DIR}/gva.log "")
install(FILES ${CMAKE_BINARY_DIR}/gva.log DESTINATION "/var/log" PERMISSIONS OWNER_WRITE OWNER_READ GROUP_WRITE GROUP_READ WORLD_READ WORLD_WRITE)
install(FILES ${CMAKE_BINARY_DIR}/external/vivoe-media-framework/build/libvivoe-media.so DESTINATION "/opt/gva/libs")
install(FILES ${CMAKE_BINARY_DIR}/etc/ld.so.conf.d/vivoe-lite.conf DESTINATION "/etc/ld.so.conf.d") 
install(FILES ${CMAKE_BINARY_DIR}/etc/profile.d/vivoe-lite.sh DESTINATION "/etc/profile.d")
install(FILES ${CMAKE_BINARY_DIR}/external/libnmea/build/src/libnmealib.so 
              ${CMAKE_BINARY_DIR}/external/install/usr/local/lib/libvivoe-media.so
              ${CMAKE_BINARY_DIR}/external/install/usr/local/lib/libvivoe-media.so.1
              ${CMAKE_BINARY_DIR}/external/install/usr/local/lib/libGeographicLib.so
              ${CMAKE_BINARY_DIR}/external/install/usr/local/lib/libGeographicLib.so.23
              ${CMAKE_BINARY_DIR}/external/install/usr/local/lib/libGeographicLib.so.23.1.0
              ${CMAKE_BINARY_DIR}/external/install/usr/local/lib/libosmscout_import.so 
              ${CMAKE_BINARY_DIR}/external/install/usr/local/lib/libosmscout_import.so.1.1.1
              ${CMAKE_BINARY_DIR}/external/install/usr/local/lib/libosmscout_map_cairo.so
              ${CMAKE_BINARY_DIR}/external/install/usr/local/lib/libosmscout_map_cairo.so.1.1.1
              ${CMAKE_BINARY_DIR}/external/install/usr/local/lib/libosmscout_map.so
              ${CMAKE_BINARY_DIR}/external/install/usr/local/lib/libosmscout_map.so.1.1.1
              ${CMAKE_BINARY_DIR}/external/install/usr/local/lib/libosmscout.so
              ${CMAKE_BINARY_DIR}/external/install/usr/local/lib/libosmscout.so.1.1.1
              # ${CMAKE_BINARY_DIR}/external/install/opt/cairo/lib/lib/
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
