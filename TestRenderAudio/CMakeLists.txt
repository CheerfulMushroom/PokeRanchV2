cmake_minimum_required(VERSION 3.10)
project(PokeRanchV2)

set(CMAKE_CXX_STANDARD 14)

set(PROJECT_SHADER_PROGRAM_DIR ../Engine/Renderable/ShaderProgram)
set(PROJECT_GAME_WINDOW_DIR ../Engine/Renderable/GameWindow)
set(PROJECT_MODEL_DIR ../Engine/Renderable/Model)
set(PROJECT_BASE_CLASSES_DIR ../Engine/BaseClasses)
set(PROJECT_FORM_DIR ../Engine/GUI/Form)
set(PROJECT_IMGUI_DIR ../Engine/GUI/imgui)
set(PROJECT_BUTTON_DIR ../Engine/GUI/Button)
set(PROJECT_NAVBAR_DIR ../Engine/GUI/NavBar)
set(PROJECT_NETWORK_DIR ../Engine/Network)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

include_directories("${PROJECT_SHADER_PROGRAM_DIR}")
include_directories("${PROJECT_GAME_WINDOW_DIR}")
include_directories("${PROJECT_MODEL_DIR}")
include_directories("${PROJECT_BASE_CLASSES_DIR}/include")
include_directories("${PROJECT_FORM_DIR}")
include_directories("${PROJECT_IMGUI_DIR}")
include_directories("${PROJECT_BUTTON_DIR}")
include_directories("${PROJECT_NAVBAR_DIR}")
include_directories("${PROJECT_NETWORK_DIR}")

find_package(OpenCV REQUIRED)
include_directories(${OPENCV_INCLUDE_DIRS})

# sets GTEST_INCLUDE_DIRS and GTEST_LIBRARIES
find_package(GTest REQUIRED)
# adds the gtest include directory
include_directories(${GTEST_INCLUDE_DIRS})

# sets GTEST_INCLUDE_DIRS and GTEST_LIBRARIES
find_package(GMock REQUIRED)
# adds the gtest include directory
include_directories(${GMOCK_INCLUDE_DIRS})


add_compile_definitions(DEBUG_MODEL)

add_executable(first_test.out
        ${PROJECT_SHADER_PROGRAM_DIR}/ShaderProgram.cpp
        main_test.cpp
        ShaderProgram_test.cpp
        GameWindow_test.cpp
        Mesh_test.cpp
        Model_test.cpp
        ${PROJECT_MODEL_DIR}/Mesh.cpp
        ${PROJECT_MODEL_DIR}/Model.cpp
        ${PROJECT_GAME_WINDOW_DIR}/GameWindow.cpp
        ${PROJECT_BASE_CLASSES_DIR}/src/GameElement.cpp
        ${PROJECT_IMGUI_DIR}/imgui.cpp
        ${PROJECT_IMGUI_DIR}/imgui_demo.cpp
        ${PROJECT_IMGUI_DIR}/imgui_draw.cpp
        ${PROJECT_IMGUI_DIR}/imgui_impl_glfw_gl3.cpp
        ${PROJECT_IMGUI_DIR}/imgui_impl_opengl3.cpp # возможно лишнее
        ${PROJECT_IMGUI_DIR}/imgui_widgets.cpp)

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

add_executable(formMain.out
        ${PROJECT_SHADER_PROGRAM_DIR}/ShaderProgram.cpp
        ${PROJECT_GAME_WINDOW_DIR}/GameWindow.cpp
        ${PROJECT_IMGUI_DIR}/imgui.cpp
        ${PROJECT_IMGUI_DIR}/imgui_demo.cpp
        ${PROJECT_IMGUI_DIR}/imgui_draw.cpp
        ${PROJECT_IMGUI_DIR}/imgui_impl_glfw_gl3.cpp
        ${PROJECT_IMGUI_DIR}/imgui_impl_opengl3.cpp # возможно лишнее
        ${PROJECT_IMGUI_DIR}/imgui_widgets.cpp
        formMain.cpp
        ${PROJECT_FORM_DIR}/Form.cpp
        ${PROJECT_NAVBAR_DIR}/NavBar.cpp
        ${PROJECT_MODEL_DIR}/Mesh.cpp
        ${PROJECT_MODEL_DIR}/Model.cpp
        ${PROJECT_MODEL_DIR}/AnimModel.cpp
        ${PROJECT_MODEL_DIR}/math_3d.cpp
        ${PROJECT_BUTTON_DIR}/Button.cpp
        ${PROJECT_BUTTON_DIR}/ImageButton.cpp
        ${PROJECT_BASE_CLASSES_DIR}/src/GameElement.cpp
        ${PROJECT_NETWORK_DIR}/HttpNetworkManager.cpp
        )



target_link_libraries(formMain.out
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
        boost_filesystem
        )
