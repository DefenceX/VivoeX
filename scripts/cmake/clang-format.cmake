## Clang format setup
add_custom_target(tidy)    
add_custom_command(
    TARGET tidy
    COMMAND find ${CMAKE_SOURCE_DIR}/hmi-display -iname *.h -o -iname *.cc | xargs clang-format --verbose -i --style=${CODE_STYLE}
    COMMAND find ${CMAKE_SOURCE_DIR}/test -iname *.h -o -iname *.cc | xargs clang-format --verbose -i --style=${CODE_STYLE}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})