enable_testing()

include(FindPkgConfig)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
pkg_check_modules(SWSCALE REQUIRED libswscale)

set(CMAKE_CXX_FLAGS --coverage)

set(
  TEST_INCLUDES
  ${GTK3_INCLUDE_DIRS} 
  ${CAIRO_INCLUDE_DIRS} 
  ${GTEST_INCLUDE_DIRS}
  ${PANGO_INCLUDE_DIRS} 
  ${SWSCALE_INCLUDE_DIRS} 
  ${PROTOBUF_INCLUDE_DIRS}
  ${NMEA_INCLUDE_DIR}
  ${MEDIA_INCLUDE_DIR}
  ${OSMSCOUT_INCLUDE_DIRS}
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

if (MSYS)
	# Static link libraries .a
	target_link_directories(tests BEFORE PRIVATE
		"${CMAKE_BINARY_DIR}/external/install/Program Files (x86)/protobuf/lib"
		"${CMAKE_BINARY_DIR}/external/install/Program Files (x86)/gflags/lib"
		"${CMAKE_BINARY_DIR}/external/install/Program Files (x86)/glog/lib"
		"${CMAKE_BINARY_DIR}/external/install/Program Files (x86)/protobuf/lib"
		"${CMAKE_BINARY_DIR}/external/install/Program Files (x86)/libosmscout/lib"
		"${CMAKE_BINARY_DIR}/external/install/Program Files (x86)/nmea/lib"
		"${CMAKE_BINARY_DIR}/external/install/Program Files (x86)/GeographicLib/lib64"
		"${CMAKE_BINARY_DIR}/external/install/Program Files (x86)/GeographicLib/lib64"
		"${CMAKE_BINARY_DIR}/external/install/Program Files (x86)/portaudio/lib"
    "${CMAKE_BINARY_DIR}/external/install/Program Files (x86)/googletest-distribution/lib64"
		"${CMAKE_BINARY_DIR}/external/install/mingw64/lib"
    "${CMAKE_BINARY_DIR}/external/install/usr/local/lib"
	)
	target_link_libraries(tests shlwapi)
else()
  target_link_directories(tests PRIVATE 
    ${GLOG_LIBRARY_DIR} 
    ${PROTOBUF_LIBRARY_DIR} 
    ${GTEST_LIBRARY_DIRS} 
    ${PANGO_LIBARARY_DIRS})
endif()

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
  gtest_main 
  nmea 
  png 
  pthread 
  stdc++fs
  mediax 
)

target_include_directories(
  tests PUBLIC
  ${TEST_INCLUDES}
)

add_dependencies(tests config-proto googletest libglog)

include(GoogleTest)

# gtest_discover_tests(tests WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
