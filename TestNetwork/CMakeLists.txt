cmake_minimum_required(VERSION 3.10)
project(PokeRanchV2)

set(CMAKE_CXX_STANDARD 14)
set(PROJECT_NETWORK_DIR ../Engine/Network)
set(PROJECT_BASE_CLASSES_DIR ../Engine/BaseClasses)


include_directories("${PROJECT_NETWORK_DIR}")
include_directories("${PROJECT_BASE_CLASSES_DIR}/include")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

# sets GTEST_INCLUDE_DIRS and GTEST_LIBRARIES
#find_package(GTest REQUIRED)
# adds the gtest include directory
#include_directories(${GTEST_INCLUDE_DIRS})
#
# sets GTEST_INCLUDE_DIRS and GTEST_LIBRARIES
#find_package(GMock REQUIRED)
# adds the gtest include directory
#include_directories(${GMOCK_INCLUDE_DIRS})

add_executable(simpleGet.out
        simpleGet.cpp
        ${PROJECT_NETWORK_DIR}/HttpNetworkManager.cpp
        ${PROJECT_NETWORK_DIR}/UserSession.cpp)

target_link_libraries(simpleGet.out
        #${GTEST_LIBRARIES}
        #${GMOCK_LIBRARIES}
        pthread
        )

add_executable(sessionTest.out
        sessionTest.cpp
        ${PROJECT_NETWORK_DIR}/HttpNetworkManager.cpp
        ${PROJECT_NETWORK_DIR}/UserSession.cpp)

target_link_libraries(sessionTest.out
        #${GTEST_LIBRARIES}
        #${GMOCK_LIBRARIES}
        pthread
        )