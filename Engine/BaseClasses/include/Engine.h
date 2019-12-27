#ifndef POKERANCHV2_ENGINE_H
#define POKERANCHV2_ENGINE_H

#include <memory>

#include "GameState.h"
#include "GameWindow.h"

class Engine {
public:
    Engine(int width = 1024, int height = 720, int fps = 30);
    explicit Engine(std::shared_ptr<GameState> newState, int width = 1024, int height = 720, int fps = 30);
    ~Engine() = default;

    void setState(std::shared_ptr<GameState> newState);
    void start();

    void updateSessionInfo(const std::string& category, const std::map<std::string, std::string>& infoToUpdate);
    std::map<std::string, std::string> getSessionInfo(const std::string& category);


    GameWindow* getWindow();


protected:
    std::shared_ptr<GameState> _currState;
    GameWindow _window;
    std::map<std::string, std::map<std::string, std::string>> _sessionInfo;
    int _fps;
};

#endif //POKERANCHV2_ENGINE_H
