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

    auto pokemon = std::make_shared<Pokemon>(camera,
                                             glm::vec3(0.9f, -1.0f, 0.0f),
                                             0.02,
                                             glm::vec3(90.0f, 150.0f, 0.0f),
                                             width,
                                             height,
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


    auto kitchenButton = std::make_shared<ImageButton>("Game/Resources/Pictures/cake-slice.png",
                                                       ImVec2(64.0f, 64.0f),
                                                       5, true,
                                                       std::bind(switchToState<KitchenState>, this->_parentEngine));
    auto homeButton = std::make_shared<ImageButton>("Game/Resources/Pictures/house.png",
                                                    ImVec2(64.0f, 64.0f),
                                                    5, false,
                                                    std::bind(switchToState<HomeState>, this->_parentEngine));
    auto saveButton = std::make_shared<ImageButton>("Game/Resources/Pictures/save.png",
                                                    ImVec2(64.0f, 64.0f),
                                                    5, true,
                                                    std::bind(savePokemonProgress, pokemon->getInfo(), this->_parentEngine));
    auto petButton = std::make_shared<ImageButton>("Game/Resources/Pictures/hand.png",
                                                    ImVec2(64.0f, 64.0f),
                                                    5, true,
                                                    std::bind(&Pokemon::pet, pokemon.get(), 15));

    auto navbar = std::make_shared<NavBar>();
    navbar->addElement(std::move(kitchenButton));
    navbar->addElement(std::move(homeButton));
    navbar->addElement(std::move(saveButton));
    navbar->addElement(std::move(petButton));
    addElement(std::move(navbar));
}

HomeState::~HomeState() {
    auto pokemonInfo = _parentEngine->getSessionInfo("pokemon");
    savePokemonProgress(pokemonInfo, _parentEngine);
}
