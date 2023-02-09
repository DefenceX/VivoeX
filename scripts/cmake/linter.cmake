

set(CODE_STYLE "{BasedOnStyle: Google, ColumnLimit: 120}")
include (CTest)

# CPP lint setup (Google Codeing standard)
set(CMAKE_CXX_CPPLINT cpplint)
if (CMAKE_CXX_CPPLINT)
    list(
        APPEND CMAKE_CXX_CPPLINT 
            "--exclude=${CMAKE_SOURCE_DIR}/examples/demo/src"
            "--linelength=120"
            "--quiet"
    )
endif()

## Valgring setup
set(CTEST_MEMORYCHECK_COMMAND, valgrind)
set(CTEST_MEMORYCHECK_COMMAND_OPTIONS, "--trace-children=yes --leak-check=full")

## Clang format setup
add_custom_target(tidy)    
add_custom_command(
    TARGET tidy
    COMMAND find ${CMAKE_SOURCE_DIR}/src -iname *.h -o -iname *.cc | xargs clang-format --verbose -i --style=${CODE_STYLE}
    COMMAND find ${CMAKE_SOURCE_DIR}/examples -iname *.h -o -iname *.cc | xargs clang-format --verbose -i --style=${CODE_STYLE}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

## Clang Tidy setup (issue on ARM builds using gcc 9.1.0, disabling for now)
if (NOT CMAKE_TOOLCHAIN_FILE)
  find_program(CMAKE_CXX_CLANG_TIDY NAMES clang-tidy)
  set(CMAKE_CXX_CLANG_TIDY clang-tidy )
  if (CMAKE_CXX_CLANG_TIDY)
      list(
          APPEND CMAKE_CXX_CLANG_TIDY 
              "--checks=*"
              "-p=${CMAKE_BINARY_DIR}"
              "--config-file=${CMAKE_SOURCE_DIR}/scripts/linter_configs/.clang_tidy"
              ## Below defines lines to lint (not exclude)
              "--line-filter=[{\"name\":\"gtest-all.cc\",\"lines\":[[1,1]]},{\"name\":\"statx.h\",\"lines\":[[9999,9999]]}]"
              "--quiet"
              "--format-style=${CODE_STYLE}"
              "-extra-arg=-I${CMAKE_BINARY_DIR}/external/install/usr/local/include"
              "-extra-arg=-I${CMAKE_SOURCE_DIR}/sigmastar/sdk/verify/mi_demo/source/internal/opencv/include/opencv4"
      )
  endif()
endif()

# CPP Check setup
set(CMAKE_CXX_CPPCHECK cppcheck)
if (CMAKE_CXX_CPPCHECK)
    list(
        APPEND CMAKE_CXX_CPPCHECK 
            "--project=${CMAKE_BINARY_DIR}/compile_commands.json"
            "--enable=warning"
            "--cppcheck-build-dir=${CMAKE_BINARY_DIR}/cppcheck"
            # "--inconclusive"
            # "--force" 
            # "--inline-suppr"
            "--std=c++20"
            "--quiet"
            # "--dump"
            "--suppressions-list=${CMAKE_SOURCE_DIR}/scripts/linter_configs/suppressions.txt"
    )
endif()
# Make the cppcheck hash directory if it does not already exist
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/cppcheck)

## This is a bit of a hack to get rid of the dump files created above by CPPCHECK. Ideally these would be created in 
## the build directory and not in source.
add_custom_target(lint_tidy)    
add_custom_command(TARGET lint_tidy
                   POST_BUILD
                   COMMAND find . -name "*.dump" -type f -delete
                   COMMAND find . -name "*.ctu-info" -type f -delete
                   WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
add_dependencies(lint_tidy sentinel_vision)

if(TRACE)
  set(TRACE_OPTS "-DTRACE=1")
endif()

# Defaults
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Dlinux=1 -D_FORTIFY_SOURCE=2 -D_GLIBCXX_ASSERTIONS ${TRACE_OPTS} -fpic  -fstack-clash-protection -fstack-protector-all -g -O2 -Wall -pipe -Werror=format-security -Werror -Wl,-z,defs -Wl,-z,now -Wl,-z,relro")