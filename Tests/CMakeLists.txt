project(Tests)

enable_testing()

set(TEST_SOURCES

        TestGameLevel.cpp)

include_directories(${CMAKE_SOURCE_DIR})
add_executable(${PROJECT_NAME} main.cpp ${SOURCES} ${TEST_SOURCES})
target_link_libraries(${PROJECT_NAME} ${LIBS} gmock gtest pthread)


add_test(
        NAME ${PROJECT_NAME}
        COMMAND ${PROJECT_NAME}
)
