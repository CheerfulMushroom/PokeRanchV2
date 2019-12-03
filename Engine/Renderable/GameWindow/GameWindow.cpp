#include <iostream>

#include "GameWindow.h"
#include <opencv2/opencv.hpp>
#include <GL/glew.h>
#include <imgui.h>
#include <imgui_impl_glfw_gl3.h>

GameWindow::GameWindow(int width, int height) {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    _window = glfwCreateWindow(width, height, "PokeRanch", nullptr, nullptr);

    if (_window == nullptr) {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent(_window);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cout << "Failed to init GLEW" << std::endl;
        glfwTerminate();
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    glDisable(GL_CULL_FACE);
//    glCullFace(GL_FRONT_AND_BACK);

    int frame_width = 0;
    int frame_height = 0;

    glfwGetFramebufferSize(_window, &frame_width, &frame_height);

    glViewport(0, 0, frame_width, frame_height);

    ImGui::CreateContext();
    ImGui_ImplGlfwGL3_Init(_window, true);
    ImGui::StyleColorsDark();
}

GLFWwindow* GameWindow::getWindow() {
    return _window;
}

std::pair<int, int> GameWindow::getWindowSize() {
    int width = 0;
    int height = 0;

    glfwGetWindowSize(_window, &width, &height);

    return std::make_pair(width, height);
}

void GameWindow::clearWindowBuffers() {
    glClearColor(0.5f, 0.4f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GameWindow::swapBuffers() {
    glfwSwapBuffers(_window);
}

void GameWindow::frameInit() {
    clearWindowBuffers();
    ImGui_ImplGlfwGL3_NewFrame();
}

void GameWindow::frameEnd() {
    ImGui::Render();
    ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
    swapBuffers();
    glfwPollEvents();
}

cv::Mat GameWindow::takeScreenshot() {
    std::pair<int, int> windowSize = getWindowSize();

    int width = std::get<0>(windowSize);
    int height = std::get<1>(windowSize);

    cv::Mat img(height, width, CV_8UC3);

    glPixelStorei(GL_PACK_ALIGNMENT, (img.step & 3) ? 1 : 4);
    glPixelStorei(GL_PACK_ROW_LENGTH, img.step / img.elemSize());

    glReadPixels(0, 0, img.cols, img.rows, GL_BGR_EXT, GL_UNSIGNED_BYTE, img.data);

    cv::Mat flipped;
    cv::flip(img, flipped, 0);

    return flipped;
}

GameWindow::~GameWindow() {
    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
}