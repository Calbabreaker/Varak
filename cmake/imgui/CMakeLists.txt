add_library(imgui 
    src/imgui_demo.cpp 
    src/imgui_draw.cpp 
    src/imgui_tables.cpp 
    src/imgui_widgets.cpp
    src/imgui.cpp
)

# temporary until imgui docking is availiable in conan
target_include_directories(imgui SYSTEM INTERFACE src/)
