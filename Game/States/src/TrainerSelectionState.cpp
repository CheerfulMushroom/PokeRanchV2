#include "Engine.h"

#include "HomeState.h"
#include "AuthState.h"
#include "GymState.h"
#include "KitchenState.h"
#include "TrainerSelectionState.h"
#include "PokemonSelectionState.h"

#include "ImageButton.h"
#include "NavBar.h"
#include "Camera.h"
#include "Model.h"
#include "AnimModel.h"

#include "PathManager.h"
#include "ModelSwitcher.h"
#include "ServerAPI.h"


// куда всунуть PathManager ?
TrainerSelectionState::TrainerSelectionState(Engine *parentEngine) : GameState(parentEngine) {
    PathManager pathManager;

    auto camera = std::make_shared<Camera>(glm::vec3(0.0f, 0.0f, 4.0f));

    int width = _parentEngine->getWindow()->getWindowSize().first;
    int height = _parentEngine->getWindow()->getWindowSize().second;


    auto camera_ptr = camera.get();

    std::vector<std::string> trainersName = {"Scientist",
                                             "Red",
                                             "Molayne",
                                             "Sina",
                                             "Sophocles",
                                             "Cook"};

    auto modelSwitcher = std::make_shared<ModelSwitcher<AnimModel>>(*this,
                                                                    trainersName,
                                                                    camera_ptr,
                                                                    glm::vec3(0.0f, -1.0f, 0.0f),
                                                                    0.012,
                                                                    glm::vec3(0.0f, 0.0f, 0.0f),
                                                                    width,
                                                                    height,
                                                                    "trainer",
                                                                    "stay");

    auto changeModelToLeft = [modelSwitcher]() {
        modelSwitcher->switchToLeft();
    };

    auto changeModelToRight = [modelSwitcher]() {
        modelSwitcher->switchToRight();
    };

    auto makeChoice = [this, modelSwitcher]() {
        std::string trainerName = modelSwitcher->returnCurrentModelName();

        ServerAPI api;
        std::map<std::string, std::string> profileInfo = _parentEngine->getSessionInfo("profile");

        Answer_t response = api.saveTrainer({{"name", trainerName}}, profileInfo["token"]);
        if (response.first != http::status::ok) {
            return;
        }

        response = api.getTrainer(profileInfo["token"]);
        if (response.first != http::status::ok) {
            return;
        }

        _parentEngine->updateSessionInfo("trainer", response.second);
        _parentEngine->updateSessionInfo("profile", {{"trainer_name", trainerName}});


        profileInfo = _parentEngine->getSessionInfo("profile");
        if (profileInfo["pokemon_name"].empty()) {
            _parentEngine->setState(std::move(std::make_shared<TrainerSelectionState>(_parentEngine)));
            return;
        }

        auto homeState = std::make_shared<HomeState>(_parentEngine);
        _parentEngine->setState(std::move(homeState));
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