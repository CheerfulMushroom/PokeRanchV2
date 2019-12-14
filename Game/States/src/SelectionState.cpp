#include "Engine.h"

#include "HomeState.h"
#include "AuthState.h"
#include "GymState.h"
#include "KitchenState.h"
#include "SelectionState.h"

#include "ImageButton.h"
#include "NavBar.h"
#include "Camera.h"
#include "Model.h"
#include "AnimModel.h"

SelectionState::SelectionState(Engine *parentEngine) : GameState(parentEngine) {
    auto camera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 4.0f));

    int width = _parentEngine->getWindow()->getWindowSize().first;
    int height = _parentEngine->getWindow()->getWindowSize().second;

    auto scientist = std::make_unique<AnimModel>("Game/Resources/Models/Scientist/scientist.dae",
                                                 camera.get(),
                                                 glm::vec3(0.0f, -1.0f, 0.0f),
                                                 0.012,
                                                 glm::vec3(0.0f, 0.0f, 0.0f),
                                                 width,
                                                 height,
                                                 std::string("scientist"));

    scientist->addMeta("modelToDelete", "true");

    auto camera_ptr = camera.get();

    auto deleteScientist = std::function<void()>([this, camera_ptr, width, height]() {
        static std::vector<std::string> paths = {"Game/Resources/Models/TrainerMale/avatar.dae",
                                                 "Game/Resources/Models/Scientist/scientist.dae"};
        static  int idx = 0;
        std::string currModel = paths[idx];


        deleteElement([](GameElement *el) {
            return el->getMeta("modelToDelete") == "true";
        });

        auto newModel = std::make_unique<AnimModel>(currModel,
                                                     camera_ptr,
                                                     glm::vec3(0.0f, -1.0f, 0.0f),
                                                     0.012,
                                                     glm::vec3(0.0f, 0.0f, 0.0f),
                                                     width,
                                                     height,
                                                     std::string("SwitchingModel"));

        newModel->addMeta("modelToDelete", "true");
        addElement(std::move(newModel));

        idx = (idx + 1) % paths.size();
    });

    auto deleteButton = std::make_unique<ImageButton>("Game/Resources/Pictures/cake-slice.png",
                                                      ImVec2(64.0f, 64.0f),
                                                      5, true, deleteScientist);

    auto navbar = std::make_unique<NavBar>();
    navbar->addButton(std::move(deleteButton));

    addElement(std::move(navbar));
    addElement(std::move(camera));
    addElement(std::move(scientist));
}