#ifdef DEBUG_GAME_STATE
#include <iostream>
#endif

#include "GameState.h"


GameState::GameState() : _stateName("Default state") {}


void GameState::addElement(std::unique_ptr<GameElement> element) {
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

std::string GameState::getName() {
    return _stateName;
}


void GameState::update(double dt) {
    for (const auto& el: _elements) {
        el->update(dt);
    }
}

void GameState::render() {
    for (const auto& el: _elements) {
        el->render();
    }
}



