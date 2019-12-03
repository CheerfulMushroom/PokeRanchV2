#include <NavBar.h>
#include <opencv2/opencv.hpp>
#include <GL/glew.h>
#include <imgui.h>
#include <imgui_internal.h>

//static std::vector<std::string> texturesPaths = {
//        "Game/Resources/Pictures/cake-slice.png",
//        "Game/Resources/Pictures/house.png",
//        "Game/Resources/Pictures/muscle-up.png",
//        "Game/Resources/Pictures/human-pyramid.png",
//        "Game/Resources/Pictures/champions.png"
//};


NavBar::NavBar()  : windowFlags(0) {
    windowFlags |= ImGuiWindowFlags_NoTitleBar;
    windowFlags |= ImGuiWindowFlags_NoResize;
    windowFlags |= ImGuiWindowFlags_NoBackground;
    windowFlags |= ImGuiWindowFlags_NoMove;

}


void NavBar::addButton(std::unique_ptr<ImageButton> button) {
    _imageButtons.push_back(std::move(button));
}

void NavBar::render() {
    ImGui::Begin("navbar", nullptr, windowFlags);

    for (size_t i = 0; i < _imageButtons.size(); i++) {
        ImGui::PushID(i);

        _imageButtons[i]->render();

        ImGui::PopID();
        ImGui::SameLine();
    }

    ImGui::End();
}