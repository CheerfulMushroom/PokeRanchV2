#ifndef POKERANCHV2_GAMESTATE_H
#define POKERANCHV2_GAMESTATE_H

#include <functional>
#include <memory>
#include <vector>

#include "GameElement.h"

class Engine;

class GameState {
public:
    explicit GameState(Engine* parent);
    virtual ~GameState() = default;

    void addElement(std::unique_ptr<GameElement> element);
    bool deleteElement(const std::function<bool(GameElement *)> &cmp);
    int getElementsAmount();

    void render();
    void update(double dt);
    void pollElements();

    std::string getName();

protected:
    Engine* _parentEngine;
    std::vector<std::unique_ptr<GameElement>> _elements;
    std::string _stateName;
};

#endif //POKERANCHV2_GAMESTATE_H
