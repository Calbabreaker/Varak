add_library(VarakRenderer
    src/buffer.cpp
    src/camera.cpp
    src/frame_buffer.cpp
    src/renderer2d.cpp
    src/renderer_api.cpp
    src/renderer.cpp
    src/rendering_context.cpp
    src/shader.cpp
    src/texture.cpp
    src/vertex_array.cpp

    src/opengl/opengl_buffer.cpp
    src/opengl/opengl_frame_buffer.cpp
    src/opengl/opengl_renderer_api.cpp
    src/opengl/opengl_context.cpp
    src/opengl/opengl_shader.cpp
    src/opengl/opengl_texture.cpp
    src/opengl/opengl_vertex_array.cpp
)

target_include_directories(VarakRenderer PRIVATE "src/")
target_include_directories(VarakRenderer INTERFACE "./")
target_precompile_headers(VarakRenderer REUSE_FROM VarakCore)
target_link_libraries(VarakRenderer 
    VarakCore CONAN_PKG::glad CONAN_PKG::stb CONAN_PKG::glm CONAN_PKG::glfw
)
