#include <GameWindow.h>

#include <unistd.h>
#include <Form.h>
#include <NavBar.h>
#include <imgui.h>
#include <Model.h>
#include <Camera.h>
#include <ImageButton.h>
#include <HttpNetworkManager.h>

#include <AnimModel.h>

#define FPS 60

int main() {
    GameWindow screen;
    Form authForm;
    NavBar navbar;

    Camera camera(glm::vec3(0.0f, 0.0f, 4.0f));

    std::pair<int, int> WindowSize = screen.getWindowSize();

    int width = std::get<0>(WindowSize);
    int height = std::get<1>(WindowSize);

    Model gym("Game/Resources/Models/AzaleaGym/AzaleaGym.obj",
            &camera,
              glm::vec3(-1.3f, -1.0f, -2.0f),
              0.02,
              glm::vec3(0.0f, 38.0f, 0.0f),
              width,
              height,
              std::string("gym"));

    AnimModel pokemon("Game/Resources/Models/Meowth/stay.dae",
                    &camera,
                    glm::vec3(0.9f, -1.0f, 0.0f),
                    0.02,
                    glm::vec3(90.0f, 140.0f, 0.0f),
                    width,
                    height,
                    std::string("pokemon"));

    Model amie("Game/Resources/Models/PokemonAmie/withoutAll.dae",
            &camera,
              glm::vec3(0.0f, -1.0f, -2.0f),
              0.015,
              glm::vec3(0.0f, 0.0f, 0.0f),
              width,
              height,
              std::string("amie"));


    #ifdef DEBUG_MODEL
    gym.shader.setSources(std::make_tuple("Engine/Renderable/Shaders/v_model_shader.vs", "Engine/Renderable/Shaders/f_model_shader.fs"));
    gym.shader.compileSources();
//
//    suit.shader.setSources(std::make_tuple("Engine/Renderable/Shaders/v_model_shader.vs", "Engine/Renderable/Shaders/f_model_shader.fs"));
//    suit.shader.compileSources();

    amie.shader.setSources(std::make_tuple("Engine/Renderable/Shaders/v_model_shader.vs", "Engine/Renderable/Shaders/f_model_shader.fs"));
    amie.shader.compileSources();
    #endif


    auto func = []() {
        std::cout << "KEK" << std::endl;
    };

    auto kitchenButton = std::make_unique<ImageButton>("Game/Resources/Pictures/cake-slice.png", ImVec2(64.0f, 64.0f), 5, false, func);
    auto homeButton = std::make_unique<ImageButton>("Game/Resources/Pictures/house.png", ImVec2(64.0f, 64.0f), 5, false, func);
    auto gymButton = std::make_unique<ImageButton>("Game/Resources/Pictures/muscle-up.png", ImVec2(128.0f, 128.0f), 5, true, func);
    auto socialButton = std::make_unique<ImageButton>("Game/Resources/Pictures/human-pyramid.png", ImVec2(64.0f, 64.0f), 5, false, func);
    auto battleButton = std::make_unique<ImageButton>("Game/Resources/Pictures/champions.png", ImVec2(64.0f, 64.0f), 5, false, func);

    navbar.addButton(std::move(kitchenButton));
    navbar.addButton(std::move(homeButton));
    navbar.addButton(std::move(gymButton));
    navbar.addButton(std::move(socialButton));
    navbar.addButton(std::move(battleButton));

    while (!glfwWindowShouldClose(screen.getWindow())) {
        double frame_start_time = glfwGetTime();
        screen.frameInit();

        //ImGui::ShowDemoWindow();

        authForm.render();

        navbar.render();

        gym.render();
        //suit.render();
        pokemon.update();
        pokemon.render();

        amie.render();

        double allowed_frame_time = 1.0 / FPS;
        double frame_end_time = glfwGetTime();

        double frame_draw_time = frame_end_time - frame_start_time;
        double sleep_time = 0.0;

        screen.frameEnd();

        if (frame_draw_time < allowed_frame_time) {
            sleep_time = allowed_frame_time - frame_draw_time;
            usleep(1000000 * sleep_time);
        }

    }

    return 0;
}