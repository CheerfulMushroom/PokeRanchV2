#ifdef DEBUG_GAME_STATE
#include <iostream>
#endif

#include "GameState.h"
#include "Engine.h"


/********************************************************
 * PUBLIC
 ********************************************************/

GameState::GameState(Engine *parentEngine) : _parentEngine(parentEngine),
                                             _stateName("Default state") {}

void GameState::addElement(std::shared_ptr<GameElement> element) {
#ifdef DEBUG_GAME_STATE
    std::cout << "Adding element id: "
              << element->getMeta("id") << std::endl;
#endif

    _elements.push_back(std::move(element));

#ifdef DEBUG_GAME_STATE
    std::cout << "Added element id: "
              << _elements[_elements.size() - 1]->getMeta("id") << std::endl;
#endif
}

bool GameState::deleteElement(const std::function<bool(GameElement *)> &cmp) {
    for (size_t i = 0; i < _elements.size(); i++) {
        if (cmp(_elements[i].get())) {
            _elements.erase(_elements.begin() + i);
            return true;
        }
    }
    return false;
}

int GameState::getElementsAmount() {
    return _elements.size();
}

void GameState::update(double dt) {
    for (const auto &el: _elements) {
        el->update(dt);
    }
}

void GameState::render() {
    for (const auto &el: _elements) {
        el->render();
    }
}

void GameState::pollElements() {
    std::vector<std::pair<std::shared_ptr<GameElement>&, double>> contenders;

    for (std::shared_ptr<GameElement> &element: _elements) {
        if (element->isClicked()) {
            contenders.emplace_back(element, element->getDistance());
        }
    }

    if (!contenders.empty()) {
        size_t minIdx = 0;
        double minDistance = contenders[0].second;

        for (size_t i = 0; i < contenders.size(); i++) {
            if (contenders[i].second < minDistance) {
                minDistance = contenders[i].second;
                minIdx = i;
            }
        }

        contenders[minIdx].first->exec();
    }
}

std::string GameState::getName() {
    return _stateName;
}


