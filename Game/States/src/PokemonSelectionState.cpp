#include "Engine.h"

#include "HomeState.h"
#include "AuthState.h"
#include "GymState.h"
#include "KitchenState.h"
#include "PokemonSelectionState.h"

#include "ImageButton.h"
#include "NavBar.h"
#include "Camera.h"
#include "Model.h"
#include "AnimModel.h"

#include "PathManager.h"
#include "ModelSwitcher.hpp"

// куда всунуть PathManager ?
PokemonSelectionState::PokemonSelectionState(Engine *parentEngine) : GameState(parentEngine) {
    PathManager pathManager;

    auto camera = std::make_shared<Camera>(glm::vec3(0.0f, 0.0f, 4.0f));

    int width = _parentEngine->getWindow()->getWindowSize().first;
    int height = _parentEngine->getWindow()->getWindowSize().second;

    auto camera_ptr = camera.get();

    std::vector<std::string> pokemonsName = { "Pikachu",
                                              "Meowth",
                                              "Litten" };

    auto modelSwitcher = std::make_shared<ModelSwitcher<AnimModel>>(*this,
                                           pokemonsName,
                                           camera_ptr,
                                           glm::vec3(0.0f, -1.0f, 0.0f),
                                           0.02,
                                           glm::vec3(90.0f, 180.0f, 0.0f),
                                           width,
                                           height,
                                           "pokemon",
                                           "stay");

    auto changeModelToLeft = [modelSwitcher]() {
        modelSwitcher->switchToLeft();
    };

    auto changeModelToRight = [modelSwitcher]() {
        modelSwitcher->switchToRight();
    };

    auto makeChoice = [this, modelSwitcher]() {
        std::string pokemonName = modelSwitcher->returnCurrentModelName();
        this->_parentEngine->getSession()->addPokemon(pokemonName);

        // теперь в HomeState
    };
    
    auto switchLeft = std::make_shared<ImageButton>(pathManager.getPicturePath("arrowToLeft"),
                                                    ImVec2(64.0f, 64.0f),
                                                    5, true, changeModelToLeft);

    auto switchRight = std::make_shared<ImageButton>(pathManager.getPicturePath("arrowToRight"),
                                                     ImVec2(64.0f, 64.0f),
                                                     5, true, changeModelToRight);

    auto markChoice = std::make_shared<ImageButton>(pathManager.getPicturePath("check-mark"),
                                                    ImVec2(64.0f, 64.0f),
                                                    5, true, makeChoice);

    auto navbar = std::make_shared<NavBar>();
    navbar->addElement(std::move(switchLeft));
    navbar->addElement(std::move(switchRight));
    navbar->addElement(std::move(markChoice));

    addElement(std::move(navbar));
    addElement(std::move(camera));
    addElement(std::move(modelSwitcher));
}