enable_testing()

find_package(Protobuf REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
pkg_check_modules(CAIRO REQUIRED cairo)
pkg_check_modules(PANGO REQUIRED pango)
pkg_check_modules(SWSCALE REQUIRED libswscale)

set(CMAKE_CXX_FLAGS --coverage)

set(
  TEST_INCLUDES
  ${GTK3_INCLUDE_DIRS} 
  ${CAIRO_INCLUDE_DIRS} 
  ${PANGO_INCLUDE_DIRS} 
  ${SWSCALE_INCLUDE_DIRS} 
  ${Protobuf_INCLUDE_DIRS}
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
)

## test_log

set(
  TEST_LOG_SOURCES
  ${CMAKE_SOURCE_DIR}/hmi-display/common/log_gva.cc
)

add_executable(
  test_log
  test_log.cc
  ${TEST_LOG_SOURCES}

)

target_link_libraries(
  test_log
  ${GTEST_LIBARAIES}
  ${TEST_LIBS}
)

target_link_directories(test_log PRIVATE ${GTEST_LIBRARY_DIRS})

target_include_directories(
  test_log PUBLIC
  ${TEST_INCLUDES}
  ${GTEST_INCLUDE_DIRS}
)

add_dependencies(test_log config-proto)

## test-hmi
add_executable(
  test_hmi
  test_hmi.cc
)

target_link_libraries(
  test_hmi
  ${GTEST_LIBARAIES}
  ${TEST_LIBS}
)

target_link_directories(test_hmi PRIVATE ${GTEST_LIBRARY_DIRS})

target_include_directories(test_hmi PUBLIC
  ${TEST_INCLUDES}
  ${GTEST_INCLUDE_DIRS}
)

add_dependencies(test_hmi config-proto googletest)

include(GoogleTest)

gtest_discover_tests(test_hmi WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
gtest_discover_tests(test_log WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})