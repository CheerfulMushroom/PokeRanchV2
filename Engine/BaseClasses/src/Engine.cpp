#ifdef DEBUG_ENGINE

#include <iostream>

#endif

#include <ctime>

#include "Engine.h"

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

    //TODO(al): add game loop
//    while (true) {
//
//    }

}

void Engine::render() {

}

void Engine::update(double dt) {

}

