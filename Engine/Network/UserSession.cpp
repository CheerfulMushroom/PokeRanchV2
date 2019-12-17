#include <UserSession.h>
#include <HttpNetworkManager.h>

bool UserSession::logIn(const std::string &login, const std::string &password, const std::string &mail) {
    try {
        HttpNetworkManager networkManager("0.0.0.0", "8888");

        std::map<std::string, std::string> infoForAuth;

        infoForAuth.insert(std::make_pair("login", login));
        infoForAuth.insert(std::make_pair("password", password));
        infoForAuth.insert(std::make_pair("mail", mail)); // исключить почту ?

        std::string responseBody = networkManager.post("/auth", infoForAuth);

        std::map<std::string, std::string> toMemory = networkManager.jsonToMap(responseBody);

        auto tokenPair = toMemory.find("token");

        if (tokenPair == toMemory.end()) {
            std::cout << "Bad auth" << std::endl;
            return false;
        } else {
            _userToken = tokenPair->second;
        }

        responseBody = networkManager.get("/get_profile");
        _info = networkManager.jsonToMap(responseBody);

        //check info for valid ?
        return true;
    }

    catch (std::exception const& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return false;
    }
}

std::string UserSession::getPokemonName() {
    auto pokemonPair = _info.find("pokemon");

    if (pokemonPair == _info.end()) {
        std::__throw_logic_error("pokemon field doesnt exist");
    }

    return pokemonPair->second;
}

std::string UserSession::getTrainerName() {
    auto trainerPair = _info.find("trainer");

    if (trainerPair == _info.end()) {
        std::__throw_logic_error("trainer field doesnt exist");
    }

    return trainerPair->second;
}