project(Varak VERSION 1.0.0)

file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.h")

add_library(Varak STATIC ${SOURCES})

target_include_directories(Varak PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_precompile_headers(Varak PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/vrpch.h")

# 3rd party libraries

# spdlog
target_include_directories(Varak PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/vendor/spdlog/include")

# glfw
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory("vendor/glfw")
target_include_directories(Varak PUBLIC "vendor/glfw/include")
target_compile_definitions(Varak PUBLIC "GLFW_INCLUDE_NONE")
target_link_libraries(Varak "glfw" "${GLFW_LIBRARIES}")

# glad
add_subdirectory("vendor/glad")
target_link_libraries(Varak Glad)

# imgui
add_subdirectory("vendor/imgui")
target_link_libraries(Varak ImGui)

# glm
target_include_directories(Varak PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/vendor/glm")

# configurations
set(CMAKE_CONFIGURATION_TYPES "Debug;Release;Dist" CACHE STRING "" FORCE) 
target_compile_definitions(Varak PUBLIC "$<$<CONFIG:DEBUG>:VR_DEBUG>")
target_compile_definitions(Varak PUBLIC "$<$<CONFIG:RELEASE>:VR_RELEASE>")
target_compile_definitions(Varak PUBLIC "$<$<CONFIG:DIST>:VR_DIST>")
