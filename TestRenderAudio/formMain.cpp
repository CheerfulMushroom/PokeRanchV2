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
#include <ProgressBar.h>


#define FPS 60

int main() {
    GameWindow screen(1280, 1024);
    Form authForm;
    NavBar navbar;

    Camera camera(glm::vec3(0.0f, 0.0f, 4.0f));

    std::pair<int, int> WindowSize = screen.getWindowSize();

    int width = std::get<0>(WindowSize);
    int height = std::get<1>(WindowSize);

    Form formBar;

    auto lB = std::make_shared<ProgressBar>(ImVec2(300.0f, 0.0f), "loyalty");
    lB->setProgress(0.5f);
    lB->setCapacity(150.0f);

    formBar.addElement(lB);

    auto sB = std::make_shared<ProgressBar>(ImVec2(300.0f, 0.0f), "satiety");
    sB->setProgress(0.3f);
    sB->setCapacity(50.0f);

    formBar.addElement(sB);

    auto hB = std::make_shared<ProgressBar>(ImVec2(300.0f, 0.0f), "health");
    hB->setProgress(0.1f);
    hB->setCapacity(100.0f);

    formBar.addElement(hB);

    while (!glfwWindowShouldClose(screen.getWindow())) {
        double frame_start_time = glfwGetTime();
        screen.frameInit();


        formBar.render();

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