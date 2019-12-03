#ifndef POKERANCH_V2_GUI_NAVBAR_H_
#define POKERANCH_V2_GUI_NAVBAR_H_

#include <IGameElement.h>
#include <vector>
#include <imgui.h>
#include <ImageButton.h>
#include <memory>

class NavBar : IGameElement {
 public:
    NavBar();

    bool isClicked() = delete;
    double getDistance() = delete;
    std::string getMeta(std::string) = delete;
    void exec() = delete;

    void render() override;
    void update(double) override {}

    void addButton(std::unique_ptr<ImageButton> button);

 private:
    ImGuiWindowFlags windowFlags;

    std::vector<std::unique_ptr<ImageButton>> _imageButtons;
};

#endif