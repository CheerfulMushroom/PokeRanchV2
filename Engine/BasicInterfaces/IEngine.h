#ifndef POKERANCHV2_IENGINE_H
#define POKERANCHV2_IENGINE_H

#include "IGameState.h"

class IEngine {
public:
    void setState(IGameState newState);
    void start();

protected:
    void render();
    void update(double dt);
};

#endif //POKERANCHV2_IENGINE_H
