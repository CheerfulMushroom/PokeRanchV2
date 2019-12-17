#include <iostream>
#include "AuthState.h"
#include "Form.h"
#include "InputText.h"
#include "Button.h"
#include "Model.h"
#include "Camera.h"
#include "Engine.h"

AuthState::AuthState(Engine *parentEngine) : GameState(parentEngine) {
    // LOGIN FORM
    auto loginForm = std::make_shared<Form>();

    auto loginInput = std::make_shared<InputText>("login", false, false);
    auto passwordInput = std::make_shared<InputText>("password", false, true);

    auto printInfo = [loginInput, passwordInput]() {
        std::cout << "Login: " << loginInput->getBuffer()
                  << "; Password: " << passwordInput->getBuffer() << std::endl;
    };

    loginForm->addElement(loginInput);
    loginForm->addElement(passwordInput);
    addElement(loginForm);
    loginForm->addElement(std::make_shared<Button>("submit", printInfo));


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