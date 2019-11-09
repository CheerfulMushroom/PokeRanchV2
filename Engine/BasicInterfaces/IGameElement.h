#ifndef POKERANCHV2_IGAMEELEMENT_H
#define POKERANCHV2_IGAMEELEMENT_H

class IGameElement {
public:
    virtual ~IGameElement() = default;

    virtual std::string getMeta(std::string arg) = 0;
    virtual bool isClicked() = 0;
    virtual double getDistance() = 0;
    virtual void exec() = 0;

    virtual void render() = 0;
    virtual void update(double dt) = 0;

};

#endif //POKERANCHV2_IGAMEELEMENT_H
