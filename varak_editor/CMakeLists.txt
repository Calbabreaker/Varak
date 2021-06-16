file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(VarakEditor
    ${SOURCES}
)

target_link_libraries(VarakEditor PRIVATE Varak)
target_include_directories(Varak PRIVATE "src/")
set_project_flags(VarakEditor)
