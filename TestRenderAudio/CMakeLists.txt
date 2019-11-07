cmake_minimum_required(VERSION 3.10)
project(PokeRanchV2)

set(CMAKE_CXX_STANDARD 14)
set(PROJECT_SOURCE_DIR src)
set(PROJECT_HEADER_DIR include)

set(PROJECT_SHADER_PROGRAM_DIR ../Engine/Renderable/ShaderProgram)
set(PROJECT_GAME_WINDOW_DIR ../Engine/Renderable/GameWindow)

#set(PROJECT_TEST_SOURCE_DIR tests)


list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

#include_directories("${PROJECT_HEADER_DIR}")
#include_directories("${PROJECT_SOURCE_DIR}")

include_directories("${PROJECT_SHADER_PROGRAM_DIR}")
include_directories("${PROJECT_GAME_WINDOW_DIR}")

find_package(OpenCV REQUIRED )

# sets GTEST_INCLUDE_DIRS and GTEST_LIBRARIES
find_package(GTest REQUIRED)
# adds the gtest include directory
include_directories(${GTEST_INCLUDE_DIRS})

# sets GTEST_INCLUDE_DIRS and GTEST_LIBRARIES
find_package(GMock REQUIRED)
# adds the gtest include directory
include_directories(${GMOCK_INCLUDE_DIRS})


add_executable(first_test.out
        ${PROJECT_SHADER_PROGRAM_DIR}/ShaderProgram.cpp
        main_test.cpp
        ShaderProgram_test.cpp
        GameWindow_test.cpp
        ${PROJECT_GAME_WINDOW_DIR}/GameWindow.cpp)

target_link_libraries(first_test.out
        ${GTEST_LIBRARIES}
        ${GMOCK_LIBRARIES}
        pthread
        GLEW
        glfw
        GL
        )

