# Set the output folder where your program will be created
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(FLASH_DIRECTORY ${CMAKE_BINARY_DIR}/images)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_COMPILER_WORKS 1)
set(CMAKE_INSTALL_MESSAGE LAZY)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES ${CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES})
set(MESSAGE_QUIET ON)
set(CODE_STYLE "{BasedOnStyle: Google, ColumnLimit: 120}")

if (MSYS)
  set(MSYS_FLAGS "-L/mingw64/lib -static-libstdc++ -D_POSIX_C_SOURCE")
endif()

if($ENV{CI})
  message(STATUS "Running CI so flags for production builds")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MSYS_FLAGS} -lstdc++fs -O3")
else()
  message(STATUS "Running locally so optimised CFLAGS for checking")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MSYS_FLAGS} -lstdc++fs -Wall -Werror")
endif()

option(TRACE "Build with trace" OFF)

if(TRACE)
  message(STATUS "Tracing of functions enabled for lttng")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MSYS_FLAGS} -g -finstrument-functions") 
endif()