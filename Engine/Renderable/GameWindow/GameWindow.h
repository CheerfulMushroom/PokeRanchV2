#ifndef PROJECT_INCLUDE_GAMEWINDOW_H_
#define PROJECT_INCLUDE_GAMEWINDOW_H_

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <opencv2/opencv.hpp>

class GameWindow {
 public:
    explicit GameWindow(int width = 1280, int height = 720);
    ~GameWindow();

    GLFWwindow* getWindow();
    std::pair<int, int> getWindowSize();

    void clearWindowBuffers();
    void swapBuffers();
    void frameInit();
    void frameEnd();

    cv::Mat takeScreenshot();

 private:
    GLFWwindow *_window;
};

#endif
