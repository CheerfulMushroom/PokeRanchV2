#ifdef DEBUG_ENGINE

#include <iostream>

#endif

#include <chrono>

#include "Engine.h"


/********************************************************
 * PUBLIC
 ********************************************************/


Engine::Engine(std::unique_ptr<GameState> newState) : _currState(std::move(newState)) {
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
    while (true) {
        auto now = std::chrono::high_resolution_clock::now();
        double timeDelta = std::chrono::duration<double, std::milli>(now - lastUpdateTime).count();
        lastUpdateTime = now;
        update(timeDelta);
        render();
    }

}


/********************************************************
 * PRIVATE
 ********************************************************/


void Engine::render() {
    _currState->render();
}

void Engine::update(double dt) {
    _currState->update(dt);
}
