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
  ${CMAKE_SOURCE_DIR}/hmi-display
  ${CMAKE_SOURCE_DIR}/hmi-display/common
  ${CMAKE_SOURCE_DIR}/hmi-display/src
  ${CMAKE_SOURCE_DIR}/hmi-display/src/states
  ${CMAKE_SOURCE_DIR}/hmi-display/src/widgets
  ${CMAKE_SOURCE_DIR}/hmi-display/src/common
  ${CMAKE_BINARY_DIR}/hmi-display/config
)

set(
  TEST_LIBS 
  ${GTK3_LIBRARIES}
  ${PANGO_LIBRARIES}
)

## test_log

set(
  TEST_LOG_SOURCES
)

add_executable(
  test_log
  test_log.cc
  ${TEST_LOG_SOURCES}

)

target_link_directories(test_log PRIVATE ${GTEST_LIBRARY_DIRS} ${PANGO_LIBARARY_DIRS})

target_link_libraries(
  test_log
  ${GLOG_LIBRARY}
  ${GTEST_LIBARAIES}
  ${TEST_LIBS}
)

target_include_directories(
  test_log PUBLIC
  ${TEST_INCLUDES}
  ${GTEST_INCLUDE_DIRS}
)

add_dependencies(test_log config-proto googletest libglog)

## test-hmi
add_executable(
  test_hmi
  test_hmi.cc
)

target_link_libraries(
  test_hmi
  ${GLOG_LIBRARY}
  ${GTEST_LIBARAIES}
  ${TEST_LIBS}
)

target_link_directories(test_hmi PRIVATE ${GTEST_LIBRARY_DIRS})

target_include_directories(test_hmi PUBLIC
  ${TEST_INCLUDES}
  ${GTEST_INCLUDE_DIRS}
)

add_dependencies(test_hmi config-proto googletest libglog)

include(GoogleTest)

gtest_discover_tests(test_hmi WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
gtest_discover_tests(test_log WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})