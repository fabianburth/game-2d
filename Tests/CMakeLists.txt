enable_testing()

set(TEST_SOURCES
        TestGameLevel.cpp
        TestEnemy.cpp)

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/Dependencies/glew/include)
add_executable(${PROJECT_NAME}_TESTS main.cpp ${SOURCES} ${TEST_SOURCES})
target_link_libraries(${PROJECT_NAME}_TESTS ${LIBS} gmock gtest pthread glew_s glfw)


add_test(
        NAME ${PROJECT_NAME}_TESTS
        COMMAND ${PROJECT_NAME}_TESTS
)
