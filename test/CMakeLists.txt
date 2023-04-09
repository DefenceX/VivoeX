enable_testing()

include(FindPkgConfig)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
pkg_check_modules(SWSCALE REQUIRED libswscale)

set(CMAKE_CXX_FLAGS --coverage)

set(
  TEST_INCLUDES
  ${GTK3_INCLUDE_DIRS} 
  ${CAIRO_INCLUDE_DIRS} 
  ${PANGO_INCLUDE_DIRS} 
  ${SWSCALE_INCLUDE_DIRS} 
  ${PROTOBUF_INCLUDE_DIRS}
  ${NMEA_INCLUDE_DIR}
  ${MEDIA_INCLUDE_DIR}
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_SOURCE_DIR}/src/common
  ${CMAKE_SOURCE_DIR}/src/hmicore
  ${CMAKE_SOURCE_DIR}/src/hmicore/states
  ${CMAKE_SOURCE_DIR}/src/hmicore/widgets
  ${CMAKE_SOURCE_DIR}/src/hmicore/common
  ${CMAKE_BINARY_DIR}/src/config
)

add_executable(
  tests
  # test_hmi.cc
  test_updater.cc
  test_log.cc
  ${TEST_LOG_SOURCES}
)

target_link_directories(tests PRIVATE ${GLOG_LIBRARY_DIR} ${PROTOBUF_LIBRARY_DIR} ${GTEST_LIBRARY_DIRS} ${PANGO_LIBARARY_DIRS})

target_link_libraries(
  tests
  ${GLOG_LIBRARY}
  ${GTEST_LIBARAIES}
  ${GTK3_LIBRARIES}
  ${PANGO_LIBRARIES}
)

target_include_directories(
  tests PUBLIC
  ${TEST_INCLUDES}
  ${GTEST_INCLUDE_DIRS}
)

add_dependencies(tests config-proto googletest libglog)

include(GoogleTest)

gtest_discover_tests(tests WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
