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
  include(scripts/cmake/pistache.cmake)
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
# include(scripts/cmake/libao.cmake)
include(scripts/cmake/alsa.cmake)
include(scripts/cmake/libsndfile.cmake)
include(scripts/cmake/portaudio.cmake)
include(scripts/cmake/osmscout.cmake)
# include(scripts/cmake/lttng.cmake)
include(scripts/cmake/nmea.cmake)
include(scripts/cmake/protobuf.cmake)
include(scripts/cmake/sonar.cmake)
include(scripts/cmake/mediax.cmake)
include(scripts/cmake/windows.cmake)

# Git shooks setup
execute_process(COMMAND git config --local include.path ${CMAKE_SOURCE_DIR}/.gitconfig)

## Update the version number everytime cmake is run, patch number can go up a lot
execute_process(COMMAND ../update.sh)

# add_subdirectory(dds)
add_subdirectory(test)
add_subdirectory(src)

include(scripts/cmake/install.cmake)

aux_source_directory(${CMAKE_SOURCE_DIR}/src src)

# include CMake module
include(scripts/cmake/cpplint.cmake)

# add all source code directories
cpplint_add_subdirectory(src)

# Setup tests
enable_testing()
add_test(NAME HMI_Tests COMMAND tests --gtest_output=xml:./test-results/hello_test.xml)

# Uninstall target
if(NOT TARGET uninstall)
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/scripts/cmake/uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

  add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
endif()
