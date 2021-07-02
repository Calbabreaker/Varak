add_library(ImGuiBackend
    src/imgui_impl_glfw.cpp
    src/imgui_impl_opengl3.cpp
)

target_compile_definitions(ImGuiBackend PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLAD)
target_link_libraries(ImGuiBackend
    CONAN_PKG::glad CONAN_PKG::glfw imgui
)

add_library(VarakImGui
    src/imgui_helper.cpp
    src/imgui_layer.cpp
)

target_include_directories(VarakImGui PRIVATE "src/")
target_include_directories(VarakImGui INTERFACE "./")
target_precompile_headers(VarakImGui REUSE_FROM VarakCore)
target_link_libraries(VarakImGui 
    VarakApp ImGuiBackend VarakEvent 
)

