file(GLOB_RECURSE VARAK_SOURCES src/*.cpp)

add_library(varak ${VARAK_SOURCES})

target_link_libraries(varak PUBLIC entt imgui glfw glm rttr spdlog PRIVATE glad stb)

target_include_directories(varak PUBLIC include)
target_compile_features(varak PRIVATE cxx_std_17)
target_precompile_headers(varak PRIVATE include/varak/pch.h)

target_compile_definitions(varak PUBLIC GLFW_INCLUDE_NONE)
target_compile_definitions(varak PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLAD)

target_compile_definitions(varak PUBLIC "$<$<CONFIG:DEBUG>:VR_DEBUG>")
target_compile_definitions(varak PUBLIC "$<$<CONFIG:RELEASE>:VR_RELEASE>")
