#include "HomeState.h"
#include "ImageButton.h"
#include "NavBar.h"
#include "Engine.h"
#include "AuthState.h"


HomeState::HomeState(Engine *parentEngine) : GameState(parentEngine) {
    auto func = std::function([] {});
    auto switchToAuth = std::function([=] {
        auto authState = std::make_unique<AuthState>(_parentEngine);
        _parentEngine->setState(std::move(authState));
    });


    auto kitchenButton = std::make_unique<ImageButton>("Game/Resources/Pictures/cake-slice.png",
                                                       ImVec2(64.0f, 64.0f),
                                                       5, false, switchToAuth);
    auto homeButton = std::make_unique<ImageButton>("Game/Resources/Pictures/house.png",
                                                    ImVec2(64.0f, 64.0f),
                                                    5, false, func);
    auto gymButton = std::make_unique<ImageButton>("Game/Resources/Pictures/muscle-up.png",
                                                   ImVec2(128.0f, 128.0f),
                                                   5, true, func);
    auto socialButton = std::make_unique<ImageButton>("Game/Resources/Pictures/human-pyramid.png",
                                                      ImVec2(64.0f, 64.0f),
                                                      5, false, func);
    auto battleButton = std::make_unique<ImageButton>("Game/Resources/Pictures/champions.png",
                                                      ImVec2(64.0f, 64.0f),
                                                      5, false, func);

    auto navbar = std::make_unique<NavBar>();
    navbar->addButton(std::move(kitchenButton));
    navbar->addButton(std::move(homeButton));
    navbar->addButton(std::move(gymButton));
    navbar->addButton(std::move(socialButton));
    navbar->addButton(std::move(battleButton));

    addElement(std::move(navbar));
}
