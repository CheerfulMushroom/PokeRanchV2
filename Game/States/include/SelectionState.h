#ifndef POKE_RANCH_V2_SELECTION_STATE_H
#define POKE_RANCH_V2_SELECTION_STATE_H

#include "GameState.h"

class Engine;

class SelectionState : public GameState {
public:
    explicit SelectionState(Engine *parentEngine);
};


#endif //POKE_RANCH_V2_REGISTER_STATE_H