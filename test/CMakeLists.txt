enable_testing()

find_package(Protobuf REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
pkg_check_modules(CAIRO REQUIRED cairo)
pkg_check_modules(PANGO REQUIRED pango)
pkg_check_modules(SWSCALE REQUIRED libswscale)

set(CMAKE_CXX_FLAGS --coverage) 

add_executable(
  test_log
  test_log.cc
)

set(
  TEST_LOG_SOURCES
  ${CMAKE_SOURCE_DIR}/hmi-display/common/log_gva.cc
)

target_link_libraries(
  test_log
  GTest::gtest_main
  ${GTK3_LIBRARIES}
  ${TEST_LOG_SOURCES}
)

target_include_directories(
  test_log PUBLIC
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

include(GoogleTest)
gtest_discover_tests(test_log)