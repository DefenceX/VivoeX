set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if($ENV{CI})
  message(STATUS "Running CI so flags for production builds")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lstdc++fs -O3")
else()
  message(STATUS "Running locally so optimised CFLAGS for checking")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lstdc++fs -Wall -Werror")
endif()

option(TRACE "Build with trace" OFF)

if(TRACE)
  message(STATUS "Tracing of functions enabled for lttng")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -finstrument-functions") 
endif()