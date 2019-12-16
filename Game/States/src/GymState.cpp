#include "Engine.h"
#include "HomeState.h"
#include "GymState.h"
#include "ImageButton.h"
#include "NavBar.h"
#include "Camera.h"
#include "Model.h"
#include "AnimModel.h"


GymState::GymState(Engine *parentEngine) : GameState(parentEngine) {
    auto func = std::function([] {});
    auto switchToHome = std::function([=] {
        auto homeState = std::make_shared<HomeState>(_parentEngine);
        _parentEngine->setState(std::move(homeState));
    });


    auto kitchenButton = std::make_shared<ImageButton>("Game/Resources/Pictures/cake-slice.png",
                                                       ImVec2(64.0f, 64.0f),
                                                       5, true, func);
    auto homeButton = std::make_shared<ImageButton>("Game/Resources/Pictures/house.png",
                                                    ImVec2(64.0f, 64.0f),
                                                    5, true, switchToHome);
    auto gymButton = std::make_shared<ImageButton>("Game/Resources/Pictures/muscle-up.png",
                                                   ImVec2(64.0f, 64.0f),
                                                   5, false, func);
    auto socialButton = std::make_shared<ImageButton>("Game/Resources/Pictures/human-pyramid.png",
                                                      ImVec2(64.0f, 64.0f),
                                                      5, true, func);
    auto battleButton = std::make_shared<ImageButton>("Game/Resources/Pictures/champions.png",
                                                      ImVec2(64.0f, 64.0f),
                                                      5, true, func);

    auto navbar = std::make_shared<NavBar>();
    navbar->addButton(std::move(kitchenButton));
    navbar->addButton(std::move(homeButton));
    navbar->addButton(std::move(gymButton));
    navbar->addButton(std::move(socialButton));
    navbar->addButton(std::move(battleButton));
    addElement(std::move(navbar));


    auto camera = std::make_shared<Camera>(glm::vec3(0.0f, 0.0f, 4.0f));

    int width = _parentEngine->getWindow()->getWindowSize().first;
    int height = _parentEngine->getWindow()->getWindowSize().second;
    auto gym = std::make_shared<Model>("Game/Resources/Models/AzaleaGym/AzaleaGym.obj",
                                       camera.get(),
                                       glm::vec3(-1.3f, -1.0f, -2.0f),
                                       0.02,
                                       glm::vec3(0.0f, 38.0f, 0.0f),
                                       width,
                                       height,
                                       std::string("gym"));

    auto pokemon = std::make_shared<AnimModel>("Game/Resources/Models/Meowth/stay.dae",
                                               camera.get(),
                                               glm::vec3(0.9f, -1.0f, 0.0f),
                                               0.02,
                                               glm::vec3(90.0f, 140.0f, 0.0f),
                                               width,
                                               height,
                                               std::string("pokemon"));

    auto amie = std::make_shared<Model>("Game/Resources/Models/PokemonAmie/pink.dae",
                                        camera.get(),
                                        glm::vec3(0.0f, -1.0f, -2.0f),
                                        0.015,
                                        glm::vec3(0.0f, 0.0f, 0.0f),
                                        width,
                                        height,
                                        std::string("amie"));
    addElement(std::move(camera));
    addElement(std::move(gym));
    addElement(std::move(pokemon));
    addElement(std::move(amie));
}
