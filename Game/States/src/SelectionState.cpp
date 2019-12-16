#define LeftButton 0
#define RightButton 1

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

static int idx = 0;

SelectionState::SelectionState(Engine *parentEngine) : GameState(parentEngine) {
    auto camera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 4.0f));

    int width = _parentEngine->getWindow()->getWindowSize().first;
    int height = _parentEngine->getWindow()->getWindowSize().second;

    auto model = std::make_unique<AnimModel>("Game/Resources/Models/Trainers/Scientist/scientist.dae",
                                                 camera.get(),
                                                 glm::vec3(0.0f, -1.0f, 0.0f),
                                                 0.012,
                                                 glm::vec3(0.0f, 0.0f, 0.0f),
                                                 width,
                                                 height,
                                                 std::string("model"));

    model->addMeta("modelToDelete", "true");

    auto camera_ptr = camera.get();



    auto changeModelToLeft = std::function<void()>([this, camera_ptr, width, height]() {
        static std::vector<std::string> paths = { "Game/Resources/Models/Trainers/Scientist/scientist.dae",
                                                  "Game/Resources/Models/Trainers/TrainerMale/avatar.dae",
                                                  "Game/Resources/Models/Trainers/Sophocles/stay.dae",
                                                  "Game/Resources/Models/Trainers/Molayne/stay.dae",
                                                  "Game/Resources/Models/Trainers/Sina/stay.dae",
                                                  "Game/Resources/Models/Trainers/Cook/stay.dae"};

        idx = (idx - 1);

        if (idx < 0) {
            idx = idx + paths.size();
        }

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


    });

    auto changeModelToRight = std::function<void()>([this, camera_ptr, width, height]() {
        static std::vector<std::string> paths = { "Game/Resources/Models/Trainers/Scientist/scientist.dae",
                                                  "Game/Resources/Models/Trainers/TrainerMale/avatar.dae",
                                                  "Game/Resources/Models/Trainers/Sophocles/stay.dae",
                                                  "Game/Resources/Models/Trainers/Molayne/stay.dae",
                                                  "Game/Resources/Models/Trainers/Sina/stay.dae",
                                                  "Game/Resources/Models/Trainers/Cook/stay.dae"};
        idx = (idx + 1) % paths.size();
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

    });


    auto deleteButtonLeft = std::make_unique<ImageButton>("Game/Resources/Pictures/arrowToLeft.png",
                                                      ImVec2(64.0f, 64.0f),
                                                      5, true, changeModelToLeft);

    auto deleteButtonRight = std::make_unique<ImageButton>("Game/Resources/Pictures/arrowToRight.png",
                                                          ImVec2(64.0f, 64.0f),
                                                          5, true, changeModelToRight);



    auto navbar = std::make_unique<NavBar>();
    navbar->addButton(std::move(deleteButtonLeft));
    navbar->addButton(std::move(deleteButtonRight));

    addElement(std::move(navbar));
    addElement(std::move(camera));
    addElement(std::move(model));
}