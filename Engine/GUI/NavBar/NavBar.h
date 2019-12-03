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
    void addButton(std::unique_ptr<ImageButton> button);

 private:
    ImGuiWindowFlags windowFlags;

    std::vector<std::unique_ptr<ImageButton>> _imageButtons;
};

#endif