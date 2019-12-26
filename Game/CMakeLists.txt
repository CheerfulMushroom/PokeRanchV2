include_directories(States/include)
include_directories(${ENGINE_PATH}/)

find_package(OpenCV REQUIRED)
include_directories(${OPENCV_INCLUDE_DIRS})


add_compile_definitions(DEBUG_MODEL)
#add_compile_definitions(DEBUG_GAME_STATE)
add_compile_definitions(GUI_DEBUG)

include_directories("${PROJECT_SHADER_PROGRAM_DIR}")
include_directories("${PROJECT_GAME_WINDOW_DIR}")
include_directories("${PROJECT_MODEL_DIR}")
include_directories("${PROJECT_BASE_CLASSES_DIR}/include")
include_directories("${PROJECT_FORM_DIR}")
include_directories("${PROJECT_IMGUI_DIR}")
include_directories("${PROJECT_BUTTON_DIR}")
include_directories("${PROJECT_INPUTTEXT_DIR}")
include_directories("${PROJECT_NAVBAR_DIR}")
include_directories("${PROJECT_NETWORK_DIR}")
include_directories("${PROJECT_PROGRESS_BAR_DIR}")
include_directories("${PROJECT_STATES_DIR}/include")
include_directories("${PROJECT_UTILS_DIR}/PathManager")
include_directories("${PROJECT_UTILS_DIR}/ModelSwitcher")
include_directories("${PROJECT_UTILS_DIR}/ButtonFunctions")
include_directories("${PROJECT_POKEMON_DIR}")
include_directories("${PROJECT_CUPCAKE_DIR}")
include_directories("${PROJECT_SERVERAPI_DIR}")
include_directories("${PROJECT_POKEMONINFOUPDATER_DIR}")


add_executable(main.out
        main.cpp
        ${PROJECT_STATES_DIR}/src/AuthState.cpp
        ${PROJECT_STATES_DIR}/src/GymState.cpp
        ${PROJECT_STATES_DIR}/src/RegisterState.cpp
        ${PROJECT_STATES_DIR}/src/HomeState.cpp
        ${PROJECT_STATES_DIR}/src/KitchenState.cpp
        ${PROJECT_STATES_DIR}/src/TrainerSelectionState.cpp
        ${PROJECT_STATES_DIR}/src/PokemonSelectionState.cpp


        ${PROJECT_BASE_CLASSES_DIR}/src/Engine.cpp
        ${PROJECT_BASE_CLASSES_DIR}/src/GameElement.cpp
        ${PROJECT_BASE_CLASSES_DIR}/src/GameState.cpp
        ${PROJECT_UTILS_DIR}/PathManager/PathManager.cpp
        ${PROJECT_UTILS_DIR}/ButtonFunctions/ButtonFunctions.cpp
        ${PROJECT_SERVERAPI_DIR}/ServerAPI.cpp
        ${PROJECT_POKEMONINFOUPDATER_DIR}/PokemonInfoUpdater.cpp


        ${PROJECT_IMGUI_DIR}/imgui.cpp
        ${PROJECT_IMGUI_DIR}/imgui_demo.cpp
        ${PROJECT_IMGUI_DIR}/imgui_draw.cpp
        ${PROJECT_IMGUI_DIR}/imgui_impl_glfw_gl3.cpp
        ${PROJECT_IMGUI_DIR}/imgui_impl_opengl3.cpp # возможно лишнее
        ${PROJECT_IMGUI_DIR}/imgui_widgets.cpp

        ${PROJECT_BUTTON_DIR}/Button.cpp
        ${PROJECT_INPUTTEXT_DIR}/InputText.cpp
        ${PROJECT_BUTTON_DIR}/ImageButton.cpp
        ${PROJECT_FORM_DIR}/Form.cpp
        ${PROJECT_NAVBAR_DIR}/NavBar.cpp
        ${PROJECT_PROGRESS_BAR_DIR}/ProgressBar.cpp
        ${PROJECT_NETWORK_DIR}/HttpNetworkManager.cpp

        ${PROJECT_POKEMON_DIR}/Pokemon.cpp
        ${PROJECT_CUPCAKE_DIR}/Cupcake.cpp
        ${PROJECT_GAME_WINDOW_DIR}/GameWindow.cpp
        ${PROJECT_MODEL_DIR}/AnimModel.cpp
        ${PROJECT_MODEL_DIR}/Model.cpp
        ${PROJECT_MODEL_DIR}/Mesh.cpp
        ${PROJECT_MODEL_DIR}/math_3d.cpp

        ${PROJECT_SHADER_PROGRAM_DIR}/ShaderProgram.cpp
        )

target_link_libraries(main.out
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