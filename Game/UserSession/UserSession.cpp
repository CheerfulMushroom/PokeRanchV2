#include <UserSession.h>
#include <HttpNetworkManager.h>

UserSession::UserSession() : networkManager("0.0.0.0", "8888") {}

void UserSession::setLogin(std::string login) {
    _login = std::move(login);
}

std::string UserSession::getLogin() {
    return _login;
}

std::string UserSession::getTrainerName() {
    auto trainerPair = _info.find("trainer_name");

    if (trainerPair == _info.end()) {
        return "";
    }

    return trainerPair->second;
}

http::status UserSession::auth(const std::string &login, const std::string &password) {
    try {
        std::map<std::string, std::string> infoForAuth;

        infoForAuth.insert(std::make_pair("login", login));
        infoForAuth.insert(std::make_pair("password", password));

        std::pair<http::status, std::string> response = networkManager.post("/auth", infoForAuth);

        if (response.first != http::status::ok) {
            return response.first;
        }

        std::map<std::string, std::string> toMemory = networkManager.jsonToMap(response.second);

        auto tokenPair = toMemory.find("token");

        _userToken = tokenPair->second;

        return response.first;
    }

    catch (std::exception const &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return http::status::unknown;
    }
}

http::status UserSession::getProfile(const std::string &login) {
    std::string queryString = "token=" + _userToken + "&login" + "=" + login;

    std::pair<http::status, std::string> response = networkManager.get("/get_profile", queryString);

    if (response.first != http::status::ok) {
        return response.first;
    }

    _info = networkManager.jsonToMap(response.second);
    return response.first;
}

http::status UserSession::registration(const std::string &login, const std::string &password, const std::string &mail) {
    try {
        std::map<std::string, std::string> infoForAuth;

        infoForAuth.insert(std::make_pair("login", login));
        infoForAuth.insert(std::make_pair("password", password));
        infoForAuth.insert(std::make_pair("mail", mail));

        std::pair<http::status, std::string> response = networkManager.post("/register", infoForAuth);

        return response.first;
    }

    catch (std::exception const &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return http::status::unknown;
    }
}

http::status UserSession::addPokemon(const std::string &pokemonName) {
    try {
        std::map<std::string, std::string> pokemonInfo;

        pokemonInfo.insert(std::make_pair("token", _userToken));
        pokemonInfo.insert(std::make_pair("name", pokemonName));

        std::pair<http::status, std::string> response = networkManager.post("/add_pokemon", pokemonInfo);

        return response.first;

    } catch (std::exception const &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return http::status::unknown;
    }
}

http::status UserSession::addTrainer(const std::string &trainerName) {
    try {
        std::map<std::string, std::string> trainerInfo;

        trainerInfo.insert(std::make_pair("token", _userToken));
        trainerInfo.insert(std::make_pair("name", trainerName));

        std::pair<http::status, std::string> response = networkManager.post("/add_trainer", trainerInfo);

        return response.first;

    } catch (std::exception const &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return http::status::unknown;
    }
}

http::status UserSession::getPokemon() {
    std::string queryString = "token=" + _userToken;

    std::pair<http::status, std::string> response = networkManager.get("/get_pokemon", queryString);

    if (response.first != http::status::ok) {
        return response.first;
    }

    _info = networkManager.jsonToMap(response.second);
    return response.first;
}

http::status UserSession::getTrainer() {
    std::string queryString = "token=" + _userToken;

    std::pair<http::status, std::string> response = networkManager.get("/get_trainer", queryString);

    if (response.first != http::status::ok) {
        return response.first;
    }

    _info = networkManager.jsonToMap(response.second);
    return response.first;
}

http::status UserSession::logOut() {
    try {
        std::map<std::string, std::string> tokenInfo;

        tokenInfo.insert(std::make_pair("token", _userToken));

        std::pair<http::status, std::string> response = networkManager.post("/add_pokemon", tokenInfo);

        return response.first;

    } catch (std::exception const &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return http::status::unknown;
    }
}


std::string UserSession::getPokemonName() {
    auto pokemonPair = _info.find("pokemon_name");

    if (pokemonPair == _info.end()) {
        return "";
    }

    return pokemonPair->second;
}


