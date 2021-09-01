find_package(Python REQUIRED)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

set(FILE "${CMAKE_CURRENT_SOURCE_DIR}/glew/include/GL/glew.h")
message(STATUS "Checking if glew is build")
if (NOT EXISTS "${FILE}")
    if(UNIX)
        message(STATUS "Building Glew")
        execute_process(COMMAND make -C ${CMAKE_CURRENT_SOURCE_DIR}/glew/auto)
    else()
        message(FATAL_ERROR "Please build GLEW first:\n"
                "1. Open Git Bash in Dependencies/glew/auto\n"
                "2. Execute mingw-32-make.exe\n"
                "3. Reload the Cmake Project")
    endif()
endif()

add_subdirectory(glfw)
add_subdirectory(glew/build/cmake)
#add_subdirectory(backward-cpp)
add_subdirectory(googletest)

include_directories(glew/include)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})