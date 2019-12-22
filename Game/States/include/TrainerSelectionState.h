#ifndef POKE_RANCH_V2_TRAINER_SELECTION_STATE_H
#define POKE_RANCH_V2_TRAINER_SELECTION_STATE_H

#include "GameState.h"
#include "ServerAPI.h"
#include "ModelSwitcher.h"
#include "AnimModel.h"

class Engine;

class TrainerSelectionState : public GameState {
public:
    explicit TrainerSelectionState(Engine *parentEngine);

    void nextScene(const std::shared_ptr<ModelSwitcher<AnimModel>>& modelSwitcher);
private:
    ServerAPI _api;
};


#endif //POKE_RANCH_V2_TRAINER_SELECTION_STATE_H