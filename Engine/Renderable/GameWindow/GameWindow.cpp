#include <iostream>

#include "GameWindow.h"

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

    int frame_width = 0;
    int frame_height = 0;

    glfwGetFramebufferSize(_window, &frame_width, &frame_height);

    glViewport(0, 0, frame_width, frame_height);
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