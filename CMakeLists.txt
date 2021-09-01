cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 20)

project(Game2D)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wpedantic -Wextra")

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

if(UNIX)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
endif()

set(FILE "${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/glew/include/GL/glew.h")
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

find_package(Python REQUIRED)
find_package(OpenGL REQUIRED)

add_subdirectory(Dependencies/glfw)
add_subdirectory(Dependencies/glew/build/cmake)
#add_subdirectory(backward-cpp)
add_subdirectory(Dependencies/googletest)
add_subdirectory(Tests)

include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(Dependencies/glew/include)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})


set(SOURCES
        Game2D/src/View/Application.cpp
        Game2D/src/Model/Block.cpp
        Game2D/src/View/BlockAnimator.cpp
        Game2D/src/View/DisplayBlock.cpp
        Game2D/src/Model/Enemy.cpp
        Game2D/src/View/EnemyAnimator.cpp
        Game2D/src/Controller/Game.cpp
        Game2D/src/View/GameInformation.cpp
        Game2D/src/Model/GameLevel.cpp
        Game2D/src/Model/GameObject.cpp
        Game2D/src/View/PengoAnimator.cpp
        Game2D/src/Model/Player.cpp
        Game2D/src/View/ResourceManager.cpp
        Game2D/src/View/Shader.cpp
        Game2D/src/View/SpriteRenderer.cpp
        Game2D/src/View/Texture.cpp
        Game2D/src/Model/Wall.cpp
        Game2D/src/View/WallAnimator.cpp
        Game2D/src/View/GameView.cpp Game2D/src/View/GameView.h Game2D/src/Model/Score.cpp Game2D/src/Model/Score.h)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} glew_s glfw)
