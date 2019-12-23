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
#include "Pokemon.h"
#include "PathManager.h"
#include "ProgressBar.h"
#include "Form.h"
#include "PokemonInfoUpdater.h"

#include "ButtonFunctions.h"

HomeState::HomeState(Engine *parentEngine) : GameState(parentEngine) {
    /// ADDING MODELS
    auto camera = std::make_shared<Camera>(glm::vec3(0.0f, 0.0f, 4.0f));

    auto pokemonInfo = _parentEngine->getSessionInfo("pokemon");
    auto trainerInfo = _parentEngine->getSessionInfo("trainer");

    PathManager pathManager;
    std::string pokemonPath = pathManager.getPokemonPath(pokemonInfo["name"], "stay");
    std::string trainerPath = pathManager.getTrainerPath(trainerInfo["name"], "stay");

    int width = _parentEngine->getWindow()->getWindowSize().first;
    int height = _parentEngine->getWindow()->getWindowSize().second;

    auto house = std::make_shared<Model>("Game/Resources/Models/Static/PokemonHouse/PokemonHouse.obj",
                                         camera.get(),
                                         glm::vec3(-2.2f, -1.0f, -2.0f),
                                         0.02,
                                         glm::vec3(0.0f, 38.0f, 0.0f),
                                         width,
                                         height,
                                         std::string("house"));

    auto pokemon = std::make_shared<Pokemon>(camera, width, height, pokemonPath,
                                             pokemonInfo["name"],
                                             std::stoi(pokemonInfo["power"]),
                                             std::stoi(pokemonInfo["agility"]),
                                             std::stoi(pokemonInfo["loyalty"]),
                                             std::stoi(pokemonInfo["satiety"]),
                                             std::stoi(pokemonInfo["health"]),
                                             std::stoi(pokemonInfo["max_health"]),
                                             std::stoi(pokemonInfo["seconds_since_last_save"]));

    auto trainer = std::make_shared<AnimModel>(trainerPath,
                                               camera.get(),
                                               glm::vec3(-0.5f, -1.0f, 0.0f),
                                               0.012,
                                               glm::vec3(0.0f, 14.0f, 0.0f),
                                               width,
                                               height,
                                               std::string("trainer"));

    auto amie = std::make_shared<Model>("Game/Resources/Models/Static/PokemonAmie/withoutAll.dae",
                                        camera.get(),
                                        glm::vec3(0.0f, -1.0f, -2.0f),
                                        0.015,
                                        glm::vec3(0.0f, 0.0f, 0.0f),
                                        width,
                                        height,
                                        std::string("amie"));
    addElement(camera);
    addElement(house);
    addElement(pokemon);
    addElement(trainer);
    addElement(amie);


    /// ADDING POKEMON INFO

    float loyalty = std::stof(pokemonInfo["loyalty"]);
    float satiety = std::stof(pokemonInfo["satiety"]);
    float health = std::stof(pokemonInfo["health"]);
    float maxHealth = std::stof(pokemonInfo["max_health"]);

    auto loyaltyBar = std::make_shared<ProgressBar>(ImVec2(300.0f, 0.0f), "Loyalty");
    loyaltyBar->setCapacity(MAX_LOYALTY);
    loyaltyBar->setProgress(loyalty / MAX_LOYALTY);

    auto satietyBar = std::make_shared<ProgressBar>(ImVec2(300.0f, 0.0f), "Satiety");
    satietyBar->setCapacity(MAX_SATIETY);
    satietyBar->setProgress(satiety / MAX_SATIETY);

    auto healthBar = std::make_shared<ProgressBar>(ImVec2(300.0f, 0.0f), "Health");
    healthBar->setCapacity(maxHealth);
    healthBar->setProgress(health / maxHealth);


    auto pokemonStats = std::make_shared<Form>("PokemonStats");
    pokemonStats->addElement(loyaltyBar);
    pokemonStats->addElement(satietyBar);
    pokemonStats->addElement(healthBar);
    addElement(pokemonStats);

    /// ADDING POKEMON INFO UPDATER

    auto pokemonInfoUpdater = std::make_shared<PokemonInfoUpdater>(pokemon,
                                                                   healthBar,
                                                                   satietyBar,
                                                                   loyaltyBar);
    addElement(pokemonInfoUpdater);

    /// ADDING BUTTONS

    auto emptyFunc = std::function([] {});

//    auto kitchenButton = std::make_shared<ImageButton>("Game/Resources/Pictures/cake-slice.png",
//                                                       ImVec2(64.0f, 64.0f),
//                                                       5, true, emptyFunc);

    auto kitchenButton = std::make_shared<ImageButton>("Game/Resources/Pictures/cake-slice.png",
                                                       ImVec2(64.0f, 64.0f),
                                                       5, true, std::bind(switchToState<KitchenState>, this->_parentEngine));

    auto homeButton = std::make_shared<ImageButton>("Game/Resources/Pictures/house.png",
                                                    ImVec2(64.0f, 64.0f),
                                                    5, false, emptyFunc);
    auto gymButton = std::make_shared<ImageButton>("Game/Resources/Pictures/muscle-up.png",
                                                   ImVec2(64.0f, 64.0f),
                                                   5, true, emptyFunc);
    auto socialButton = std::make_shared<ImageButton>("Game/Resources/Pictures/human-pyramid.png",
                                                      ImVec2(64.0f, 64.0f),
                                                      5, true, emptyFunc);
    auto battleButton = std::make_shared<ImageButton>("Game/Resources/Pictures/champions.png",
                                                      ImVec2(64.0f, 64.0f),
                                                      5, true, emptyFunc);
    auto saveButton = std::make_shared<ImageButton>("Game/Resources/Pictures/champions.png",
                                                    ImVec2(64.0f, 64.0f),
                                                    5, true,
                                                    std::bind(&HomeState::saveProgress, this, pokemon));

    auto navbar = std::make_shared<NavBar>();
    navbar->addElement(std::move(kitchenButton));
    navbar->addElement(std::move(homeButton));
    navbar->addElement(std::move(gymButton));
    navbar->addElement(std::move(socialButton));
    navbar->addElement(std::move(battleButton));
    navbar->addElement(std::move(saveButton));
    addElement(std::move(navbar));
}

void HomeState::saveProgress(const std::shared_ptr<Pokemon> &pokemon) {
    auto pokemonInfo = pokemon->getInfo();
    _parentEngine->updateSessionInfo("pokemon", pokemonInfo);

    auto profileInfo = _parentEngine->getSessionInfo("profile");
    std::string token = profileInfo["token"];

    Answer_t response = _api.savePokemon(pokemonInfo, token);

    if (response.first != http::status::ok) {
        std::cout << "Error occurred:" << std::endl;
        for (const auto &errorInfo:response.second) {
            std::cout << errorInfo.first << ": " << errorInfo.second << std::endl;
        }
        return;
    }

}
