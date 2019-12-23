#include "ButtonFunctions.h"
#include "ServerAPI.h"

void savePokemonProgress(const std::shared_ptr<Pokemon>& pokemon, Engine *engine) {
    auto pokemonInfo = pokemon->getInfo();
    engine->updateSessionInfo("pokemon", pokemonInfo);

    auto profileInfo = engine->getSessionInfo("profile");
    std::string token = profileInfo["token"];

    ServerAPI api;
    Answer_t response = api.savePokemon(pokemonInfo, token);

    if (response.first != http::status::ok) {
        std::cout << "Error occurred:" << std::endl;
        for (const auto &errorInfo:response.second) {
            std::cout << errorInfo.first << ": " << errorInfo.second << std::endl;
        }
        return;
    }
}
