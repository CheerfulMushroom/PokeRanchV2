CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
PROJECT(PokeRanchV2 VERSION 2)


SET(CMAKE_CXX_STANDARD 17)
#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

SET(ENGINE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/Engine)
SET(GAME_PATH ${CMAKE_CURRENT_SOURCE_DIR}/Game)

set(PROJECT_SHADER_PROGRAM_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/Engine/Renderable/ShaderProgram)
set(PROJECT_GAME_WINDOW_DIR     ${CMAKE_CURRENT_SOURCE_DIR}/Engine/Renderable/GameWindow)
set(PROJECT_MODEL_DIR           ${CMAKE_CURRENT_SOURCE_DIR}/Engine/Renderable/Model)
set(PROJECT_BASE_CLASSES_DIR    ${CMAKE_CURRENT_SOURCE_DIR}/Engine/BaseClasses)
set(PROJECT_FORM_DIR            ${CMAKE_CURRENT_SOURCE_DIR}/Engine/GUI/Form)
set(PROJECT_IMGUI_DIR           ${CMAKE_CURRENT_SOURCE_DIR}/Engine/GUI/imgui)
set(PROJECT_BUTTON_DIR          ${CMAKE_CURRENT_SOURCE_DIR}/Engine/GUI/Button)
set(PROJECT_NAVBAR_DIR          ${CMAKE_CURRENT_SOURCE_DIR}/Engine/GUI/NavBar)
set(PROJECT_NETWORK_DIR         ${CMAKE_CURRENT_SOURCE_DIR}/Engine/Network)
set(PROJECT_STATES_DIR          ${CMAKE_CURRENT_SOURCE_DIR}/Game/States)


include_directories(/home/alexandr/Downloads/boost_1_71_0)
include_directories(Engine)
include_directories(Game)

add_subdirectory(Engine)
add_subdirectory(Game)
add_subdirectory(StateTest)
add_subdirectory(TestRenderAudio)
add_subdirectory(TestNetwork)
