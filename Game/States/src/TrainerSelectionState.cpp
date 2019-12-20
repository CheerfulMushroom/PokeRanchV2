#include "Engine.h"

#include "HomeState.h"
#include "AuthState.h"
#include "GymState.h"
#include "KitchenState.h"
#include "TrainerSelectionState.h"

#include "ImageButton.h"
#include "NavBar.h"
#include "Camera.h"
#include "Model.h"
#include "AnimModel.h"

#include "PathManager.h"

static int idx = 0;

// куда всунуть PathManager ?
TrainerSelectionState::TrainerSelectionState(Engine *parentEngine) : GameState(parentEngine) {
    PathManager pathManager;

    auto camera = std::make_shared<Camera>(glm::vec3(0.0f, 0.0f, 4.0f));

    int width = _parentEngine->getWindow()->getWindowSize().first;
    int height = _parentEngine->getWindow()->getWindowSize().second;

    auto model = std::make_shared<AnimModel>("Game/Resources/Models/Trainers/Scientist/stay.dae",
                                                 camera.get(),
                                                 glm::vec3(0.0f, -1.0f, 0.0f),
                                                 0.012,
                                                 glm::vec3(0.0f, 0.0f, 0.0f),
                                                 width,
                                                 height,
                                                 std::string("model"));

    model->addMeta("modelToDelete", "true");

    auto camera_ptr = camera.get();

    auto changeModelToLeft = std::function<void()>([this, camera_ptr, pathManager, width, height]() {
        static std::vector<std::string> trainersName = { "Scientist",
                                                         "Red",
                                                         "Molayne",
                                                         "Sina",
                                                         "Sophocles",
                                                         "Cook" };

        idx = (idx - 1);

        if (idx < 0) {
            idx = idx + trainersName.size();
        }

        std::string modelPath = pathManager.getTrainerPath(trainersName[idx], "stay");


        deleteElement([](GameElement *el) {
            return el->getMeta("modelToDelete") == "true";
        });

        auto newModel = std::make_shared<AnimModel>(modelPath,
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

    auto changeModelToRight = std::function<void()>([this, camera_ptr, pathManager, width, height]() {
        static std::vector<std::string> trainersName = { "Scientist",
                                                         "Red",
                                                         "Molayne",
                                                         "Sina",
                                                         "Sophocles",
                                                         "Cook" };

        idx = (idx + 1) % trainersName.size();
        std::string modelPath = pathManager.getTrainerPath(trainersName[idx], "stay");


        deleteElement([](GameElement *el) {
            return el->getMeta("modelToDelete") == "true";
        });

        auto newModel = std::make_shared<AnimModel>(modelPath,
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

    auto func = [](){}; // функция для makeChoice должна


    auto switchLeft = std::make_shared<ImageButton>("Game/Resources/Pictures/arrowToLeft.png",
                                                      ImVec2(64.0f, 64.0f),
                                                      5, true, changeModelToLeft);

    auto switchRight = std::make_shared<ImageButton>("Game/Resources/Pictures/arrowToRight.png",
                                                          ImVec2(64.0f, 64.0f),
                                                          5, true, changeModelToRight);

    auto makeChoice = std::make_shared<ImageButton>("Game/Resources/Pictures/check-mark.png",
                                                           ImVec2(64.0f, 64.0f),
                                                           5, true, func);

    auto navbar = std::make_shared<NavBar>();
    navbar->addElement(std::move(switchLeft));
    navbar->addElement(std::move(switchRight));
    navbar->addElement(std::move(makeChoice));

    addElement(std::move(navbar));
    addElement(std::move(camera));
    addElement(std::move(model));
}