enable_testing()
include(FindPkgConfig)

pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
pkg_check_modules(SWSCALE REQUIRED libswscale)

set(CMAKE_CXX_FLAGS --coverage)

include_directories(
  ${CMAKE_SOURCE_DIR}/hmi-display
  ${CAIRO_INCLUDE_DIRS}
  ${CMAKE_BINARY_DIR}/external/install/usr/local/include/
  ${CMAKE_BINARY_DIR}/external/libnmea/src/include
  ${CMAKE_BINARY_DIR}/external/vivoe-media-framework/src
  ${CMAKE_BINARY_DIR}/hmi-display/config
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/hmi-display
  ${CMAKE_SOURCE_DIR}/src
  ${GLOG_INCLUDE_DIRS}
  ${GTEST_INCLUDE_DIRS}
  ${GTK3_INCLUDE_DIRS}
  ${PANGO_INCLUDE_DIRS}
  ${PROTOBUF_INCLUDE_DIRS}
  ${SWSCALE_INCLUDE_DIRS}
  ${TEST_INCLUDES}
)

add_executable(tests
  test_log.cc
  test_config.cc
  test_updater.cc
)

target_link_libraries(tests
  hmi-updater png pthread hmi-video vivoe-media nmea
  ${PORTAUDIO_LIBRARIES} ${SNDFILE_LIBRARIES} pthread glog widgets
  GeographicLib config-proto stdc++fs ${OSMSCOUT_LIBARAIES}
  ${PROTOBUF_LIBRARY} ${GTK_LIBRARIES3} ${GFLAGS_LIBS}
  ${CAIRO_LIBRARIES} ${PANGO_LIBRARIES} ${SWSCALE_LIBRARIES}
  ${GTK3_LIBRARIES} ${GEOGRAPHIC_LIBRARIES} ${WINDOWS_RESOURCE_LIB}
)
target_link_directories(tests BEFORE PRIVATE
  ${CMAKE_BINARY_DIR}/external/libnmea/build/src
  ${CMAKE_BINARY_DIR}/external/libprotobuf/build
  ${CMAKE_BINARY_DIR}/external/vivoe-media-framework/build
  ${GLOG_LIBRARY_DIR}
  ${GTEST_LIBRARY_DIRS}
  ${PANGO_LIBARARY_DIRS}
  ${CAIRO_LIBARARY_DIRS}
  ${PROTOBUF_LIBRARY_DIR}
)

add_dependencies(tests config-proto googletest libglog)
target_link_libraries(tests hmicore)
target_include_directories(tests BEFORE PRIVATE
  ${CMAKE_SOURCE_DIR}/hmi-display
  ${CMAKE_BINARY_DIR}/external/install/usr/local/include
  ${CMAKE_BINARY_DIR}/external/libprotobuf/build
  ${GLOG_INCLUDE_DIRS} 
  ${PROTOBUF_INCLUDE_DIRS} 
  ${GTEST_INCLUDE_DIRS}
)

target_link_directories(tests BEFORE PRIVATE
    ${CMAKE_BINARY_DIR}/external/install/usr/local/lib64/libglog.so.1
		${CMAKE_BINARY_DIR}/external/libprotobuf/build
		${GLOG_LIBRARY_DIR} 
		${PROTOBUF_LIBRARY_DIR} 
		${GTEST_LIBRARY_DIRS}
)

include(GoogleTest)
gtest_discover_tests(tests WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
