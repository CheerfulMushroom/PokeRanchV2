list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}")


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


include_directories("${PROJECT_SHADER_PROGRAM_DIR}")
include_directories("${PROJECT_GAME_WINDOW_DIR}")
include_directories("${PROJECT_MODEL_DIR}")
include_directories("${PROJECT_BASE_CLASSES_DIR}/include")
include_directories("${PROJECT_FORM_DIR}")
include_directories("${PROJECT_IMGUI_DIR}")
include_directories("${PROJECT_BUTTON_DIR}")
include_directories("${PROJECT_NAVBAR_DIR}")
include_directories("${PROJECT_NETWORK_DIR}")


add_compile_definitions(
        DEBUG_GAME_ELEMENT
        DEBUG_GAME_STATE
        DEBUG_ENGINE)

add_executable(stateTest
        main.cpp
        GameElementTest.cpp
        GameStateTest.cpp
        EngineTest.cpp

        ${PROJECT_BASE_CLASSES_DIR}/src/Engine.cpp
        ${PROJECT_BASE_CLASSES_DIR}/src/GameElement.cpp
        ${PROJECT_BASE_CLASSES_DIR}/src/GameState.cpp

        ${PROJECT_GAME_WINDOW_DIR}/GameWindow.cpp

        ${PROJECT_IMGUI_DIR}/imgui.cpp
        ${PROJECT_IMGUI_DIR}/imgui_demo.cpp
        ${PROJECT_IMGUI_DIR}/imgui_draw.cpp
        ${PROJECT_IMGUI_DIR}/imgui_impl_glfw_gl3.cpp
        ${PROJECT_IMGUI_DIR}/imgui_impl_opengl3.cpp # возможно лишнее
        ${PROJECT_IMGUI_DIR}/imgui_widgets.cpp
        )


target_link_libraries(stateTest
        ${GTEST_LIBRARIES}
        ${GMOCK_LIBRARIES}
        GLEW
        glfw
        GL
        opencv_core
        opencv_imgproc
        opencv_highgui
        opencv_imgcodecs
        opencv_videoio
        opencv_calib3d
        pthread)

