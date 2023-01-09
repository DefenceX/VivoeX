# ------------------------------------------------------------------------------
# lttng-ust
# ------------------------------------------------------------------------------
ExternalProject_Add(
    lttngust
    GIT_REPOSITORY      https://github.com/lttng/lttng-ust
    GIT_SHALLOW         1
    CMAKE_ARGS          -DCMAKE_UNITY_BUILD=YES
    GIT_TAG             master
    PREFIX              ${CMAKE_BINARY_DIR}/external/lttngust/prefix
    TMP_DIR             ${CMAKE_BINARY_DIR}/external/lttngust/tmp
    STAMP_DIR           ${CMAKE_BINARY_DIR}/external/lttngust/stamp
    DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/external/lttngust/download
    SOURCE_DIR          ${CMAKE_BINARY_DIR}/external/lttngust/src
    BINARY_DIR          ${CMAKE_BINARY_DIR}/external/lttngust/build
    CONFIGURE_COMMAND   cd ${CMAKE_BINARY_DIR}/external/lttngust/src && ./bootstrap && ./configure
    BUILD_COMMAND       make $(nproc)
    INSTALL_COMMAND     ""
    UPDATE_DISCONNECTED 1
    BUILD_ALWAYS        0
)
