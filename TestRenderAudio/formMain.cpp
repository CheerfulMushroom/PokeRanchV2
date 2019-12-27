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
#include <Picture.h>

#define FPS 60

static unsigned int texture_from_file(const std::string &path) {  // Перенести в utils
    unsigned int texture_id;
    glGenTextures(1, &texture_id);

    cv::Mat image = cv::imread(path);

    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.cols, image.rows, 0, GL_BGR, GL_UNSIGNED_BYTE, image.ptr());

    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    cv::flip(image, image, 0);

    glBindTexture(GL_TEXTURE_2D, 0);

    return texture_id;
}

int main() {
    GameWindow screen(1366, 768);
    Form authForm("lol");
    NavBar navbar;


    Camera camera(glm::vec3(0.0f, 0.0f, 4.0f));

    std::pair<int, int> WindowSize = screen.getWindowSize();

    int width = std::get<0>(WindowSize);
    int height = std::get<1>(WindowSize);

    Form formBar("lol1");

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

//    add_element(std::make_unique<Picture>(-1.0f, -1.0f, 2.0f, 2.0f,
//                                          "project/pictures/main_screen.png"));

    Picture background(-1.0f, -1.0f, 2.0f, 2.0f, "Game/Resources/Pictures/background.png");

    while (!glfwWindowShouldClose(screen.getWindow())) {
        double frame_start_time = glfwGetTime();
        screen.frameInit();

        //ImGui::ShowDemoWindow();
        formBar.render();

        background.render();

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