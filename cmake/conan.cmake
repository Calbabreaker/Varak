function(run_conan)
    if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
        message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
        file(DOWNLOAD "https://github.com/conan-io/cmake-conan/raw/v0.16.1/conan.cmake" "${CMAKE_BINARY_DIR}/conan.cmake")
    endif()

    set(CONAN_SYSTEM_INCLUDES "On")
    include(${CMAKE_BINARY_DIR}/conan.cmake)

    conan_cmake_run(
        REQUIRES
            entt/3.7.1
            glad/0.1.34
            glfw/3.3.4
            glm/0.9.9.8
            rttr/0.9.6
            spdlog/1.8.5
            stb/20200203

        OPTIONS 
            glad:gl_profile=core 
            glad:gl_version=4.5

        BASIC_SETUP CMAKE_TARGETS 
        BUILD missing
    )
endfunction()
