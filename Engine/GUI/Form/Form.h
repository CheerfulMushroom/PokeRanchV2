#ifndef POKERANCH_V2_GUI_FORM_H_
#define POKERANCH_V2_GUI_FORM_H_

#include <IGameElement.h>
#include <string>

static const int fieldSize = 64;

class Form : public IGameElement {
 public:
    Form();

    bool isClicked() = delete;
    double getDistance() = delete;
    std::string getMeta(std::string) = delete;
    void exec() = delete;

    void render() override;

    void update(double) override {}

 private:
    char loginBuf[fieldSize];
    char passwordBuf[fieldSize];
};

#endif