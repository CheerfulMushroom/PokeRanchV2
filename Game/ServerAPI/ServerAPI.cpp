#include <ServerAPI.h>
#include <HttpNetworkManager.h>

ServerAPI::ServerAPI(const std::string& addr, const std::string& port) :
        _networkManager(addr, port) {}


Answer_t ServerAPI::auth(const std::string& login, const std::string& password) {
    std::map<std::string, std::string> infoForAuth;
    infoForAuth["login"] = login;
    infoForAuth["password"] = password;

    try {
        std::pair<http::status, std::string> response = _networkManager.post("/auth", infoForAuth);
        return {response.first, _networkManager.jsonToMap(response.second)};
    }
    catch (std::exception const& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return {http::status::unknown, {}};
    }
}

Answer_t ServerAPI::registration(const std::string& login, const std::string& password, const std::string& mail) {
    std::map<std::string, std::string> infoForAuth;
    infoForAuth["login"] = login;
    infoForAuth["password"] = password;
    infoForAuth["mail"] = mail;

    try {
        std::pair<http::status, std::string> response = _networkManager.post("/register", infoForAuth);
        return {response.first, _networkManager.jsonToMap(response.second)};
    }
    catch (std::exception const& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return {http::status::unknown, {}};
    }
}

Answer_t ServerAPI::logout(const std::string& token) {
    std::map<std::string, std::string> tokenInfo;
    tokenInfo["token"] = token;

    try {
        std::pair<http::status, std::string> response = _networkManager.post("/add_pokemon", tokenInfo);
        return {response.first, _networkManager.jsonToMap(response.second)};
    }
    catch (std::exception const& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return {http::status::unknown, {}};
    }
}

Answer_t ServerAPI::getProfile(const std::string& login, const std::string& token) {
    std::string queryString = "token=" + token + "&login" + "=" + login;

    try {
        std::pair<http::status, std::string> response = _networkManager.get("/get_profile", queryString);
        return {response.first, _networkManager.jsonToMap(response.second)};
    }
    catch (std::exception const& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return {http::status::unknown, {}};
    }
}


Answer_t ServerAPI::savePokemon(std::map<std::string, std::string> pokemonInfo,
                                const std::string& token) {
    std::map<std::string, std::string> toSend = std::move(pokemonInfo);
    toSend["token"] = token;

    try {
        std::pair<http::status, std::string> response = _networkManager.post("/save_pokemon", toSend);
        return {response.first, _networkManager.jsonToMap(response.second)};
    }
    catch (std::exception const& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return {http::status::unknown, {}};
    }
}

Answer_t ServerAPI::getPokemon(const std::string& token) {
    std::string queryString = "token=" + token;

    try {
        std::pair<http::status, std::string> response = _networkManager.get("/get_pokemon", queryString);
        return {response.first, _networkManager.jsonToMap(response.second)};
    }
    catch (std::exception const& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return {http::status::unknown, {}};
    }
}


Answer_t ServerAPI::saveTrainer(std::map<std::string, std::string> trainerInfo,
                                const std::string& token) {
    std::map<std::string, std::string> toSend = std::move(trainerInfo);
    toSend["token"] = token;

    try {
        std::pair<http::status, std::string> response = _networkManager.post("/save_trainer", toSend);
        return {response.first, _networkManager.jsonToMap(response.second)};
    }
    catch (std::exception const& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return {http::status::unknown, {}};
    }
}

Answer_t ServerAPI::getTrainer(const std::string& token) {
    std::string queryString = "token=" + token;

    try {
        std::pair<http::status, std::string> response = _networkManager.get("/get_trainer", queryString);
        return {response.first, _networkManager.jsonToMap(response.second)};
    }
    catch (std::exception const& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return {http::status::unknown, {}};
    }
}
