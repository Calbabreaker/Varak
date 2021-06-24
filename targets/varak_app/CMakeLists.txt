add_library(VarakApp
    src/application.cpp 
    src/layer_stack.cpp
    src/input.cpp
)

set_project_warnings(VarakApp)
target_include_directories(VarakApp PRIVATE "src/")
target_include_directories(VarakApp INTERFACE "./")
target_precompile_headers(VarakApp REUSE_FROM VarakCore)
target_link_libraries(VarakApp
    VarakCore VarakEvent VarakWindow VarakRenderer 
)

