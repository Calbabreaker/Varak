add_library(VarakApp
    src/application.cpp 
    src/layer_stack.cpp
)

set_project_flags(VarakApp)
target_link_libraries(VarakApp
    VarakCore VarakEvent VarakWindow VarakRenderer glm
)

target_include_directories(VarakApp PRIVATE "src/")
target_include_directories(VarakApp INTERFACE "./")
