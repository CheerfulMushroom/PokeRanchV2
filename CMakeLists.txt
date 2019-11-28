CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
PROJECT(PokeRanchV2 VERSION 2)


SET(CMAKE_CXX_STANDARD 17)
#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

SET(ENGINE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/Engine)
SET(GAME_PATH ${CMAKE_CURRENT_SOURCE_DIR}/Game)


include_directories(Engine)
include_directories(Game)

add_subdirectory(Engine)
add_subdirectory(Game)
add_subdirectory(StateTest)
