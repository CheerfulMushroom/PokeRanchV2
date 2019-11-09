#ifndef POKERANCHV2_IGAMEELEMENT_H
#define POKERANCHV2_IGAMEELEMENT_H

class IGameElement {
public:
    std::string getMeta(std::string arg);
    bool isClicked();
    double getDistance();
    void exec();

    void render();
    void update(double dt);
};

#endif //POKERANCHV2_IGAMEELEMENT_H
