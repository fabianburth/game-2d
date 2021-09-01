cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 20)

project(Game2D)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wpedantic -Wextra")
if(UNIX)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
endif()


find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

add_subdirectory(Dependencies)
add_subdirectory(Tests)

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

add_executable(${PROJECT_NAME} ${SOURCES} ${BACKWARD_ENABLE})

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} glew_s glfw)

add_backward(${PROJECT_NAME})