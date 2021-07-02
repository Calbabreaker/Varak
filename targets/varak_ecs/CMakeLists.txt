add_library(VarakECS
    src/components/camera_component.cpp
    src/components/transform_component.cpp

    src/editor_camera.cpp
    src/scene.cpp
    src/scene_serializer.cpp
)

target_include_directories(VarakECS PRIVATE "src/")
target_include_directories(VarakECS INTERFACE "./")
target_precompile_headers(VarakECS REUSE_FROM VarakCore)
target_link_libraries(VarakECS
    VarakRenderer VarakApp CONAN_PKG::entt
)
