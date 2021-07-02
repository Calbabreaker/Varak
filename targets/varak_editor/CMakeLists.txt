add_executable(VarakEditor
    src/editor_layer.cpp
    src/varak_editor_app.cpp
    src/panels/scene_hierarchy_panel.cpp
    src/panels/inspector_panel/inspector_panel_entity.cpp
    src/panels/inspector_panel/inspector_panel.cpp
)

target_include_directories(VarakEditor PRIVATE "src/")
target_precompile_headers(VarakEditor REUSE_FROM VarakCore)
target_link_libraries(VarakEditor 
    VarakECS VarakImGui VarakApp 
)
