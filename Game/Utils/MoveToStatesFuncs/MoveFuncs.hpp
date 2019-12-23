#ifndef UTILS_MOVE_FUNCS_HPP_
#define UTILS_MOVE_FUNCS_HPP_

#include <Engine.h>

template <class State>
void switchToState(Engine *engine) {
    auto newState = std::make_shared<State>(engine);
       engine->setState(std::move(newState));
}

#endif  // UTILS_MOVE_FUNCS_HPP_