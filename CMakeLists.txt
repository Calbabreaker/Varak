cmake_minimum_required(VERSION 3.16)
project(Varak)

# ---- Checks ----
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose debug or release" FORCE)
endif()

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
    message(
        FATAL_ERROR
        "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there."
    )
endif()

# ---- Conan Setup ----

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)

# do some hacking with imgui until docking gets merched into main
add_subdirectory(cmake/imgui)
set(CONAN_INCLUDE_DIRS ${CONAN_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/cmake/imgui/src)
set(CONAN_LIBS ${CONAN_LIBS} ImGui)

set(CONAN_SYSTEM_INCLUDES "On")
conan_basic_setup()

# ---- Includes and Subdirectories ----

include(cmake/project_flags.cmake)

add_subdirectory(varak)
add_subdirectory(varak_editor)
