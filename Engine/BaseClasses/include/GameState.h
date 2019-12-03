#ifndef POKERANCHV2_GAMESTATE_H
#define POKERANCHV2_GAMESTATE_H

#include <functional>
#include <memory>
#include <vector>

#include "GameElement.h"

class GameState {
public:
    GameState();
    virtual ~GameState() = default;

    void addElement(std::unique_ptr<GameElement> element);
    bool deleteElement(const std::function<bool(GameElement *)> &cmp);
    int getElementsAmount();

    void render();
    void update(double dt);
    std::string getName();

protected:
    std::vector<std::unique_ptr<GameElement>> _elements;
    std::string _stateName;
};

#endif //POKERANCHV2_GAMESTATE_H
