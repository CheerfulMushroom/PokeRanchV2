#ifndef POKERANCH_V2_GUI_NAVBAR_H_
#define POKERANCH_V2_GUI_NAVBAR_H_

#include <vector>
#include <memory>

#include "imgui.h"
#include "GameElement.h"

class NavBar : public GameElement {
 public:
    NavBar();

    void render() override;
    bool isClicked() override;
    double getDistance() override;
    void exec() override;

    void addElement(std::shared_ptr<GameElement> button);

 private:
    ImGuiWindowFlags _windowFlags;

    std::vector<std::shared_ptr<GameElement>> _elements;
};

#endif