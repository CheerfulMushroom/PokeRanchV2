#ifdef DEBUG_ENGINE

#include <iostream>

#endif

#include <chrono>
#include <thread>

#include "BaseClasses/include/Engine.h"


/********************************************************
 * PUBLIC
 ********************************************************/


Engine::Engine(int width, int height, int fps) :
        _window(width, height),
        _fps(fps) {}

Engine::Engine(std::unique_ptr<GameState> newState, int width, int height, int fps) :
        _currState(std::move(newState)),
        _window(width, height),
        _fps(fps) {
#ifdef DEBUG_ENGINE
    std::cout << "Engine state is set to: " << _currState->getName() << std::endl;
#endif
}

void Engine::setState(std::unique_ptr<GameState> newState) {
    _currState = std::move(newState);
#ifdef DEBUG_ENGINE
    std::cout << "Engine state is set to: " << _currState->getName() << std::endl;
#endif
}

void Engine::start() {
#ifdef DEBUG_ENGINE
    std::cout << "Engine started" << std::endl;
#endif

    auto lastUpdateTime = std::chrono::high_resolution_clock::now();
    while (!glfwWindowShouldClose(_window.getWindow())) {
        auto now = std::chrono::high_resolution_clock::now();
        double timeDelta = std::chrono::duration<double, std::milli>(now - lastUpdateTime).count();
        lastUpdateTime = now;

        _window.frameInit();
        _currState->update(timeDelta);
        _currState->render();
        _currState->pollElements();
        _window.frameEnd();


        //TODO(al):remove this
        std::this_thread::sleep_for(std::chrono::milliseconds(1 / _fps));
    }

}

GameWindow *Engine::getWindow() {
    return &_window;
}

/********************************************************
 * PRIVATE
 ********************************************************/

