cmake_minimum_required(VERSION 3.0…3.16)
project(vivoe-lite)
add_custom_target(vivoe-lite)
add_dependencies(vivoe-lite hmi-display)

include(scripts/cmake/version.cmake) # Always include this first
include(scripts/cmake/cpp.cmake)     # Always include this second
include(scripts/cmake/cpack.cmake)
include(scripts/cmake/CMakeGraphVizOptions.cmake)
if(NOT MSYS)
  include(scripts/cmake/dds.cmake)
endif()
include(scripts/cmake/clang-format.cmake)
# include(scripts/cmake/cairo.cmake)
# include(scripts/cmake/pango.cmake)
include(scripts/cmake/doxygen.cmake)
include(scripts/cmake/dot.cmake)
include(scripts/cmake/gflags.cmake)
include(scripts/cmake/glog.cmake)
include(scripts/cmake/googletest.cmake)
include(scripts/cmake/geographic.cmake)
include(scripts/cmake/osmscout.cmake)
# include(scripts/cmake/lttng.cmake)
include(scripts/cmake/nema.cmake)
include(scripts/cmake/protobuf.cmake)
include(scripts/cmake/sonar.cmake)
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


if (MSYS)
  install(TARGETS hmi-display)
  file(GLOB_RECURSE OSMSCOUT_DLL "${CMAKE_BINARY_DIR}/external/install/Program Files (x86)/libosmscout/bin/*.dll")
  install(FILES ${OSMSCOUT_DLL} DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
  install(FILES "${CMAKE_BINARY_DIR}/external/install/Program Files (x86)/GeographicLib/bin/libGeographicLib.dll" DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
  install(FILES "${CMAKE_BINARY_DIR}/external/install/usr/local/lib/libvivoe-media.dll" DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
  install(FILES "${CMAKE_BINARY_DIR}/external/install/Program Files (x86)/glog/bin/libglog.dll" DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
  # install(FILES "${CMAKE_BINARY_DIR}/external/install/Program Files (x86)/gflag/bin/libgflag.dll" DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
  ## MSYS libs now
  install(FILES 
    C:/msys64/mingw64/bin/libcairo-2.dll
    C:/msys64/mingw64/bin/libgcc_s_seh-1.dll
    C:/msys64/mingw64/bin/libgtk-3-0.dll
    C:/msys64/mingw64/bin/libglib-2.0-0.dll
    C:/msys64/mingw64/bin/libgio-2.0-0.dll
    C:/msys64/mingw64/bin/libgobject-2.0-0.dll
    C:/msys64/mingw64/bin/libgdk-3-0.dll
    C:/msys64/mingw64/bin/libstdc++-6.dll
    C:/msys64/mingw64/bin/libwinpthread-1.dll
    C:/msys64/mingw64/bin/libpango-1.0-0.dll
    C:/msys64/mingw64/bin/libpangocairo-1.0-0.dll
    C:/msys64/mingw64/bin/libiconv-2.dll
    C:/msys64/mingw64/bin/libpng16-16.dll
    C:/msys64/mingw64/bin/libintl-8.dll
    C:/msys64/mingw64/bin/swscale-5.dll
    C:/msys64/mingw64/bin/libprotobuf.dll
    C:/msys64/mingw64/bin/zlib1.dll
    C:/msys64/mingw64/bin/libfreetype-6.dll
    C:/msys64/mingw64/bin/libfontconfig-1.dll
    C:/msys64/mingw64/bin/libpixman-1-0.dll
    C:/msys64/mingw64/bin/libepoxy-0.dll
    C:/msys64/mingw64/bin/libcairo-gobject-2.dll
    C:/msys64/mingw64/bin/libgdk_pixbuf-2.0-0.dll
    C:/msys64/mingw64/bin/libfribidi-0.dll
    C:/msys64/mingw64/bin/libgmodule-2.0-0.dll
    C:/msys64/mingw64/bin/libpcre2-8-0.dll
    C:/msys64/mingw64/bin/libffi-8.dll
    C:/msys64/mingw64/bin/libpangowin32-1.0-0.dll
    C:/msys64/mingw64/bin/libatk-1.0-0.dll
    C:/msys64/mingw64/bin/libharfbuzz-0.dll
    C:/msys64/mingw64/bin/libthai-0.dll
    C:/msys64/mingw64/bin/avutil-56.dll
    C:/msys64/mingw64/bin/libpangoft2-1.0-0.dll
    C:/msys64/mingw64/bin/libgflags.dll
    C:/msys64/mingw64/bin/libbrotlidec.dll
    C:/msys64/mingw64/bin/libbz2-1.dll
    C:/msys64/mingw64/bin/libexpat-1.dll
    C:/msys64/mingw64/bin/libmfx-1.dll
    C:/msys64/mingw64/bin/libgraphite2.dll
    C:/msys64/mingw64/bin/libdatrie-1.dll
    C:/msys64/mingw64/bin/libbrotlicommon.dll
  DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
else()
  install(TARGETS hmi-display DESTINATION /opt/gva/hmi)

  # Install DDS
  file(GLOB_RECURSE DDS_LIBS ${CMAKE_BINARY_DIR}/external/install/usr/local/libcyclone*.so*)
  # Install binaries with external libs
  file(WRITE ${CMAKE_BINARY_DIR}/gva.log "")
  install(FILES ${CMAKE_BINARY_DIR}/gva.log DESTINATION "/var/log" PERMISSIONS OWNER_WRITE OWNER_READ GROUP_WRITE GROUP_READ WORLD_READ WORLD_WRITE)
  install(FILES ${CMAKE_BINARY_DIR}/external/vivoe-media-framework/build/libvivoe-media.so DESTINATION "/opt/gva/libs")
  install(FILES ${CMAKE_BINARY_DIR}/etc/ld.so.conf.d/vivoe-lite.conf DESTINATION "/etc/ld.so.conf.d") 
  install(FILES ${CMAKE_BINARY_DIR}/etc/profile.d/vivoe-lite.sh DESTINATION "/etc/profile.d")
  install(FILES  
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
                # ${CMAKE_BINARY_DIR}/external/install/lib/${ARCH}-linux-gnu/libpango-1.0.so
                # ${CMAKE_BINARY_DIR}/external/install/lib/${ARCH}-linux-gnu/libpangocairo-1.0.so
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
endif()

aux_source_directory(${CMAKE_SOURCE_DIR}/src src)

# include CMake module
include(scripts/cmake/cpplint.cmake)

# add all source code directories
cpplint_add_subdirectory(hmi-display)
cpplint_add_subdirectory(video)

# Setup tests
enable_testing()
add_test(NAME HMI_Tests COMMAND test_hmi --gtest_output=xml:./test-results/hello_test.xml)

# Uninstall target
if(NOT TARGET uninstall)
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/scripts/cmake/uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

  add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
endif()
