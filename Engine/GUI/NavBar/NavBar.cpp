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


NavBar::NavBar() : windowFlags(0) {
    windowFlags |= ImGuiWindowFlags_NoTitleBar;
    windowFlags |= ImGuiWindowFlags_NoResize;
    windowFlags |= ImGuiWindowFlags_NoBackground;
    windowFlags |= ImGuiWindowFlags_NoMove;

}


void NavBar::addButton(std::unique_ptr<ImageButton> button) {
    _elements.push_back(std::move(button));
}

void NavBar::render() {
    ImGui::Begin("navbar", nullptr, windowFlags);

    for (size_t i = 0; i < _elements.size(); i++) {
        ImGui::PushID(i);

        _elements[i]->render();

        ImGui::PopID();
        ImGui::SameLine();
    }

    ImGui::End();
}

bool NavBar::isClicked() {
    for (const auto &element: _elements) {
        if (element->isClicked()) {
            return true;
        }
    }
    return false;
}

double NavBar::getDistance() {
    double minDistance = 0;
    for (const auto &element: _elements) {
        if (element->getDistance() < minDistance) {
            minDistance = element->getDistance();
        }
    }
    return minDistance;
}

void NavBar::exec() {
    std::vector<std::pair<std::unique_ptr<GameElement> &, double>> contenders;

    for (std::unique_ptr<GameElement> &element: _elements) {
        if (element->isClicked()) {
            contenders.emplace_back(element, element->getDistance());
        }
    }

    if (!contenders.empty()) {
        size_t minIdx = 0;
        double minDistance = contenders[0].second;

        for (size_t i = 0; i < contenders.size(); i++) {
            if (contenders[i].second < minDistance) {
                minDistance = contenders[i].second;
                minIdx = i;
            }
        }

        contenders[minIdx].first->exec();
    }
}
