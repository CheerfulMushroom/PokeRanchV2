#ifndef POKE_RANCH_V2_POKEMON_SELECTION_STATE_H
#define POKE_RANCH_V2_POKEMON_SELECTION_STATE_H

#include "GameState.h"
#include "ServerAPI.h"
#include "ModelSwitcher.h"
#include "AnimModel.h"

class Engine;

class PokemonSelectionState : public GameState {
public:
    explicit PokemonSelectionState(Engine *parentEngine);

    void setNextScene(const std::shared_ptr<ModelSwitcher<AnimModel>>& modelSwitcher);
private:
    ServerAPI _api;
};


#endif //POKE_RANCH_V2_POKEMON_SELECTION_STATE_H