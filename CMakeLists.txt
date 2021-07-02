cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(Varak LANGUAGES CXX)

include(cmake/conan.cmake)
include(cmake/project_settings.cmake)
include(cmake/target_warnings.cmake)

run_conan()
message(STATUS packages: ${CONAN_PKGS})


# ---- Subdirectories ----

# these definitions prevent pch to be used so we undefine them
add_compile_options(-U_BSD_SOURCE -U_DEFAULT_SOURCE)

add_subdirectory(cmake/imgui)

add_subdirectory(targets/varak_core)

add_subdirectory(targets/varak_app)
add_subdirectory(targets/varak_event)
add_subdirectory(targets/varak_imgui)
add_subdirectory(targets/varak_renderer)
add_subdirectory(targets/varak_ecs)

add_subdirectory(targets/varak_editor)
