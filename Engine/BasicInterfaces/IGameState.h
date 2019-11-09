#ifndef POKERANCHV2_IGAMESTATE_H
#define POKERANCHV2_IGAMESTATE_H

#include <functional>

#include "IGameElement.h"

class IGameState {
public:
    void addElement(IGameElement element);
    bool deleteElement(std::function<bool()> cmp);
    int getElementsAmount();

    void render();
    void update(double dt);
};

#endif //POKERANCHV2_IGAMESTATE_H
