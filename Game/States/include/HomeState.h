#ifndef POKERANCHV2_HOMESTATE_H
#define POKERANCHV2_HOMESTATE_H

#include "GameState.h"

class Engine;

class HomeState : public GameState {
public:
    explicit HomeState(Engine *parentEngine);
};

#endif //POKERANCHV2_HOMESTATE_H
