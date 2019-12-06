#ifdef DEBUG_ENGINE

#include <iostream>

#endif

#include <chrono>
#include <thread>

#include "BaseClasses/include/Engine.h"


/********************************************************
 * PUBLIC
 ********************************************************/


Engine::Engine() : _window() {}

Engine::Engine(std::unique_ptr<GameState> newState) : _currState(std::move(newState)),
                                                      _window() {
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
        update(timeDelta);
        render();

        //TODO(al):remove this
        std::this_thread::sleep_for (std::chrono::milliseconds(1/60));
    }

}


/********************************************************
 * PRIVATE
 ********************************************************/


void Engine::render() {
    _window.frameInit();
    _currState->render();
    _window.frameEnd();
}

void Engine::update(double dt) {
    _currState->update(dt);
}


