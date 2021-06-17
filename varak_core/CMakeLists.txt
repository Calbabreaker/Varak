add_library(VarakCore 
    src/log.cpp
)

set_project_flags(VarakCore)
target_include_directories(VarakCore PRIVATE "src/")
target_precompile_headers(VarakCore PUBLIC "src/vrpch.h")

target_link_libraries(VarakCore stdc++fs spdlog)

# Debug Mode will define VR_DEBUG and Release Mode will define VR_RELEASE
target_compile_definitions(VarakCore PUBLIC "$<$<CONFIG:DEBUG>:VR_DEBUG>")
target_compile_definitions(VarakCore PUBLIC "$<$<CONFIG:RELEASE>:VR_RELEASE>")

target_compile_definitions(VarakCore PUBLIC GLFW_INCLUDE_NONE)
