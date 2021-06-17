add_library(VarakWindow
    src/window.cpp
)

set_project_flags(VarakWindow)
target_include_directories(VarakWindow PRIVATE "src/")
target_include_directories(VarakWindow INTERFACE "./")
target_link_libraries(VarakWindow 
    VarakEvent VarakCore VarakRenderer glfw
)

