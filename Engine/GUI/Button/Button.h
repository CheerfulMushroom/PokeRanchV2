#ifndef POKERANCH_V2_GUI_BUTTON_H_
#define POKERANCH_V2_GUI_BUTTON_H_

#include <Button.h>
#include <GameElement.h>
#include <functional>

static const int labelSize = 64;

class Button : GameElement {
 public:
    Button(std::string _label, const std::function<void()> &func);

    void render() override;
    void exec() override;

    void update(double) override {}


 private:
    char label[labelSize];
    std::function<void ()> _execFunc;
};

#endif