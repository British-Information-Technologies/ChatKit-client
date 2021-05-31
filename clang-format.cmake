
file(GLOB_RECURSE ALL_SOURCE_FILES *.cc *.h)

add_custom_target(
        clangformat
        COMMAND /usr/bin/clang-format
        -style=Google
        -i
        ${ALL_SOURCE_FILES}
)
