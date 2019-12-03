#ifndef POKERANCHV2_GAMEELEMENT_H
#define POKERANCHV2_GAMEELEMENT_H

#include <map>

class GameElement {
public:
    GameElement() = default;
    explicit GameElement(std::map<std::string, std::string> meta);
    ~GameElement() = default;

    std::string getMeta(const std::string &key);
    bool addMeta(const std::string &key, const std::string &value);
    virtual bool isClicked();
    virtual double getDistance();
    virtual void exec();

    virtual void render();
    virtual void update(double dt);
protected:
    std::map<std::string, std::string> _meta;
};

#endif //POKERANCHV2_GAMEELEMENT_H
