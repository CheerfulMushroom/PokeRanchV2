#include "PokemonInfoUpdater.h"
#include "ProgressBar.h"

PokemonInfoUpdater::PokemonInfoUpdater(std::shared_ptr<Pokemon> pokemon,
                                       std::shared_ptr<ProgressBar> healthBar,
                                       std::shared_ptr<ProgressBar> satietyBar,
                                       std::shared_ptr<ProgressBar> loyaltyBar,
                                       Engine *parentEngine) :
        _pokemon(std::move(pokemon)),
        _loyaltyBar(std::move(loyaltyBar)),
        _satietyBar(std::move(satietyBar)),
        _healthBar(std::move(healthBar)),
        _parentEngine(parentEngine) {}


void PokemonInfoUpdater::update(double dt) {
    auto pokemonInfo = _pokemon->getInfo();
    float loyalty = std::stof(pokemonInfo["loyalty"]);
    float satiety = std::stof(pokemonInfo["satiety"]);
    float health = std::stof(pokemonInfo["health"]);
    float maxHealth = std::stof(pokemonInfo["max_health"]);
    pokemonInfo["seconds_since_last_save"] = "0";

    /// UPDATE SESSION
    _parentEngine->updateSessionInfo("pokemon", pokemonInfo);

    /// UPDATE BARS
    _healthBar->setCapacity(maxHealth);
    _healthBar->setProgress(health / maxHealth);

    _satietyBar->setCapacity(MAX_SATIETY);
    _satietyBar->setProgress(satiety / MAX_SATIETY);

    _loyaltyBar->setCapacity(MAX_LOYALTY);
    _loyaltyBar->setProgress(loyalty / MAX_LOYALTY);
}

