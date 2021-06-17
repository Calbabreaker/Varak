add_library(VarakImGui
    src/imgui_helper.cpp
    src/imgui_impl_glfw.cpp
    src/imgui_impl_opengl3.cpp
    src/imgui_layer.cpp
)

set_project_flags(VarakImGui)
target_include_directories(VarakImGui PRIVATE "src/")
target_include_directories(VarakImGui INTERFACE "./")
target_link_libraries(VarakImGui 
    VarakApp VarakEvent imgui glm
)

target_compile_definitions(VarakImGui PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLAD)
