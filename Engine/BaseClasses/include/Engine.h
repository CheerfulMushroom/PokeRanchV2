#ifndef POKERANCHV2_ENGINE_H
#define POKERANCHV2_ENGINE_H

#include "GameState.h"

class Engine {
public:
    Engine() = default;
    explicit Engine(std::unique_ptr<GameState> newState);
    ~Engine() = default;

    void setState(std::unique_ptr<GameState> newState);
    void start();

protected:
    void render();
    void update(double dt);

    std::unique_ptr<GameState> _currState;
};

#endif //POKERANCHV2_ENGINE_H
