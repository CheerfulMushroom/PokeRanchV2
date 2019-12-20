#ifndef POKERANCHV2_ENGINE_H
#define POKERANCHV2_ENGINE_H

#include <memory>

#include "GameState.h"
#include "GameWindow.h"
#include "UserSession.h"

class Engine {
public:
    Engine(int width = 1024, int height=720, int fps=30);
    explicit Engine(std::shared_ptr<GameState> newState, int width = 1024, int height=720, int fps=30);
    ~Engine() = default;

    void setState(std::shared_ptr<GameState> newState);

    void start();

    GameWindow* getWindow();
    UserSession* getSession();

protected:
    std::shared_ptr<GameState> _currState;
    GameWindow _window;
    UserSession _session;
    int _fps;
};

#endif //POKERANCHV2_ENGINE_H
