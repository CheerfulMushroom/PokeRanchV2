#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <ShaderProgram.h>
#include <GameWindow.h>
#include <Mesh.h>
#include <opencv2/opencv.hpp>

class MockPathManager {
public:
    MockPathManager() = default;

    MOCK_METHOD1(getShadersPath, std::tuple<std::string, std::string> (std::string const& name));
    MOCK_METHOD1(getModelPath, std::string (std::string const& name));
};

class MeshTest : public ::testing::Test {
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

    ShaderProgram shader;
    MockPathManager pathManager;
    GameWindow screen;
};


TEST_F(MeshTest, getGoldenImages) {
    EXPECT_CALL(pathManager, getShadersPath("simpleMeshShaders"))
        .Times(1)
        .WillOnce(::testing::Return(std::make_tuple("Engine/Renderable/Shaders/testExample.vs", "Engine/Renderable/Shaders/testExample.fs")));

    shader.setSources(pathManager.getShadersPath("simpleMeshShaders"));
    shader.compileSources();

    std::vector<Vertex> rectangleVertices = {
            { {0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f} },
            { {0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f} },
            { {-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f} },
            { {-0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f} },
    };

    std::vector<unsigned int> rectangleIndices = { 0, 1, 3, 1, 2, 3 };
    std::vector<Texture> rectangleTextures = {};

    std::vector<Vertex> triangleVertices = {
            { {-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f} },
            { {0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f} },
            { {0.0f, 0.5f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f} },
    };

    std::vector<unsigned int> triangleIndices = { 0, 1, 2 };
    std::vector<Texture> triangleTextures = {};

    shader.use();

    Mesh rectangle(rectangleVertices, rectangleIndices, rectangleTextures);
    Mesh triangle(triangleVertices, triangleIndices, triangleTextures);

    screen.clearWindowBuffers();

    rectangle.drawMesh(shader);

    cv::Mat whiteRectangle = screen.takeScreenshot();

    bool writeImageResult = cv::imwrite("TestRenderAudio/GoldenImages/WhiteRectangle.png", whiteRectangle);

    EXPECT_TRUE(writeImageResult);

    screen.clearWindowBuffers();

    triangle.drawMesh(shader);

    cv::Mat whiteTriangle = screen.takeScreenshot();

    writeImageResult = cv::imwrite("TestRenderAudio/GoldenImages/WhiteTriangle.png", whiteTriangle);

    EXPECT_TRUE(writeImageResult);
}

TEST_F(MeshTest, compareWithRectangle) {
    EXPECT_CALL(pathManager, getShadersPath("simpleMeshShaders"))
            .Times(1)
            .WillOnce(::testing::Return(std::make_tuple("Engine/Renderable/Shaders/testExample.vs", "Engine/Renderable/Shaders/testExample.fs")));

    shader.setSources(pathManager.getShadersPath("simpleMeshShaders"));
    shader.compileSources();

    std::vector<Vertex> rectangleVertices = {
            { {0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f} },
            { {0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f} },
            { {-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f} },
            { {-0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f} },
    };

    std::vector<unsigned int> rectangleIndices = { 0, 1, 3, 1, 2, 3 };
    std::vector<Texture> rectangleTextures = {};

    shader.use();

    Mesh rectangle(rectangleVertices, rectangleIndices, rectangleTextures);

    screen.clearWindowBuffers();

    rectangle.drawMesh(shader);

    cv::Mat rectangleScreenshot = screen.takeScreenshot();

    cv::Mat rectangleTrue = cv::imread("TestRenderAudio/GoldenImages/WhiteRectangle.png", cv::IMREAD_COLOR);

    EXPECT_TRUE(compareImage(rectangleScreenshot, rectangleTrue));
}

TEST_F(MeshTest, compareWithTriangle) {
    EXPECT_CALL(pathManager, getShadersPath("simpleMeshShaders"))
            .Times(1)
            .WillOnce(::testing::Return(std::make_tuple("Engine/Renderable/Shaders/testExample.vs", "Engine/Renderable/Shaders/testExample.fs")));

    shader.setSources(pathManager.getShadersPath("simpleMeshShaders"));
    shader.compileSources();

    std::vector<Vertex> triangleVertices = {
            { {-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f} },
            { {0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f} },
            { {0.0f, 0.5f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f} },
    };

    std::vector<unsigned int> triangleIndices = { 0, 1, 2 };
    std::vector<Texture> triangleTextures = {};

    shader.use();

    Mesh triangle(triangleVertices, triangleIndices, triangleTextures);

    screen.clearWindowBuffers();

    triangle.drawMesh(shader);

    cv::Mat triangleScreenshot = screen.takeScreenshot();

    cv::Mat triangleTrue = cv::imread("TestRenderAudio/GoldenImages/WhiteTriangle.png", cv::IMREAD_COLOR);

    EXPECT_TRUE(compareImage(triangleScreenshot, triangleTrue));
}