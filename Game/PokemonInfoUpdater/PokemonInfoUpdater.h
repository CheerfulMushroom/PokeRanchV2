#ifndef POKERANCHV2_POKEMONINFOUPDATER_H
#define POKERANCHV2_POKEMONINFOUPDATER_H

#include <memory>

#include "GameElement.h"
#include "Pokemon.h"
#include "ProgressBar.h"
#include "Engine.h"

class PokemonInfoUpdater: public GameElement {
public:
    PokemonInfoUpdater(std::shared_ptr<Pokemon> pokemon,
                       std::shared_ptr<ProgressBar> healthBar,
                       std::shared_ptr<ProgressBar> satietyBar,
                       std::shared_ptr<ProgressBar> loyaltyBar,
                       Engine* parentEngine);

    void update(double dt) override;

private:
    std::shared_ptr<Pokemon> _pokemon;
    std::shared_ptr<ProgressBar> _healthBar;
    std::shared_ptr<ProgressBar> _satietyBar;
    std::shared_ptr<ProgressBar> _loyaltyBar;
    Engine* _parentEngine;
};


#endif //POKERANCHV2_POKEMONINFOUPDATER_H
