#include "Engine.h"

#include "KitchenState.h"
#include "AuthState.h"
#include "GymState.h"
#include "KitchenState.h"

#include "ImageButton.h"
#include "NavBar.h"
#include "Camera.h"
#include "Model.h"
#include "AnimModel.h"
#include "Pokemon.h"
#include "Cupcake.h"
#include "PathManager.h"
#include "ProgressBar.h"
#include "Form.h"
#include "PokemonInfoUpdater.h"

#include "ButtonFunctions.h"

KitchenState::KitchenState(Engine *parentEngine) : GameState(parentEngine) {
    /// ADDING MODELS
    auto camera = std::make_shared<Camera>(glm::vec3(0.0f, 0.0f, 4.0f));

    auto pokemonInfo = _parentEngine->getSessionInfo("pokemon");
    auto trainerInfo = _parentEngine->getSessionInfo("trainer");

    PathManager pathManager;

    std::string pokemonPath = pathManager.getPokemonPath(pokemonInfo["name"], "eat");

    std::string cockPath = pathManager.getTrainerPath("Cook", "stay");

    int width = _parentEngine->getWindow()->getWindowSize().first;
    int height = _parentEngine->getWindow()->getWindowSize().second;

    auto house = std::make_shared<Model>("Game/Resources/Models/Static/PokemonHouse/PokemonHouse.obj",
                                         camera.get(),
                                         glm::vec3(-2.3f, -1.0f, -2.3f),
                                         0.058,
                                         glm::vec3(0.0f, 38.0f, 0.0f),
                                         width,
                                         height,
                                         std::string("house"));

    auto plate = std::make_shared<Model>(pathManager.getStaticModelPath("CookPlate/CookPlate"),
                                         camera.get(),
                                         glm::vec3(0.0f, -1.0f, -2.0f),
                                         0.04,
                                         glm::vec3(0.0f, 38.0f, 0.0f),
                                         width,
                                         height,
                                         std::string("plate"));


    auto puff = std::make_shared<Cupcake>("PokePuffs/Summer/summer",
                                          camera,
                                          glm::vec3(0.0f, -0.77f, -2.0f),
                                          0.04,
                                          glm::vec3(0.0f, 38.0f, 0.0f),
                                          width,
                                          height);

    auto pokemon = std::make_shared<Pokemon>(pokemonPath,
                                             camera,
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

    auto trainer = std::make_shared<AnimModel>(cockPath,
                                               camera.get(),
                                               glm::vec3(-1.5f, -1.0f, 0.0f),
                                               0.012,
                                               glm::vec3(0.0f, 56.0f, 0.0f),
                                               width,
                                               height,
                                               std::string("trainer"));

    auto amie = std::make_shared<Model>("Game/Resources/Models/Static/PokemonAmie/pink.dae",
                                        camera.get(),
                                        glm::vec3(0.0f, -1.0f, -2.0f),
                                        0.015,
                                        glm::vec3(0.0f, 0.0f, 0.0f),
                                        width,
                                        height,
                                        std::string("amie"));

    addElement(camera);
    addElement(house);
    addElement(plate);
    addElement(puff);
    addElement(pokemon);
    addElement(trainer);
    addElement(amie);


    /// ADDING POKEMON INFO

    float loyalty = std::stof(pokemonInfo["loyalty"]);
    float satiety = std::stof(pokemonInfo["satiety"]);
    float health = std::stof(pokemonInfo["health"]);
    float maxHealth = std::stof(pokemonInfo["max_health"]);

    auto loyaltyBar = std::make_shared<ProgressBar>(ImVec2(300.0f, 0.0f), "Loyalty");
    loyaltyBar->setCapacity(100);
    loyaltyBar->setProgress(loyalty / 100);

    auto satietyBar = std::make_shared<ProgressBar>(ImVec2(300.0f, 0.0f), "Satiety");
    satietyBar->setCapacity(100);
    satietyBar->setProgress(satiety / 100);

    auto healthBar = std::make_shared<ProgressBar>(ImVec2(300.0f, 0.0f), "Health");
    healthBar->setCapacity(maxHealth);
    healthBar->setProgress(health / maxHealth);


    auto pokemonStats = std::make_shared<Form>("PokemonStats");

    auto emptyFunction = []() {};

    auto pokemonIcon = std::make_shared<ImageButton>(pathManager.getPicturePath(pokemonInfo["name"] + "Icon"),
                                                     ImVec2(64.0f, 64.0f),
                                                     0, true, emptyFunction);

    pokemonStats->addElement(pokemonIcon);
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

    auto kitchenButton = std::make_shared<ImageButton>(pathManager.getPicturePath("cake-slice"),
                                                       ImVec2(64.0f, 64.0f),
                                                       5, false,
                                                       std::bind(switchToState<KitchenState>, this->_parentEngine));

    auto homeButton = std::make_shared<ImageButton>(pathManager.getPicturePath("house"),
                                                    ImVec2(64.0f, 64.0f),
                                                    5, true, emptyFunc);
    auto gymButton = std::make_shared<ImageButton>(pathManager.getPicturePath("muscle-up"),
                                                   ImVec2(64.0f, 64.0f),
                                                   5, true, emptyFunc);
    auto socialButton = std::make_shared<ImageButton>(pathManager.getPicturePath("human-pyramid"),
                                                      ImVec2(64.0f, 64.0f),
                                                      5, true, emptyFunc);
    auto battleButton = std::make_shared<ImageButton>(pathManager.getPicturePath("champions"),
                                                      ImVec2(64.0f, 64.0f),
                                                      5, true, emptyFunc);
    auto saveButton = std::make_shared<ImageButton>(pathManager.getPicturePath("champions"),
                                                    ImVec2(64.0f, 64.0f),
                                                    5, true,
                                                    std::bind(savePokemonProgress, pokemon, this->_parentEngine));

    auto navbar = std::make_shared<NavBar>();
    navbar->addElement(std::move(kitchenButton));
    navbar->addElement(std::move(homeButton));
    navbar->addElement(std::move(gymButton));
    navbar->addElement(std::move(socialButton));
    navbar->addElement(std::move(battleButton));
    navbar->addElement(std::move(saveButton));
    addElement(std::move(navbar));


    // ADDING SIDE_BAR

    auto sideBar = std::make_shared<Form>("SideBar");

    auto winterPuff = std::make_shared<ImageButton>(pathManager.getPicturePath("summerPuff"),
                                                    ImVec2(128.0f, 128.0f),
                                                    5, true, emptyFunc);

    auto summerPuff = std::make_shared<ImageButton>(pathManager.getPicturePath("winterPuff"),
                                                    ImVec2(128.0f, 128.0f),
                                                    5, true, emptyFunc);

    auto springPuff = std::make_shared<ImageButton>(pathManager.getPicturePath("wishPuff"),
                                                    ImVec2(128.0f, 128.0f),
                                                    5, true, emptyFunc);

    sideBar->addElement(std::move(winterPuff));
    sideBar->addElement(std::move(summerPuff));
    sideBar->addElement(std::move(springPuff));

    addElement(std::move(sideBar));
}
