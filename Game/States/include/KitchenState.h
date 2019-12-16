#ifndef POKE_RANCH_V2_KITCHEN_STATE_H_
#define POKE_RANCH_V2_KITCHEN_STATE_H_

#include "GameState.h"

class Engine;

class KitchenState : public GameState {
public:
    explicit KitchenState(Engine *parentEngine);
};

#endif //POKE_RANCH_V2_KITCHEN_STATE_H_