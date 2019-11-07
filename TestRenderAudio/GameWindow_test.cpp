#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <GameWindow.h>


TEST(GameWindowTest, checkDefaultSettings) {  // 1280 * 1024
    GameWindow screen;

    EXPECT_TRUE(screen.getWindow() != nullptr);

    std::pair<int, int> WindowSize = screen.getWindowSize();

    EXPECT_EQ(std::get<0>(WindowSize), 1280);
    EXPECT_EQ(std::get<1>(WindowSize), 1024);
}

TEST(GameWindowTest, checkHD) {
    GameWindow screen(1280, 720);

    EXPECT_TRUE(screen.getWindow() != nullptr);

    std::pair<int, int> WindowSize = screen.getWindowSize();

    EXPECT_EQ(std::get<0>(WindowSize), 1280);
    EXPECT_EQ(std::get<1>(WindowSize), 720);
}

TEST(GameWindowTest, checkFullHD) {
    GameWindow screen(1920, 1080);

    EXPECT_TRUE(screen.getWindow() != nullptr);

    std::pair<int, int> WindowSize = screen.getWindowSize();

    EXPECT_EQ(std::get<0>(WindowSize), 1920);
    EXPECT_EQ(std::get<1>(WindowSize), 1080);
}


