#include "Pokemon.h"
#include "Camera.h"

Pokemon::Pokemon(const std::shared_ptr<Camera> &camera, int width, int height, const std::string &pathToModel,
                 std::string name, int power, int agility, int loyalty, int satiety, int health, int maxHealth) :
        _model(pathToModel,
               camera.get(),
               glm::vec3(0.9f, -1.0f, 0.0f),
               0.02,
               glm::vec3(90.0f, 150.0f, 0.0f),
               width,
               height,
               std::string("pokemon")),
        _name(std::move(name)),
        _power(power),
        _agility(agility),
        _loyalty(loyalty),
        _satiety(satiety),
        _health(health),
        _maxHealth(maxHealth) {}

void Pokemon::render() {
    _model.render();
}

void Pokemon::update(double dt) {
    _model.update(dt);
    _satiety -= dt / (0.5 * 1000);
    if (_satiety < 0) {
        _satiety = 0;
        _health -= dt / (1 * 1000);
        _loyalty -= dt / (1.5 * 1000);
    }
}


std::map<std::string, std::string> Pokemon::getInfo() {
    return {
            {"name",      _name},
            {"power",     std::to_string(int(round(_power)))},
            {"agility",   std::to_string(int(round(_agility)))},
            {"loyalty",   std::to_string(int(round(_loyalty)))},
            {"satiety",   std::to_string(int(round(_satiety)))},
            {"health",    std::to_string(int(round(_health)))},
            {"max_health", std::to_string(int(round(_maxHealth)))},
    };
}

void Pokemon::feed(int satietyFactor) {
    _satiety += satietyFactor;
}

void Pokemon::pet(int loyaltyFactor) {
    _loyalty += loyaltyFactor;
}
