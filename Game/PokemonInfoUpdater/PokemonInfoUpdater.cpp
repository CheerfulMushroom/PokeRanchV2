#include "PokemonInfoUpdater.h"

#include "ProgressBar.h"

PokemonInfoUpdater::PokemonInfoUpdater(std::shared_ptr<Pokemon> pokemon,
                                       std::shared_ptr<ProgressBar> healthBar,
                                       std::shared_ptr<ProgressBar> satietyBar,
                                       std::shared_ptr<ProgressBar> loyaltyBar) :
        _pokemon(std::move(pokemon)),
        _loyaltyBar(std::move(loyaltyBar)),
        _satietyBar(std::move(satietyBar)),
        _healthBar(std::move(healthBar)) {}


void PokemonInfoUpdater::update(double dt) {
    auto pokemonInfo = _pokemon->getInfo();
    float loyalty = std::stof(pokemonInfo["loyalty"]);
    float satiety = std::stof(pokemonInfo["satiety"]);
    float health = std::stof(pokemonInfo["health"]);
    float maxHealth = std::stof(pokemonInfo["max_health"]);

    _healthBar->setCapacity(maxHealth);
    _healthBar->setProgress(health / maxHealth);

    _satietyBar->setCapacity(100);
    _satietyBar->setProgress(satiety / 100);

    _loyaltyBar->setCapacity(100);
    _loyaltyBar->setProgress(loyalty / 100);
}

