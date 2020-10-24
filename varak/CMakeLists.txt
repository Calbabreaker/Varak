file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp" "src/*.h")

add_library(Varak STATIC ${SOURCES})

target_include_directories(Varak PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")

# 3rd party libraries

target_include_directories(Varak PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/vendor/spdlog/include")

# configuration

target_compile_definitions(Varak PUBLIC "$<$<CONFIG:DEBUG>:VR_DEBUG>")
target_compile_definitions(Varak PUBLIC "$<$<CONFIG:RELEASE>:VR_RELEASE>")
target_compile_definitions(Varak PUBLIC "$<$<CONFIG:DIST>:VR_DIST>")