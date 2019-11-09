#ifndef POKERANCHV2_AUTHSTATE_H
#define POKERANCHV2_AUTHSTATE_H

#include "../../../Engine/BasicInterfaces/IGameState.h"

class AuthState : IGameState {
public:
    AuthState();

    void addElement(IGameElement* element) override;
    bool deleteElement(std::function<bool(IGameElement*)> cmp) override;
    int getElementsAmount() override;

private:
    void render() override;
    void update(double dt) override;

    std::vector<IGameElement*> _elements;
};


#endif //POKERANCHV2_AUTHSTATE_H
