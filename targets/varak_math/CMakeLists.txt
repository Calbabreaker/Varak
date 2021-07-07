add_library(VarakMath
    src/camera.cpp
)

target_include_directories(VarakMath PRIVATE "src/")
target_include_directories(VarakMath INTERFACE "./")
target_precompile_headers(VarakMath REUSE_FROM VarakCore)
target_link_libraries(VarakMath
    VarakCore CONAN_PKG::glm 
)
