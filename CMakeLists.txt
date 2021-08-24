cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 20)

project(Game2D)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(Dependencies/glfw-3.3.4)
add_subdirectory(Dependencies/glew-2.2.0/build/cmake)

include_directories(Dependencies/glew-2.2.0/include)

set(SOURCES
        Game2D/src/View/Application.cpp
        Game2D/src/Model/Block.cpp
        Game2D/src/View/BlockAnimator.cpp
        Game2D/src/Model/DisplayBlock.cpp
        Game2D/src/Model/Enemy.cpp
        Game2D/src/View/EnemyAnimator.cpp
        Game2D/src/Controller/Game.cpp
        Game2D/src/Model/GameInformation.cpp
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
)

find_package(OpenGL REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS})

add_executable(Game2D ${SOURCES})

target_link_libraries(Game2D ${OPENGL_LIBRARIES} glew_s glfw)