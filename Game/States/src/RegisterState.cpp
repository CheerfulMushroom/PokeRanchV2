
#include <iostream>
#include "Form.h"
#include "InputText.h"
#include "Button.h"
#include "Model.h"
#include "Camera.h"
#include "Engine.h"

#include "TrainerSelectionState.h"
#include "RegisterState.h"
#include "AuthState.h"

#include "ServerAPI.h"

RegisterState::RegisterState(Engine* parentEngine) : GameState(parentEngine) {
    auto registrationForm = std::make_shared<Form>();

    auto loginInput = std::make_shared<InputText>("login", false, false);
    auto passwordInput = std::make_shared<InputText>("password", false, true);
    auto mailInput = std::make_shared<InputText>("mail", false, false);

    auto registerCall = [this, loginInput, passwordInput, mailInput]() {
        std::string login = loginInput->getBuffer();
        std::string password = passwordInput->getBuffer();
        std::string mail = mailInput->getBuffer();

        ServerAPI api;
        Answer_t response = api.registration(login, password, mail);

        if (response.first != http::status::ok) {
            return;
        }

        auto selectState = std::make_shared<AuthState>(_parentEngine);
        _parentEngine->setState(std::move(selectState));
    };

    auto authCall = [this]() {
        auto authState = std::make_shared<AuthState>(_parentEngine);
        _parentEngine->setState(std::move(authState));
    };

    registrationForm->addElement(loginInput);
    registrationForm->addElement(passwordInput);
    registrationForm->addElement(mailInput);

    registrationForm->addElement(std::make_shared<Button>("logfgin", authCall));
    registrationForm->addElement(std::make_shared<Button>("register", registerCall));
    //registrationForm->addElement(std::make_shared<Button>("login", authCall));

    addElement(registrationForm);
}