#include "Pokemon.h"
#include "Camera.h"
#include "PathManager.h"

Pokemon::Pokemon(std::shared_ptr<Camera> camera,
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
                 int secondsSinceLastSave) :
        _camera(std::move(camera)),
        _translate(translate),
        _scale(scale),
        _angles(angles),
        _width(width),
        _height(height),
        _name(name),
        _power(power),
        _agility(agility),
        _loyalty(loyalty),
        _satiety(satiety),
        _health(health),
        _maxHealth(maxHealth),
        _model("Game/Resources/Models/Pokemons/" + name + "/stay.dae",
               _camera.get(),
               _translate,
               _scale,
               _angles,
               _width,
               _height,
               std::string("pokemon")) {

    switchAnimation("stay");
    update(secondsSinceLastSave * 1000);
}

void Pokemon::render() {
    _model.render();
}

void Pokemon::update(double dt) {
    /// UPDATE SATIETY
    _satiety -= dt / (0.5 * 1000);
    if (_satiety < 0) {
        _satiety = 0;
        _health -= dt / (1 * 1000);
        _loyalty -= dt / (1.5 * 1000);
    } else if (_satiety > MAX_SATIETY) {
        _satiety = MAX_SATIETY;
    }

    /// UPDATE LOYALTY
    if (_loyalty < 0) {
        _loyalty = 0;
    } else if (_loyalty > MAX_LOYALTY) {
        _loyalty = MAX_LOYALTY;
    }

    /// UPDATE HEALTH
    if (_health < 0) {
        _health = 0;
    } else if (_health > _maxHealth) {
        _health = _maxHealth;
    }

    _model.update(dt);
}


std::map<std::string, std::string> Pokemon::getInfo() {
    return {
            {"name",       _name},
            {"power",      std::to_string(int(round(_power)))},
            {"agility",    std::to_string(int(round(_agility)))},
            {"loyalty",    std::to_string(int(round(_loyalty)))},
            {"satiety",    std::to_string(int(round(_satiety)))},
            {"health",     std::to_string(int(round(_health)))},
            {"max_health", std::to_string(int(round(_maxHealth)))},
    };
}

void Pokemon::feed(int satietyFactor) {
    _satiety += satietyFactor;
}

void Pokemon::pet(int loyaltyFactor) {
    _loyalty += loyaltyFactor;
}

void Pokemon::switchAnimation(const std::string &action) {
    PathManager pathManager;
    std::string pokemonPath = pathManager.getPokemonPath(_name, action);
    _model.change_animation(pokemonPath);

}
