#ifndef POKERANCHV2_IGAMESTATE_H
#define POKERANCHV2_IGAMESTATE_H

#include <functional>

#include "IGameElement.h"

class IGameState {
public:
    virtual ~IGameState() = default;
    virtual void addElement(IGameElement* element) = 0;
    virtual bool deleteElement(std::function<bool(IGameElement*)> cmp) = 0;
    virtual int getElementsAmount() = 0;

    virtual void render() = 0;
    virtual void update(double dt) = 0;
};

#endif //POKERANCHV2_IGAMESTATE_H
