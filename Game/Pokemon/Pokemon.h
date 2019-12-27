#ifndef POKERANCHV2_POKEMON_H
#define POKERANCHV2_POKEMON_H

#define MAX_SATIETY 100
#define MAX_LOYALTY 100
#define HAPPY_AFTER_FEEDING_MS 2000

#include <memory>
#include <glm/glm.hpp>

#include "GameElement.h"
#include "AnimModel.h"


class Pokemon : public GameElement {
public:
    Pokemon(std::shared_ptr<Camera> camera,
            glm::vec3 translate,
            float scale,
            glm::vec3 angles,
            int width,
            int height,
            const std::string& name,
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
    void switchAnimation(const std::string &action);

    std::shared_ptr<Camera> _camera;
    glm::vec3 _translate;
    float _scale;
    glm::vec3 _angles;
    int _width;
    int _height;
    AnimModel _model;
    std::string _name;
    double _power;
    double _agility;
    double _loyalty;
    double _satiety;
    double _health;
    double _maxHealth;

    bool _alive;
    bool _happy;
    double _timeSinceFeeding;
};


#endif //POKERANCHV2_POKEMON_H
