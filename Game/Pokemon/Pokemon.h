#ifndef POKERANCHV2_POKEMON_H
#define POKERANCHV2_POKEMON_H

#define MAX_SATIETY 100
#define MAX_LOYALTY 100

#include <memory>
#include <glm/glm.hpp>

#include "GameElement.h"
#include "AnimModel.h"

class Pokemon : public GameElement {
public:
    Pokemon(const std::string &pathToModel,
            const std::shared_ptr<Camera> &camera,
            glm::vec3 translate,
            float scale,
            glm::vec3 angles,
            int width,
            int height,
            std::string name,
            int power,
            int agility,
            int loyalty,
            int satiety,
            int health,
            int maxHealth,
            int secondsSinceLastSave);

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
