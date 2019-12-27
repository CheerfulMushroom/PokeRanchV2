#include "ButtonFunctions.h"
#include "ServerAPI.h"


void savePokemonProgress(std::map<std::string, std::string> pokemonInfo, Engine *engine) {
    pokemonInfo["seconds_since_last_save"] = "0";
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

