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
target_link_libraries(tests 
  hmiupdater 
  hmiaudio
  widgets 
  hmicore 
  pthread
  ${CAIRO_LIBRARIES} 
  ${GEOGRAPHIC_LIBRARIES} 
	${GFLAGS_LIBS} 
	${GTK3_LIBRARIES}
	${OSMSCOUT_LIBARAIES} 
	${PANGO_LIBRARIES} 
	${PORTAUDIO_LIBRARIES}
	${PROTOBUF_LIBRARY} 
	${SNDFILE_LIBRARIES}
	${SWSCALE_LIBRARIES} 
	${WINDOWS_RESOURCE_LIB} 
	GeographicLib 
	config-proto 
	glog 
  gtest
	hmivideo 
	nmea 
	png 
	pthread 
	stdc++fs
	vivoe-media 
)

include(GoogleTest)
gtest_discover_tests(tests WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
