#ifndef POKERANCHV2_POKEMON_H
#define POKERANCHV2_POKEMON_H

#include <memory>

#include "GameElement.h"
#include "AnimModel.h"

class Pokemon : public GameElement {
public:
    Pokemon(const std::shared_ptr<Camera> &camera, int width, int height, const std::string &pathToModel,
            std::string name, int power, int agility, int loyalty, int satiety, int health, int maxHealth);

    void render() override;
    void update(double dt) override;

    void feed(int satietyFactor);
    void pet(int loyaltyFactor);

    std::map<std::string, std::string> getInfo();

private:
    AnimModel _model;
    std::string _name;
    double _power;
    double _agility;
    double _loyalty;
    double _satiety;
    double _health;
    double _maxHealth;
};


#endif //POKERANCHV2_POKEMON_H
