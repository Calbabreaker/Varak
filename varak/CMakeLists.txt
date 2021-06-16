file(GLOB_RECURSE SOURCES src/*.cpp)

add_library(Varak
    ${SOURCES}
)

target_include_directories(Varak PUBLIC "src/")
target_precompile_headers(Varak PUBLIC "src/vrpch.h")

set_project_flags(Varak)

target_link_libraries(Varak PUBLIC ${CONAN_LIBS})
target_link_libraries(Varak PUBLIC stdc++fs)

target_compile_definitions(Varak PUBLIC GLFW_INCLUDE_NONE)
target_compile_definitions(Varak PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLAD)

target_compile_definitions(Varak PUBLIC "$<$<CONFIG:DEBUG>:VR_DEBUG>")
target_compile_definitions(Varak PUBLIC "$<$<CONFIG:RELEASE>:VR_RELEASE>")
