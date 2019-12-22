#ifndef POKE_RANCH_V2_REGISTER_STATE_H
#define POKE_RANCH_V2_REGISTER_STATE_H

#include <memory>

#include "GameState.h"
#include "ServerAPI.h"
#include "InputText.h"


class Engine;

class RegisterState : public GameState {
public:
    explicit RegisterState(Engine* parentEngine);

    void registerUser(const std::shared_ptr<InputText>& loginInput,
                      const std::shared_ptr<InputText>& passwordInput,
                      const std::shared_ptr<InputText>& mailInput);

private:
    ServerAPI _api;
};

#endif //POKE_RANCH_V2_REGISTER_STATE_H
