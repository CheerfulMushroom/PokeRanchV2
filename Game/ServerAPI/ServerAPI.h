#ifndef NETWORK_USER_SESSION_H_
#define NETWORK_USER_SESSION_H_

#include <iostream>
#include <map>
#include <boost/beast/http/status.hpp>
#include <HttpNetworkManager.h>

using namespace boost::beast;

typedef std::pair<http::status, std::map<std::string, std::string>> Answer_t;

class ServerAPI {
public:
    explicit ServerAPI(const std::string& addr = "0.0.0.0", const std::string& port = "8888");

    Answer_t auth(const std::string& login, const std::string& password);
    Answer_t registration(const std::string& login, const std::string& password, const std::string& mail);
    Answer_t logout(const std::string& token);
    Answer_t getProfile(const std::string& login,
                        const std::string& token);

    Answer_t savePokemon(std::map<std::string, std::string> pokemonInfo,
                         const std::string& token);
    Answer_t getPokemon(const std::string& token);

    Answer_t saveTrainer(std::map<std::string, std::string> trainerInfo,
                         const std::string& token);
    Answer_t getTrainer(const std::string& token);

private:
    HttpNetworkManager _networkManager;
};


#endif  // NETWORK_USER_SESSION_H_

