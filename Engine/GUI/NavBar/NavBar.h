#ifndef POKERANCH_V2_GUI_NAVBAR_H_
#define POKERANCH_V2_GUI_NAVBAR_H_

#include <GameElement.h>
#include <vector>
#include <imgui.h>
#include <ImageButton.h>
#include <memory>

class NavBar : public GameElement {
 public:
    NavBar();

    void render() override;
    bool isClicked() override;
    double getDistance() override;
    void exec() override;

    void addButton(std::shared_ptr<ImageButton> button);

 private:
    ImGuiWindowFlags windowFlags;

    std::vector<std::shared_ptr<GameElement>> _elements;
};

#endif