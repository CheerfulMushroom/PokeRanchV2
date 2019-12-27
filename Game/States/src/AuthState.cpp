#include <iostream>
#include "AuthState.h"
#include "Form.h"
#include "Picture.h"
#include "InputText.h"
#include "Button.h"
#include "Model.h"
#include "Camera.h"
#include "Engine.h"
#include "ServerAPI.h"

#include "HomeState.h"
#include "TrainerSelectionState.h"
#include "PokemonSelectionState.h"
#include "RegisterState.h"

AuthState::AuthState(Engine* parentEngine) : GameState(parentEngine) {
    /// LOGIN FORM


    auto background = std::make_shared<Picture>(-1.0f, -1.0f, 2.0f, 2.0f, "Game/Resources/Pictures/background.png");

    auto loginForm = std::make_shared<Form>("LoginForm");

    auto loginInput = std::make_shared<InputText>("login", false, false);
    auto passwordInput = std::make_shared<InputText>("password", false, true);

    addElement(background);

    loginForm->addElement(loginInput);
    loginForm->addElement(passwordInput);
    addElement(loginForm);

    loginForm->addElement(std::make_shared<Button>("submit",
                                                   std::bind(&AuthState::login, this, loginInput, passwordInput)));

    auto switchToRegistration = [this]() {
        auto registerState = std::make_shared<RegisterState>(_parentEngine);
        _parentEngine->setState(std::move(registerState));
    };
    loginForm->addElement(std::make_shared<Button>("register", switchToRegistration));

    /// LOGO
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

void AuthState::login(const std::shared_ptr<InputText>& loginInput,
                      const std::shared_ptr<InputText>& passwordInput) {
    std::string login = loginInput->getBuffer();
    std::string password = passwordInput->getBuffer();

    ServerAPI api;
    Answer_t response = api.auth(login, password);
    if (response.first != http::status::ok) {
        std::cout << "Error occurred: " << response.first << std::endl;
        return;
    }

    _parentEngine->updateSessionInfo("profile",
                                     {
                                             {"login",    login},
                                             {"password", password},
                                     });
    _parentEngine->updateSessionInfo("profile", response.second);

    /// UPDATE PROFILE INFO
    std::string token = _parentEngine->getSessionInfo("profile")["token"];
    response = api.getProfile(login, token);
    if (response.first != http::status::ok) {
        std::cout << "Error occurred: " << response.first << std::endl;
        return;
    }
    _parentEngine->updateSessionInfo("profile", response.second);


    /// UPDATE POKEMON INFO
    response = api.getPokemon(token);
    if (response.first == http::status::ok) {
        _parentEngine->updateSessionInfo("pokemon", response.second);
    }


    /// UPDATE TRAINER INFO
    response = api.getTrainer(token);
    if (response.first == http::status::ok) {
        _parentEngine->updateSessionInfo("trainer", response.second);
    }


    std::map<std::string, std::string> profileInfo = _parentEngine->getSessionInfo("profile");

    /// ADD POKEMON IF NONE
    if (profileInfo["pokemon_name"].empty()) {
        _parentEngine->setState(std::move(std::make_shared<PokemonSelectionState>(_parentEngine)));
        return;
    }

    /// ADD TRAINER IF NONE
    if (profileInfo["trainer_name"].empty()) {
        _parentEngine->setState(std::move(std::make_shared<TrainerSelectionState>(_parentEngine)));
        return;
    }


    auto homeState = std::make_shared<HomeState>(_parentEngine);
    _parentEngine->setState(std::move(homeState));
}
