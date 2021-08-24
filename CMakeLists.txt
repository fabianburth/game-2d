cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 20)

project(Game2D)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(Dependencies/glfw-3.3.4)
add_subdirectory(Dependencies/glew-2.2.0/build/cmake)

include_directories(Dependencies/glew-2.2.0/include)

set(SOURCES
        Game2D/src/Application.cpp
        Game2D/src/Block.cpp
        Game2D/src/BlockAnimator.cpp
        Game2D/src/DisplayBlock.cpp
        Game2D/src/Enemy.cpp
        Game2D/src/EnemyAnimator.cpp
        Game2D/src/Game.cpp
        Game2D/src/GameInformation.cpp
        Game2D/src/GameLevel.cpp
        Game2D/src/GameObject.cpp
        Game2D/src/PengoAnimator.cpp
        Game2D/src/Player.cpp
        Game2D/src/ResourceManager.cpp
        Game2D/src/Shader.cpp
        Game2D/src/SpriteRenderer.cpp
        Game2D/src/Texture.cpp
        Game2D/src/Wall.cpp
        Game2D/src/WallAnimator.cpp
)

find_package(OpenGL REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS})

add_executable(Game2D ${SOURCES})

target_link_libraries(Game2D ${OPENGL_LIBRARIES} glew glfw)