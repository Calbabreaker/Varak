file(GLOB_RECURSE VARAK_EDITOR_SOURCES src/*.cpp)

add_executable(varak_editor ${VARAK_EDITOR_SOURCES})

target_link_libraries(varak_editor varak)
target_precompile_headers(varak_editor REUSE_FROM varak)
