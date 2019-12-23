#ifndef POKE_RANCH_V2_KITCHEN_STATE_H_
#define POKE_RANCH_V2_KITCHEN_STATE_H_

#include <memory>
#include "GameState.h"
#include "ServerAPI.h"
#include "Pokemon.h"

class Engine;

class KitchenState : public GameState {
public:
    explicit KitchenState(Engine *parentEngine);
};

#endif //POKE_RANCH_V2_KITCHEN_STATE_H_