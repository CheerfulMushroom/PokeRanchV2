#ifndef POKERANCH_V2_GUI_FORM_H_
#define POKERANCH_V2_GUI_FORM_H_

#include <GameElement.h>
#include <string>
#include <Button.h>

static const int fieldSize = 64;

class Form : public GameElement {
 public:
    Form();

    void render() override;

    void update(double) override {}

 private:
    char loginBuf[fieldSize];
    char passwordBuf[fieldSize];
    Button _button;

};

#endif