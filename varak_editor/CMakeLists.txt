file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(VarakEditor
    ${SOURCES}
)

target_include_directories(VarakEditor PRIVATE "src/")
set_project_flags(VarakEditor)
target_link_libraries(VarakEditor 
    VarakScene VarakImGui VarakApp
)
