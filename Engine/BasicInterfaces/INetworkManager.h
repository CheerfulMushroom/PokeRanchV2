#ifndef POKERANCHV2_INETWORKMANAGER_H
#define POKERANCHV2_INETWORKMANAGER_H

#include <map>

class INetworkManager {
public:
    std::map<std::string, std::string> send(std::map<std::string, std::string>);
};

#endif //POKERANCHV2_INETWORKMANAGER_H
