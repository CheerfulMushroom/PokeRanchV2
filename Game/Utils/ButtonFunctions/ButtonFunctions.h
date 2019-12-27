#ifndef UTILS_MOVE_FUNCS_H_
#define UTILS_MOVE_FUNCS_H_

#include <functional>
#include <memory>
#include "Engine.h"
#include "Pokemon.h"


template<class State>
void switchToState(Engine *engine);

void savePokemonProgress(std::map<std::string, std::string> pokemonInfo, Engine *engine);


#include <ButtonFunctions.hpp>

#endif  // UTILS_MOVE_FUNCS_H_