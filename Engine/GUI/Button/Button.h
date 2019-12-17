#ifndef POKERANCH_V2_GUI_BUTTON_H_
#define POKERANCH_V2_GUI_BUTTON_H_

#include <GameElement.h>
#include <functional>


class Button : public GameElement {
public:
    Button(std::string label, std::function<void()> func);

    void render() override;
    bool isClicked() override;
    double getDistance() override;
    void exec() override;

private:
    std::string _label;
    std::function<void()> _execFunc;
    bool _isClicked;

};

#endif