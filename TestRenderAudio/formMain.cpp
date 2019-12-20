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
    GameWindow screen(1280, 1024);
    Form authForm;
    NavBar navbar;

    Camera camera(glm::vec3(0.0f, 0.0f, 4.0f));

    std::pair<int, int> WindowSize = screen.getWindowSize();

    int width = std::get<0>(WindowSize);
    int height = std::get<1>(WindowSize);


    AnimModel pokemon("Game/Resources/Models/Litten/stay.dae",
                    &camera,
                    glm::vec3(0.9f, -1.0f, 0.0f),
                    0.02,
                    glm::vec3(90.0f, 140.0f, 0.0f),
                    width,
                    height,
                    std::string("pokemon"));

    AnimModel trainer("Game/Resources/Models/Red/stay.dae",
                      &camera,
                      glm::vec3(0.9f, -1.0f, 0.0f),
                      0.02,
                      glm::vec3(90.0f, 140.0f, 0.0f),
                      width,
                      height,
                      std::string("trainer"));

    #ifdef DEBUG_MODEL
//    gym.shader.setSources(std::make_tuple("Engine/Renderable/Shaders/v_model_shader.vs", "Engine/Renderable/Shaders/f_model_shader.fs"));
//    gym.shader.compileSources();

//    suit.shader.setSources(std::make_tuple("Engine/Renderable/Shaders/v_model_shader.vs", "Engine/Renderable/Shaders/f_model_shader.fs"));
//    suit.shader.compileSources();

//    amie.shader.setSources(std::make_tuple("Engine/Renderable/Shaders/v_model_shader.vs", "Engine/Renderable/Shaders/f_model_shader.fs"));
//    amie.shader.compileSources();
//
//    logo.shader.setSources(std::make_tuple("Engine/Renderable/Shaders/v_model_shader.vs", "Engine/Renderable/Shaders/f_model_shader.fs"));
//    logo.shader.compileSources();
    #endif

    auto func = []() {
        std::cout << "KEK" << std::endl;
    };

    auto kitchenButton = std::make_shared<ImageButton>("Game/Resources/Pictures/cake-slice.png", ImVec2(64.0f, 64.0f), 5, true, func);
    auto homeButton = std::make_shared<ImageButton>("Game/Resources/Pictures/house.png", ImVec2(64.0f, 64.0f), 5, true, func);
    auto gymButton = std::make_shared<ImageButton>("Game/Resources/Pictures/muscle-up.png", ImVec2(128.0f, 128.0f), 5, true, func);
    auto socialButton = std::make_shared<ImageButton>("Game/Resources/Pictures/human-pyramid.png", ImVec2(64.0f, 64.0f), 5, true, func);
    auto battleButton = std::make_shared<ImageButton>("Game/Resources/Pictures/champions.png", ImVec2(64.0f, 64.0f), 5, true, func);

    navbar.addElement(std::move(kitchenButton));
    navbar.addElement(std::move(homeButton));
    navbar.addElement(std::move(gymButton));
    navbar.addElement(std::move(socialButton));
    navbar.addElement(std::move(battleButton));

    while (!glfwWindowShouldClose(screen.getWindow())) {
        double frame_start_time = glfwGetTime();
        screen.frameInit();

        ImGui::ShowDemoWindow();

        //authForm.render();

        //navbar.render();


//        pokemon.update(0.0);
//        pokemon.render();

//        trainer.update(0.0);
//        trainer.render();


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