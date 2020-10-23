file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(Sandbox ${SOURCES})

target_link_libraries(Sandbox Varak)