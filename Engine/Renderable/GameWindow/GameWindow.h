#ifndef PROJECT_INCLUDE_GAMEWINDOW_H_
#define PROJECT_INCLUDE_GAMEWINDOW_H_

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


class GameWindow {
 public:
    explicit GameWindow(int width = 1280, int height = 1024);

    // Геттеры
    GLFWwindow* getWindow();

    std::pair<int, int> getWindowSize(); // ДОПИСАНО

 private:
    GLFWwindow *_window;
};

#endif
