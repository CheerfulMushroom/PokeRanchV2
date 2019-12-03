#ifndef POKERANCH_V2_GUI_BUTTON_H_
#define POKERANCH_V2_GUI_BUTTON_H_

#include <Button.h>
#include <IGameElement.h>

static const int labelSize = 64;

class Button : IGameElement {
 public:
    Button(std::string _label);

    bool isClicked() = delete;
    double getDistance() = delete;
    std::string getMeta(std::string) = delete;
    void exec() = delete;

    void render() override;

    void update(double) override {}


 private:
    char label[labelSize];
};

#endif