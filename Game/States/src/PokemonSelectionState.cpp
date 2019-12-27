#include "Engine.h"

#include "HomeState.h"
#include "AuthState.h"
#include "GymState.h"
#include "KitchenState.h"
#include "PokemonSelectionState.h"
#include "TrainerSelectionState.h"

#include "ImageButton.h"
#include "NavBar.h"
#include "Camera.h"
#include "Model.h"
#include "AnimModel.h"
#include "Picture.h"

#include "PathManager.h"
#include "ModelSwitcher.hpp"
#include "ServerAPI.h"


PokemonSelectionState::PokemonSelectionState(Engine* parentEngine) : GameState(parentEngine) {
    PathManager pathManager;

    auto background = std::make_shared<Picture>(-1.0f, -1.0f, 2.0f, 2.0f, "Game/Resources/Pictures/pokemonSelectBackground.png");
    addElement(std::move(background));

    auto camera = std::make_shared<Camera>(glm::vec3(0.0f, 0.0f, 4.0f));

    int width = _parentEngine->getWindow()->getWindowSize().first;
    int height = _parentEngine->getWindow()->getWindowSize().second;

    auto camera_ptr = camera.get();

    std::vector<std::string> pokemonsName = {"Pikachu",
                                             "Meowth",
                                             "Litten",
                                             "Vulpix"};

    auto modelSwitcher = std::make_shared<ModelSwitcher<AnimModel>>(*this,
                                                                    pokemonsName,
                                                                    camera_ptr,
                                                                    glm::vec3(-1.4f, -1.0f, 1.0f),
                                                                    0.024,
                                                                    glm::vec3(90.0f, 223.0f, 0.0f),
                                                                    width,
                                                                    height,
                                                                    "pokemon",
                                                                    "stay");


    auto makeChoice = [this, modelSwitcher]() {

    };

    auto switchLeft = std::make_shared<ImageButton>(pathManager.getPicturePath("arrowToLeft"),
                                                    ImVec2(64.0f, 64.0f),
                                                    5, true,
                                                    std::bind(&ModelSwitcher<AnimModel>::switchToLeft, modelSwitcher.get()));

    auto switchRight = std::make_shared<ImageButton>(pathManager.getPicturePath("arrowToRight"),
                                                     ImVec2(64.0f, 64.0f),
                                                     5, true,
                                                     std::bind(&ModelSwitcher<AnimModel>::switchToRight, modelSwitcher.get()));

    auto markChoice = std::make_shared<ImageButton>(pathManager.getPicturePath("check-mark"),
                                                    ImVec2(64.0f, 64.0f),
                                                    5, true,
                                                    std::bind(&PokemonSelectionState::setNextScene, this, modelSwitcher));

    auto navbar = std::make_shared<NavBar>();
    navbar->addElement(std::move(switchLeft));
    navbar->addElement(std::move(switchRight));
    navbar->addElement(std::move(markChoice));

    addElement(std::move(navbar));
    addElement(std::move(camera));
    addElement(std::move(modelSwitcher));
}

void PokemonSelectionState::setNextScene(const std::shared_ptr<ModelSwitcher<AnimModel>>& modelSwitcher) {
    std::string pokemonName = modelSwitcher->returnCurrentModelName();
    std::map<std::string, std::string> profileInfo = _parentEngine->getSessionInfo("profile");

    Answer_t response = _api.savePokemon({{"name", pokemonName}}, profileInfo["token"]);
    if (response.first != http::status::ok) {
        return;
    }

    response = _api.getPokemon(profileInfo["token"]);
    if (response.first != http::status::ok) {
        return;
    }

    _parentEngine->updateSessionInfo("pokemon", response.second);
    _parentEngine->updateSessionInfo("profile", {{"pokemon_name", pokemonName}});


    profileInfo = _parentEngine->getSessionInfo("profile");
    if (profileInfo["trainer_name"].empty()) {
        _parentEngine->setState(std::move(std::make_shared<TrainerSelectionState>(_parentEngine)));
        return;
    }

    auto homeState = std::make_shared<HomeState>(_parentEngine);
    _parentEngine->setState(std::move(homeState));
}
