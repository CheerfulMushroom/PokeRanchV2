#ifndef POKERANCHV2_GYMSTATE_H
#define POKERANCHV2_GYMSTATE_H

#include "GameState.h"

class Engine;

class GymState : public GameState {
public:
    explicit GymState(Engine *parentEngine);
};

#endif //POKERANCHV2_GYMSTATE_H
