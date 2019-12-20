#ifndef POKE_RANCH_V2_TRAINER_SELECTION_STATE_H
#define POKE_RANCH_V2_TRAINER_SELECTION_STATE_H

#include "GameState.h"

class Engine;

class TrainerSelectionState : public GameState {
public:
    explicit TrainerSelectionState(Engine *parentEngine);
};


#endif //POKE_RANCH_V2_TRAINER_SELECTION_STATE_H