add_library(VarakScene
    src/entity.cpp
    src/scene.cpp
)

set_project_flags(VarakScene)
target_include_directories(VarakScene PRIVATE "src/")
target_include_directories(VarakScene INTERFACE "./")
target_link_libraries(VarakScene
    VarakRenderer VarakApp entt
)
