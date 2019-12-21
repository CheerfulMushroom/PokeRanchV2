#include <iostream>
#include "AuthState.h"
#include "Form.h"
#include "InputText.h"
#include "Button.h"
#include "Model.h"
#include "Camera.h"
#include "Engine.h"

#include "HomeState.h"
#include "TrainerSelectionState.h"
#include "PokemonSelectionState.h"
#include "RegisterState.h"

AuthState::AuthState(Engine *parentEngine) : GameState(parentEngine) {
    // LOGIN FORM
    auto loginForm = std::make_shared<Form>();

    auto loginInput = std::make_shared<InputText>("login", false, false);
    auto passwordInput = std::make_shared<InputText>("password", false, true);

    auto loginCall = [this, loginInput, passwordInput]() {
        std::string login = loginInput->getBuffer();
        std::string password = passwordInput->getBuffer();
        _parentEngine->getSession()->setLogin(login);

        // в случае, если сервер не отмечает надо это ловить
        http::status result = _parentEngine->getSession()->auth(login, password);

        if (result != http::status::ok) {
            std::cout << "Error occured: " << result << std::endl;
            return;
        }

//        if (result == http::status::ok) {
//            auto homeState = std::make_shared<HomeState>(_parentEngine);
//            _parentEngine->setState(std::move(homeState));
//        } else {
//            // TODO
//            // подсветить форму ?
//        }

        _parentEngine->getSession()->getProfile(login);


        if (_parentEngine->getSession()->getPokemonName().empty()) {
            _parentEngine->setState(std::move(std::make_shared<PokemonSelectionState>(_parentEngine)));
            return;
        }

        if (_parentEngine->getSession()->getTrainerName().empty()) {
            _parentEngine->setState(std::move(std::make_shared<TrainerSelectionState>(_parentEngine)));
            return;
        }

        auto homeState = std::make_shared<HomeState>(_parentEngine);
        _parentEngine->setState(std::move(homeState));

    };

    auto registerCall = [this]() {
        auto registerState = std::make_shared<RegisterState>(_parentEngine);
        _parentEngine->setState(std::move(registerState));
    };


    loginForm->addElement(loginInput);
    loginForm->addElement(passwordInput);
    addElement(loginForm);

    loginForm->addElement(std::make_shared<Button>("submit", loginCall));
    loginForm->addElement(std::make_shared<Button>("register", registerCall));

    auto camera = std::make_shared<Camera>(glm::vec3(0.0f, 0.0f, 4.0f));

    int width = _parentEngine->getWindow()->getWindowSize().first;
    int height = _parentEngine->getWindow()->getWindowSize().second;


    auto logo = std::make_shared<Model>("Game/Resources/Models/Static/PokemonLogo/Logo.dae",
                                        camera.get(),
                                        glm::vec3(0.0f, 1.4f, -2.0f),
                                        0.006,
                                        glm::vec3(0.0f, 0.0f, 0.0f),
                                        width,
                                        height,
                                        std::string("logo"));

    addElement(std::move(camera));
    addElement(std::move(logo));
}