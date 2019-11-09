#ifndef POKERANCHV2_IENGINE_H
#define POKERANCHV2_IENGINE_H

#include "IGameState.h"

class IEngine {
public:
    virtual ~IEngine() = default;
    virtual void setState(IGameState* newState) = 0;
    virtual void start() = 0;

protected:
    virtual void render() = 0;
    virtual void update(double dt) = 0;
};

#endif //POKERANCHV2_IENGINE_H
