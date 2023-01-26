

# ------------------------------------------------------------------------------
# protobuf
# ------------------------------------------------------------------------------
ExternalProject_Add(
    protobuf
    GIT_REPOSITORY      https://github.com/protocolbuffers/protobuf
    GIT_SHALLOW         1
    CMAKE_ARGS          -DCMAKE_UNITY_BUILD=YES
    GIT_TAG             main
    PREFIX              ${CMAKE_BINARY_DIR}/external/protobuf/prefix
    TMP_DIR             ${CMAKE_BINARY_DIR}/external/protobuf/tmp
    STAMP_DIR           ${CMAKE_BINARY_DIR}/external/protobuf/stamp
    DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/external/protobuf/download
    SOURCE_DIR          ${CMAKE_BINARY_DIR}/external/protobuf/src
    BINARY_DIR          ${CMAKE_BINARY_DIR}/external/protobuf/build
    INSTALL_COMMAND     make DESTDIR=${CMAKE_BINARY_DIR}/external/install install
    UPDATE_DISCONNECTED 1
    BUILD_ALWAYS        0
)