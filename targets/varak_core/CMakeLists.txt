add_library(VarakCore 
    src/log.cpp
)

target_warnings(VarakCore PUBLIC)
target_compile_features(VarakCore PUBLIC cxx_std_17)
target_include_directories(VarakCore PRIVATE "src/")
target_include_directories(VarakCore INTERFACE "./")
target_precompile_headers(VarakCore PRIVATE "src/vrpch.h")

target_link_libraries(VarakCore 
    CONAN_PKG::spdlog rttr_core
)

# Debug Mode will define VR_DEBUG and Release Mode will define VR_RELEASE
target_compile_definitions(VarakCore PUBLIC "$<$<CONFIG:DEBUG>:VR_DEBUG>")
target_compile_definitions(VarakCore PUBLIC "$<$<CONFIG:RELEASE>:VR_RELEASE>")

target_compile_definitions(VarakCore PUBLIC GLFW_INCLUDE_NONE)
