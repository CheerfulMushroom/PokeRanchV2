cmake_minimum_required(VERSION 3.10)
project(PokeRanchV2)

set(CMAKE_CXX_STANDARD 14)

set(PROJECT_SHADER_PROGRAM_DIR ../Engine/Renderable/ShaderProgram)
set(PROJECT_GAME_WINDOW_DIR ../Engine/Renderable/GameWindow)
set(PROJECT_MODEL_DIR ../Engine/Renderable/Model)
set(PROJECT_INTERFACES_DIR ../Engine/BasicInterfaces)

#set(PROJECT_TEST_SOURCE_DIR tests)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

#include_directories("${PROJECT_HEADER_DIR}")
#include_directories("${PROJECT_SOURCE_DIR}")

include_directories("${PROJECT_SHADER_PROGRAM_DIR}")
include_directories("${PROJECT_GAME_WINDOW_DIR}")
include_directories("${PROJECT_MODEL_DIR}")
include_directories("${PROJECT_INTERFACES_DIR}")

find_package(OpenCV REQUIRED)
#include_directories(${OPENCV_INCLUDE_DIRS})

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
        Mesh_test.cpp
        Model_test.cpp
        ${PROJECT_MODEL_DIR}/Mesh.cpp
        ${PROJECT_MODEL_DIR}/Model.cpp
        ${PROJECT_GAME_WINDOW_DIR}/GameWindow.cpp)

target_link_libraries(first_test.out
        ${GTEST_LIBRARIES}
        ${GMOCK_LIBRARIES}
        pthread
        GLEW
        glfw
        GL
        opencv_core
        opencv_imgproc
        opencv_highgui
        opencv_imgcodecs
        opencv_videoio
        opencv_calib3d
        assimp
        )
