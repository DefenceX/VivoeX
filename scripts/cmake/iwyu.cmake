include(ExternalProject)

message (STATUS "Added include-what-you-use to external submodules")

# ------------------------------------------------------------------------------
# include-what-you-use
# ------------------------------------------------------------------------------
ExternalProject_Add(
    include-what-you-use
    GIT_REPOSITORY      https://github.com/include-what-you-use/include-what-you-use.git
    GIT_SHALLOW         1
    GIT_TAG             clang_12
    CMAKE_ARGS          -DCMAKE_INSTALL_MESSAGE=LAZY -DCMAKE_PREFIX_PATH=/usr/lib/llvm-12
    PREFIX              ${CMAKE_BINARY_DIR}/external/include-what-you-use/prefix
    TMP_DIR             ${CMAKE_BINARY_DIR}/external/include-what-you-use/tmp
    STAMP_DIR           ${CMAKE_BINARY_DIR}/external/include-what-you-use/stamp
    DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/external/include-what-you-use/download
    SOURCE_DIR          ${CMAKE_BINARY_DIR}/external/include-what-you-use/src
    BINARY_DIR          ${CMAKE_BINARY_DIR}/external/include-what-you-use/build
    INSTALL_COMMAND     make DESTDIR=${CMAKE_BINARY_DIR}/external/install install 
    UPDATE_DISCONNECTED 1
    BUILD_ALWAYS        0
)

if (EXISTS  ${CMAKE_BINARY_DIR}/external/install/usr/local/bin/include-what-you-use)
    set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE ${CMAKE_BINARY_DIR}/external/install/usr/local/bin/include-what-you-use)
    if (CMAKE_CXX_INCLUDE_WHAT_YOU_USE)
        list(
            APPEND CMAKE_CXX_INCLUDE_WHAT_YOU_USE 
                "-Xiwyu"
                "--max_line_length=120"
        )
    endif()
endif()