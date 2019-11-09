#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <ShaderProgram.h>
#include <GameWindow.h>
#include <Model.h>
#include <Camera.h>
#include <opencv2/opencv.hpp>

class MockPathManager {
public:
    MockPathManager() = default;

    MOCK_METHOD1(getShadersPath, std::tuple<std::string, std::string> (std::string const& name));
    MOCK_METHOD1(getModelPath, std::string (std::string const& name));
};

class ModelTest : public ::testing::Test {
protected:

    bool compareImage(cv::Mat& currentImage, cv::Mat& goldenImage) {
        cv::Mat channelsDiff[3];

        cv::Mat channelsCurrentImage[3];
        cv::Mat channelsGoldenImage[3];

        cv::split(currentImage, channelsCurrentImage);
        cv::split(goldenImage, channelsGoldenImage);

        int diffValues = 0;

        for (int i = 0; i < 3; i++) {
            cv::bitwise_xor(channelsCurrentImage[i], channelsGoldenImage[i], channelsDiff[i]);
            diffValues += cv::countNonZero(channelsDiff[i]);
        }

        return (diffValues == 0);
    };

    MockPathManager pathManager;
    GameWindow screen;
};

TEST_F(ModelTest, getGoldenImages) {
    EXPECT_CALL(pathManager, getShadersPath("ModelShaders"))
        .Times(2)
        .WillRepeatedly(::testing::Return(std::make_tuple("Engine/Renderable/Shaders/v_model_shader.vs", "Engine/Renderable/Shaders/f_model_shader.fs")));

    EXPECT_CALL(pathManager, getModelPath("NanosuitModel"))
        .Times(1)
        .WillOnce(::testing::Return(std::string("Game/Resources/Models/nanosuit/nanosuit.obj")));

    EXPECT_CALL(pathManager, getModelPath("GymModel"))
        .Times(1)
        .WillOnce(::testing::Return(std::string("Game/Resources/Models/AzaleaGym/AzaleaGym.obj")));

    Camera camera(glm::vec3(0.0f, 0.0f, 4.0f));

    std::pair<int, int> WindowSize = screen.getWindowSize();

    int width = std::get<0>(WindowSize);
    int height = std::get<1>(WindowSize);

    Model nanosuit(pathManager.getModelPath("NanosuitModel"),
                     &camera,
                     glm::vec3(.0f, -1.0f, -2.0f),
                     glm::vec3(0.2f, 0.2f, 0.2f),
                     glm::vec3(0.0f, 0.0f, 1.0f),
                     0.0f,
                     width,
                     height);

    Model gym(pathManager.getModelPath("GymModel"),
                   &camera,
                   glm::vec3(.0f, -1.0f, -2.0f),
                   glm::vec3(0.02f, 0.02f, 0.02f),
                   glm::vec3(0.0f, 0.0f, 1.0f),
                   0.0f,
                   width,
                   height);


    nanosuit.shader.setSources(pathManager.getShadersPath("ModelShaders"));
    nanosuit.shader.compileSources();

    gym.shader.setSources(pathManager.getShadersPath("ModelShaders"));
    gym.shader.compileSources();

    screen.clearWindowBuffers();

    nanosuit.render();

    cv::Mat nanosuitScreenshot = screen.takeScreenshot();

    bool writeImageResult = cv::imwrite("TestRenderAudio/GoldenImages/Nanosuit.png", nanosuitScreenshot);

    EXPECT_TRUE(writeImageResult);

    screen.clearWindowBuffers();

    gym.render();

    cv::Mat gymScreenshot = screen.takeScreenshot();

    writeImageResult = cv::imwrite("TestRenderAudio/GoldenImages/Gym.png", gymScreenshot);

    EXPECT_TRUE(writeImageResult);
}

TEST_F(ModelTest, compareWithNanosuit) {
    EXPECT_CALL(pathManager, getShadersPath("ModelShaders"))
        .Times(1)
        .WillOnce(::testing::Return(std::make_tuple("Engine/Renderable/Shaders/v_model_shader.vs", "Engine/Renderable/Shaders/f_model_shader.fs")));

    EXPECT_CALL(pathManager, getModelPath("NanosuitModel"))
        .Times(1)
        .WillOnce(::testing::Return(std::string("Game/Resources/Models/nanosuit/nanosuit.obj")));

    Camera camera(glm::vec3(0.0f, 0.0f, 4.0f));

    std::pair<int, int> WindowSize = screen.getWindowSize();

    int width = std::get<0>(WindowSize);
    int height = std::get<1>(WindowSize);

    Model nanosuit(pathManager.getModelPath("NanosuitModel"),
                   &camera,
                   glm::vec3(.0f, -1.0f, -2.0f),
                   glm::vec3(0.2f, 0.2f, 0.2f),
                   glm::vec3(0.0f, 0.0f, 1.0f),
                   0.0f,
                   width,
                   height);

    nanosuit.shader.setSources(pathManager.getShadersPath("ModelShaders"));
    nanosuit.shader.compileSources();

    screen.clearWindowBuffers();

    nanosuit.render();

    cv::Mat nanosuitScreenshot = screen.takeScreenshot();

    cv::Mat nanosuitTrue = cv::imread("TestRenderAudio/GoldenImages/Nanosuit.png", cv::IMREAD_COLOR);

    EXPECT_TRUE(compareImage(nanosuitScreenshot, nanosuitTrue));
}

TEST_F(ModelTest, compareWithGym) {
    EXPECT_CALL(pathManager, getShadersPath("ModelShaders"))
            .Times(1)
            .WillOnce(::testing::Return(std::make_tuple("Engine/Renderable/Shaders/v_model_shader.vs", "Engine/Renderable/Shaders/f_model_shader.fs")));

    EXPECT_CALL(pathManager, getModelPath("GymModel"))
            .Times(1)
            .WillOnce(::testing::Return(std::string("Game/Resources/Models/AzaleaGym/AzaleaGym.obj")));

    Camera camera(glm::vec3(0.0f, 0.0f, 4.0f));

    std::pair<int, int> WindowSize = screen.getWindowSize();

    int width = std::get<0>(WindowSize);
    int height = std::get<1>(WindowSize);

    Model gym(pathManager.getModelPath("GymModel"),
                   &camera,
                   glm::vec3(.0f, -1.0f, -2.0f),
                   glm::vec3(0.02f, 0.02f, 0.02f),
                   glm::vec3(0.0f, 0.0f, 1.0f),
                   0.0f,
                   width,
                   height);

    gym.shader.setSources(pathManager.getShadersPath("ModelShaders"));
    gym.shader.compileSources();

    screen.clearWindowBuffers();

    gym.render();

    cv::Mat gymScreenshot = screen.takeScreenshot();

    cv::Mat gymTrue = cv::imread("TestRenderAudio/GoldenImages/Gym.png", cv::IMREAD_COLOR);

    EXPECT_TRUE(compareImage(gymScreenshot, gymTrue));
}