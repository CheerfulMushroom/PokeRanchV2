list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}")

# sets GTEST_INCLUDE_DIRS and GTEST_LIBRARIES
find_package(GTest REQUIRED)
# adds the gtest include directory
include_directories(${GTEST_INCLUDE_DIRS})

# sets GTEST_INCLUDE_DIRS and GTEST_LIBRARIES
find_package(GMock REQUIRED)
# adds the gtest include directory
include_directories(${GMOCK_INCLUDE_DIRS})

include_directories(../Game/States/include)
add_executable(stateTest
        mainTest.cpp
        myTest.cpp
        ../Game/States/src/AuthState.cpp)

target_link_libraries(stateTest
        ${GTEST_LIBRARIES}
        ${GMOCK_LIBRARIES}
        pthread)

