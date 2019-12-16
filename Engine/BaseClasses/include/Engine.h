#ifndef POKERANCHV2_ENGINE_H
#define POKERANCHV2_ENGINE_H

#include <memory>

#include "GameState.h"
#include "GameWindow.h"

class Engine {
public:
    Engine(int width = 1024, int height=720, int fps=30);
    explicit Engine(std::unique_ptr<GameState> newState, int width = 1024, int height=720, int fps=30);
    ~Engine() = default;

    void setState(std::unique_ptr<GameState> newState);
    void start();

    GameWindow* getWindow();

protected:
    std::unique_ptr<GameState> _currState;
    GameWindow _window;
    int _fps;
};

#endif //POKERANCHV2_ENGINE_H
