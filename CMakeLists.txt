cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(Varak LANGUAGES CXX)

# ---- Checks ----
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose debug or release" FORCE)
endif()

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
    message(
        FATAL_ERROR
        "In-source builds not allowed. Please make a 'build/' directory and run 'cmake ../' from there."
    )
endif()

# ---- Conan Setup ----

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)

# do some hacking with imgui until docking gets merched into main
add_subdirectory(cmake/imgui)
set(CONAN_INCLUDE_DIRS ${CONAN_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/cmake/imgui/src)
set(CONAN_LIBS ${CONAN_LIBS} imgui)

set(CONAN_SYSTEM_INCLUDES "On")
conan_basic_setup()

# ---- Includes and Subdirectories ----

include(cmake/project_warnings.cmake)

add_subdirectory(targets/varak_core)

add_subdirectory(targets/varak_app)
add_subdirectory(targets/varak_event)
add_subdirectory(targets/varak_imgui)
add_subdirectory(targets/varak_renderer)
add_subdirectory(targets/varak_ecs)

add_subdirectory(targets/varak_editor)
