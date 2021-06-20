add_library(VarakWindow
    src/window.cpp
)

set_project_warnings(VarakWindow)
target_include_directories(VarakWindow PRIVATE "src/")
target_include_directories(VarakWindow INTERFACE "./")
target_precompile_headers(VarakWindow REUSE_FROM VarakCore)
target_link_libraries(VarakWindow 
    VarakEvent VarakCore VarakRenderer 
)

