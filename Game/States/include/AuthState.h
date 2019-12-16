#ifndef POKERANCHV2_AUTHSTATE_H
#define POKERANCHV2_AUTHSTATE_H

#include "GameState.h"

class Engine;

class AuthState : public GameState {
public:
    explicit AuthState(Engine *parentEngine);
};


#endif //POKERANCHV2_AUTHSTATE_H
