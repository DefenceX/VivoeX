# ------------------------------------------------------------------------------
# lttng-ust
# ------------------------------------------------------------------------------
ExternalProject_Add(
    lttngust
    GIT_REPOSITORY      https://github.com/lttng/lttng-ust
    GIT_SHALLOW         1
    CMAKE_ARGS          -DCMAKE_UNITY_BUILD=YES
    GIT_TAG             v2.13.5
    PREFIX              ${CMAKE_BINARY_DIR}/external/lttngust/prefix
    TMP_DIR             ${CMAKE_BINARY_DIR}/external/lttngust/tmp
    STAMP_DIR           ${CMAKE_BINARY_DIR}/external/lttngust/stamp
    DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/external/lttngust/download
    SOURCE_DIR          ${CMAKE_BINARY_DIR}/external/lttngust/src
    BUILD_IN_SOURCE     TRUE
    CONFIGURE_COMMAND   ./bootstrap && ./configure --disable-numa --disable-man-pages
    BUILD_COMMAND       make
    INSTALL_COMMAND     ""
    UPDATE_DISCONNECTED TRUE
    BUILD_ALWAYS        0
)
