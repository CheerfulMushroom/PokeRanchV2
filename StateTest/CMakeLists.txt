list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}")

# sets GTEST_INCLUDE_DIRS and GTEST_LIBRARIES
find_package(GTest REQUIRED)
# adds the gtest include directory
include_directories(${GTEST_INCLUDE_DIRS})

# sets GTEST_INCLUDE_DIRS and GTEST_LIBRARIES
find_package(GMock REQUIRED)
# adds the gtest include directory
include_directories(${GMOCK_INCLUDE_DIRS})

include_directories(${GAME_PATH}/States/include)
include_directories(${ENGINE_PATH}/BaseClasses/include)

add_compile_definitions(
        DEBUG_GAME_ELEMENT
        DEBUG_GAME_STATE
        DEBUG_ENGINE)

add_executable(stateTest
        main.cpp
        GameElementTest.cpp
        GameStateTest.cpp
        EngineTest.cpp

        ${ENGINE_PATH}/BaseClasses/src/GameElement.cpp
        ${ENGINE_PATH}/BaseClasses/src/GameState.cpp
        ${ENGINE_PATH}/BaseClasses/src/Engine.cpp)

target_link_libraries(stateTest
        ${GTEST_LIBRARIES}
        ${GMOCK_LIBRARIES}
        pthread)

