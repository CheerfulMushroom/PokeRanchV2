#ifndef POKERANCHV2_HOMESTATE_H
#define POKERANCHV2_HOMESTATE_H

#include <memory>
#include "GameState.h"
#include "ServerAPI.h"
#include "Pokemon.h"

class Engine;

class HomeState : public GameState {
public:
    explicit HomeState(Engine *parentEngine);
    ~HomeState();
};

#endif //POKERANCHV2_HOMESTATE_H
