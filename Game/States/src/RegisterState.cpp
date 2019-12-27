#include <iostream>
#include "Form.h"
#include "InputText.h"
#include "Button.h"
#include "Model.h"
#include "Camera.h"
#include "Engine.h"
#include "Picture.h"

#include "TrainerSelectionState.h"
#include "RegisterState.h"
#include "AuthState.h"

#include "ServerAPI.h"

RegisterState::RegisterState(Engine* parentEngine) : GameState(parentEngine) {
    auto registrationForm = std::make_shared<Form>("RegisterForm");

    auto background = std::make_shared<Picture>(-1.0f, -1.0f, 2.0f, 2.0f, "Game/Resources/Pictures/registerBackground.png");
    addElement(background);


    auto loginInput = std::make_shared<InputText>("login", false, false);
    auto passwordInput = std::make_shared<InputText>("password", false, true);
    auto mailInput = std::make_shared<InputText>("mail", false, false);


    registrationForm->addElement(loginInput);
    registrationForm->addElement(passwordInput);
    registrationForm->addElement(mailInput);

    registrationForm->addElement(
            std::make_shared<Button>(
                    "Register",
                    std::bind(&RegisterState::registerUser, this, loginInput, passwordInput, mailInput)));


    auto switchToLogin = [this]() {
        auto authState = std::make_shared<AuthState>(_parentEngine);
        _parentEngine->setState(std::move(authState));
    };
    registrationForm->addElement(std::make_shared<Button>("Login", switchToLogin));


    addElement(registrationForm);
}

void RegisterState::registerUser(const std::shared_ptr<InputText>& loginInput,
                                 const std::shared_ptr<InputText>& passwordInput,
                                 const std::shared_ptr<InputText>& mailInput) {
    std::string login = loginInput->getBuffer();
    std::string password = passwordInput->getBuffer();
    std::string mail = mailInput->getBuffer();

    Answer_t response = _api.registration(login, password, mail);

    if (response.first != http::status::ok) {
        return;
    }

    auto selectState = std::make_shared<AuthState>(_parentEngine);
    _parentEngine->setState(std::move(selectState));
}
