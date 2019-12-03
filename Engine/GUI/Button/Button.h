#ifndef POKERANCH_V2_GUI_BUTTON_H_
#define POKERANCH_V2_GUI_BUTTON_H_

#include <Button.h>
#include <GameElement.h>

static const int labelSize = 64;

class Button : GameElement {
 public:
    Button(std::string _label);

    void render() override;

    void update(double) override {}


 private:
    char label[labelSize];
};

#endif