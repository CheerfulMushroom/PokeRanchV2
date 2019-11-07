#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <ShaderProgram.h>
#include <GameWindow.h>

class MockPathManager {
public:
    MockPathManager() = default;

    MOCK_METHOD1(getShadersPath, std::tuple<std::string, std::string> (std::string const& name));
    MOCK_METHOD1(getModelPath, std::string (std::string const& name));

};

class ShaderProgramTest : public ::testing::Test {
 protected:
    ShaderProgram shader;

    GameWindow screen;
    MockPathManager pathManager;
};

TEST_F(ShaderProgramTest, checkValidPath) {
    EXPECT_CALL(pathManager, getShadersPath("AnimShader"))
        .Times(1)
        .WillOnce(::testing::Return(std::make_tuple(
                "../../Engine/Renderable/Shaders/v_model_anim_pokedex_shader.vs",
                "../../Engine/Renderable/Shaders/f_model_anim_shader.fs")));

    bool setting_state = shader.setSources(pathManager.getShadersPath("AnimShader"));

    EXPECT_TRUE(setting_state);
}

TEST_F(ShaderProgramTest, checkBadPath) {
    EXPECT_CALL(pathManager, getShadersPath("Blabla"))
        .Times(1)
        .WillOnce(::testing::Return(std::make_tuple("", "")));

    bool setting_state = shader.setSources(pathManager.getShadersPath("Blabla"));

    EXPECT_FALSE(setting_state);
}

TEST_F(ShaderProgramTest, checkCorrectSources) {
    EXPECT_CALL(pathManager, getShadersPath("AnimShader"))
        .Times(1)
        .WillOnce(::testing::Return(std::make_tuple(
                "../../Engine/Renderable/Shaders/v_model_anim_pokedex_shader.vs",
                "../../Engine/Renderable/Shaders/f_model_anim_shader.fs")));

    bool setting_state = shader.setSources(pathManager.getShadersPath("AnimShader"));

    ASSERT_TRUE(setting_state);

    bool compile_state = shader.compileSources();

    EXPECT_TRUE(compile_state);
}

TEST_F(ShaderProgramTest, checkIncorrectSources) {
    EXPECT_CALL(pathManager, getShadersPath("AnimShader"))
            .Times(1)
            .WillOnce(::testing::Return(std::make_tuple(
                    "../../Engine/Renderable/Shaders/incorrect_v_model_anim_pokedex_shader.vs",
                    "../../Engine/Renderable/Shaders/incorrect_f_model_anim_shader.fs")));

    bool setting_state = shader.setSources(pathManager.getShadersPath("AnimShader"));

    ASSERT_TRUE(setting_state);

    bool compile_state = shader.compileSources();

    EXPECT_FALSE(compile_state);
}

TEST_F(ShaderProgramTest, checkEmptySources) {
    EXPECT_CALL(pathManager, getShadersPath("AnimShader"))
            .Times(1)
            .WillOnce(::testing::Return(std::make_tuple(
                    "../../Engine/Renderable/Shaders/empty_shader.vs",
                    "../../Engine/Renderable/Shaders/empty_shader.fs")));

    bool setting_state = shader.setSources(pathManager.getShadersPath("AnimShader"));

    ASSERT_TRUE(setting_state);

    bool compile_state = shader.compileSources();

    EXPECT_FALSE(compile_state);
}

// Протестировать set_mat4_uniform