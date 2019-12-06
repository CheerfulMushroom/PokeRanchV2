#ifndef POKERANCHV2_ENGINE_H
#define POKERANCHV2_ENGINE_H

#include <memory>

#include "GameState.h"
#include "Renderable/GameWindow/GameWindow.h"

class Engine {
public:
    Engine();
    explicit Engine(std::unique_ptr<GameState> newState);
    ~Engine() = default;

    void setState(std::unique_ptr<GameState> newState);
    void start();

protected:
    void render();
    void update(double dt);

    std::unique_ptr<GameState> _currState;
    GameWindow _window;
};

#endif //POKERANCHV2_ENGINE_H
