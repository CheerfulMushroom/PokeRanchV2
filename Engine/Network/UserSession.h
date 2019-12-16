#ifndef NETWORK_USER_SESSION_H_
#define NETWORK_USER_SESSION_H_

// продумать взаимодействие с архитектурой игры
// где и как абстрагироваться от адреса ?
#include <iostream>
#include <map>

class UserSession {
 public:
    bool logIn(const std::string &login, const std::string &password, const std::string &mail);
    bool logOut();

    bool syncData(std::map<std::string, std::string> &info);

 private:
    std::string _userToken;
    std::map<std::string, std::string> _info; // в каком виде будем хранить информацию пользователя ?

};



#endif  // NETWORK_USER_SESSION_H_

