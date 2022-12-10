# ------------------------------------------------------------------------------
# libnema
# ------------------------------------------------------------------------------
ExternalProject_Add(
    libnmea
    GIT_REPOSITORY      https://github.com/DefenceX/nmealib
    GIT_SHALLOW         1
    CMAKE_ARGS          -DCMAKE_UNITY_BUILD=YES
    GIT_TAG             main
    PREFIX              ${CMAKE_BINARY_DIR}/external/libnmea/prefix
    TMP_DIR             ${CMAKE_BINARY_DIR}/external/libnmea/tmp
    STAMP_DIR           ${CMAKE_BINARY_DIR}/external/libnmea/stamp
    DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/external/libnmea/download
    SOURCE_DIR          ${CMAKE_BINARY_DIR}/external/libnmea/src
    BINARY_DIR          ${CMAKE_BINARY_DIR}/external/libnmea/build
    BUILD_COMMAND       bash -c "make $(nproc)"
    INSTALL_COMMAND     ""
    UPDATE_DISCONNECTED 1
    BUILD_ALWAYS        0
)
