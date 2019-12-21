#ifndef NETWORK_USER_SESSION_H_
#define NETWORK_USER_SESSION_H_

#include <iostream>
#include <map>
#include <boost/beast/http/status.hpp>
#include <HttpNetworkManager.h>

using namespace boost::beast;

class UserSession {
 public:
    UserSession();

    void setLogin(std::string login);
    std::string getLogin();

    http::status auth(const std::string &login, const std::string &password);
    http::status registration(const std::string &login, const std::string &password, const std::string &mail);
    http::status logOut();
    http::status getProfile(const std::string &login);

    http::status addPokemon(const std::string &pokemonName);
    //http::status savePokemon(const std::string &pokemonName);
    http::status getPokemon();

    http::status addTrainer(const std::string &pokemonName);
    //http::status saveTrainer(const std::string &pokemonName);
    http::status getTrainer();

    //http::status syncData(std::map<std::string, std::string> &info);

    std::string getPokemonName(); // при поддержке нескольких покемонов std::vector<std::string>
    std::string getTrainerName();

 private:
    HttpNetworkManager networkManager;
    std::string _login;
    std::string _userToken;
    std::map<std::string, std::string> _info; // в каком виде будем хранить информацию пользователя ?
};



#endif  // NETWORK_USER_SESSION_H_

