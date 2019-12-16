#include <UserSession.h>
#include <HttpNetworkManager.h>

bool UserSession::logIn(const std::string &login, const std::string &password, const std::string &mail) {
    try {
        HttpNetworkManager networkManager("0.0.0.0", "8888");

        std::map<std::string, std::string> infoForAuth;

        infoForAuth.insert(std::make_pair("login", login));
        infoForAuth.insert(std::make_pair("password", password));
        infoForAuth.insert(std::make_pair("mail", mail));

        std::string responseBody = networkManager.post("/auth", infoForAuth);

        std::map<std::string, std::string> toMemory = networkManager.jsonToMap(responseBody);

        auto tokenPair = toMemory.find("token");

        if (tokenPair == toMemory.end()) {
            std::cout << "Bad auth" << std::endl;
            return false;
        } else {
            _userToken = tokenPair->second;
            return true;
        }
    }

    catch (std::exception const& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return false;
    }
}

