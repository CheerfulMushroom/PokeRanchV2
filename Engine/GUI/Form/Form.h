#ifndef POKERANCH_V2_GUI_FORM_H_
#define POKERANCH_V2_GUI_FORM_H_

#include <string>
#include <memory>
#include <vector>

#include "GameElement.h"
#include "imgui.h"

static const int fieldSize = 64;

class Form : public GameElement {
 public:
    Form(const std::string &title);

    void render() override;
    bool isClicked() override;
    double getDistance() override;
    void exec() override;

    void addElement(std::shared_ptr<GameElement> button);

 private:
    ImGuiWindowFlags _windowFlags;

    std::string _title;
    std::vector<std::shared_ptr<GameElement>> _elements;
};

#endif