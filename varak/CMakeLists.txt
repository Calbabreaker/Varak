file(GLOB_RECURSE SOURCES src/*.cpp)

add_library(Varak STATIC ${SOURCES})

target_include_directories(Varak PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")