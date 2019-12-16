#include <iostream>
#include "AuthState.h"
#include "Form.h"
#include "Model.h"
#include "Camera.h"
#include "Engine.h"

AuthState::AuthState(Engine *parentEngine) : GameState(parentEngine) {
    addElement(std::make_unique<Form>());

    auto camera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 4.0f));

    int width = _parentEngine->getWindow()->getWindowSize().first;
    int height = _parentEngine->getWindow()->getWindowSize().second;


    auto logo = std::make_unique<Model>("Game/Resources/Models/PokemonLogo/Logo.dae",
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