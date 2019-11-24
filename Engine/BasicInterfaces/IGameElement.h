#ifndef POKERANCHV2_IGAMEELEMENT_H
#define POKERANCHV2_IGAMEELEMENT_H

class IGameElement {
public:
     ~IGameElement() = default;

     std::string getMeta(std::string arg);
     bool isClicked();
     double getDistance();
     void exec();

     virtual void render() = 0;
     virtual void update(double dt) = 0;

};

#endif //POKERANCHV2_IGAMEELEMENT_H
