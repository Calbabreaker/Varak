add_library(VarakScene
    src/components/camera_component.cpp
    src/components/transform_component.cpp

    src/editor_camera.cpp
    src/scene.cpp
    src/scene_serializer.cpp
)

set_project_warnings(VarakScene)
target_include_directories(VarakScene PRIVATE "src/")
target_include_directories(VarakScene INTERFACE "./")
target_precompile_headers(VarakScene REUSE_FROM VarakCore)
target_link_libraries(VarakScene
    VarakRenderer VarakApp rttr_core
)
