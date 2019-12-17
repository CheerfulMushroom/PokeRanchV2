#include "Engine.h"

#include "HomeState.h"
#include "AuthState.h"
#include "GymState.h"
#include "KitchenState.h"

#include "ImageButton.h"
#include "NavBar.h"
#include "Camera.h"
#include "Model.h"
#include "AnimModel.h"

HomeState::HomeState(Engine *parentEngine) : GameState(parentEngine) {
    auto func = std::function([] {});

//    auto switchToAuth = std::function([=] {
//        auto authState = std::make_shared<AuthState>(_parentEngine);
//        _parentEngine->setState(std::move(authState));
//    });

    auto switchToKitchen = std::function([=] {
        auto kitchenState = std::make_shared<KitchenState>(_parentEngine);
        _parentEngine->setState(std::move(kitchenState));
    });

    auto switchToGym = std::function([=] {
        auto gymState = std::make_shared<GymState>(_parentEngine);
        _parentEngine->setState(std::move(gymState));
    });


    auto kitchenButton = std::make_shared<ImageButton>("Game/Resources/Pictures/cake-slice.png",
                                                       ImVec2(64.0f, 64.0f),
                                                       5, true, switchToKitchen);
    auto homeButton = std::make_shared<ImageButton>("Game/Resources/Pictures/house.png",
                                                    ImVec2(64.0f, 64.0f),
                                                    5, false, func);
    auto gymButton = std::make_shared<ImageButton>("Game/Resources/Pictures/muscle-up.png",
                                                   ImVec2(64.0f, 64.0f),
                                                   5, true, switchToGym);
    auto socialButton = std::make_shared<ImageButton>("Game/Resources/Pictures/human-pyramid.png",
                                                      ImVec2(64.0f, 64.0f),
                                                      5, true, func);
    auto battleButton = std::make_shared<ImageButton>("Game/Resources/Pictures/champions.png",
                                                      ImVec2(64.0f, 64.0f),
                                                      5, true, func);

    auto navbar = std::make_shared<NavBar>();
    navbar->addElement(std::move(kitchenButton));
    navbar->addElement(std::move(homeButton));
    navbar->addElement(std::move(gymButton));
    navbar->addElement(std::move(socialButton));
    navbar->addElement(std::move(battleButton));
    addElement(std::move(navbar));


    auto camera = std::make_shared<Camera>(glm::vec3(0.0f, 0.0f, 4.0f));

    int width = _parentEngine->getWindow()->getWindowSize().first;
    int height = _parentEngine->getWindow()->getWindowSize().second;

    auto house = std::make_shared<Model>("Game/Resources/Models/PokemonHouse/PokemonHouse.obj",
                                         camera.get(),
                                         glm::vec3(-1.3f, -1.0f, -2.0f),
                                         0.02,
                                         glm::vec3(0.0f, 38.0f, 0.0f),
                                         width,
                                         height,
                                         std::string("house"));

    auto pokemon = std::make_shared<AnimModel>("Game/Resources/Models/Pikachu/stay.dae",
                                               camera.get(),
                                               glm::vec3(-0.9f, -1.0f, 0.0f),
                                               0.02,
                                               glm::vec3(90.0f, 140.0f, 0.0f),
                                               width,
                                               height,
                                               std::string("pokemon"));

    auto amie = std::make_shared<Model>("Game/Resources/Models/PokemonAmie/withoutAll.dae",
                                        camera.get(),
                                        glm::vec3(0.0f, -1.0f, -2.0f),
                                        0.015,
                                        glm::vec3(0.0f, 0.0f, 0.0f),
                                        width,
                                        height,
                                        std::string("amie"));
    addElement(std::move(camera));
    addElement(std::move(house));
    addElement(std::move(pokemon));
    addElement(std::move(amie));

}
