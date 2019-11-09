#include "AuthState.h"

AuthState::AuthState() {};

void AuthState::addElement(IGameElement* element) {
    _elements.push_back(element);
}

bool AuthState::deleteElement(std::function<bool(IGameElement*)> cmp) {
    for (size_t i = 0; i < _elements.size(); i++) {
        if (cmp(_elements[i])) {
            delete _elements[i];
            _elements.erase(_elements.begin() + i);
            return true;
        }
    }
    return false;
}

int AuthState::getElementsAmount() {
    return _elements.size();
}

void AuthState::render() {}

void AuthState::update(double dt) {}