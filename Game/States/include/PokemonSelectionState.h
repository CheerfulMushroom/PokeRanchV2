#ifndef POKE_RANCH_V2_POKEMON_SELECTION_STATE_H
#define POKE_RANCH_V2_POKEMON_SELECTION_STATE_H

#include "GameState.h"

class Engine;

class PokemonSelectionState : public GameState {
public:
    explicit PokemonSelectionState(Engine *parentEngine);
};


#endif //POKE_RANCH_V2_POKEMON_SELECTION_STATE_H