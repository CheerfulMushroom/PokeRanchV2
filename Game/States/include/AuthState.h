#ifndef POKERANCHV2_AUTHSTATE_H
#define POKERANCHV2_AUTHSTATE_H

#include "GameState.h"
#include "ServerAPI.h"
#include "InputText.h"

class Engine;

class AuthState : public GameState {
public:
    explicit AuthState(Engine* parentEngine);

    void login(const std::shared_ptr<InputText>& loginInput,
               const std::shared_ptr<InputText>& passwordInput);
private:
    ServerAPI _api;
};


#endif //POKERANCHV2_AUTHSTATE_H
