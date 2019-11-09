#ifndef POKERANCHV2_INETWORKMANAGER_H
#define POKERANCHV2_INETWORKMANAGER_H

#include <map>

class INetworkManager {
public:
    virtual std::map<std::string, std::string> send(std::map<std::string, std::string>) = 0;
};

#endif //POKERANCHV2_INETWORKMANAGER_H
