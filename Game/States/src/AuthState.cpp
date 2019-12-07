#include <iostream>
#include "AuthState.h"
#include "Form.h"

#include "Engine.h"

AuthState::AuthState(Engine *parentEngine) : GameState(parentEngine) {
    addElement(std::make_unique<Form>());
}