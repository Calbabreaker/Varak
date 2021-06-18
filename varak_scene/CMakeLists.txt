add_library(VarakScene
    src/entity.cpp
    src/scene.cpp
    src/editor_camera.cpp
)

set_project_flags(VarakScene)
target_include_directories(VarakScene PRIVATE "src/")
target_include_directories(VarakScene INTERFACE "./")
target_precompile_headers(VarakScene REUSE_FROM VarakCore)
target_link_libraries(VarakScene
    VarakRenderer VarakApp 
)
