#ifdef DEBUG_GAME_ELEMENT
#include <iostream>
#endif

#include "GameElement.h"

/********************************************************
 * PUBLIC
 ********************************************************/


GameElement::GameElement(std::map<std::string, std::string> meta) : _meta(std::move(meta)) {}

std::string GameElement::getMeta(const std::string &key) {
    if (_meta.count(key) == 1) {
        return _meta[key];
    }
    return "";
}

bool GameElement::addMeta(const std::string &key, const std::string &value) {
    if (_meta.count(key) == 0) {
        _meta[key] = value;
#ifdef DEBUG_GAME_ELEMENT
        std::cout << "Added meta: " << key << " = " << value << std::endl;
#endif
        return true;
    }
    return false;
}

bool GameElement::isClicked() {
    return false;
}

double GameElement::getDistance() {
    return -1;
}

void GameElement::exec() {
#ifdef DEBUG_GAME_ELEMENT
    std::cout << "Executing element id: " << getMeta("id") << std::endl;
#endif
}

void GameElement::render() {}

void GameElement::update(double dt) {}

