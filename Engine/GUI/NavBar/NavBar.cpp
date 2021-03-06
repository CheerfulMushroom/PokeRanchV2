#include "NavBar.h"
#include "imgui.h"
#include "imgui_internal.h"

NavBar::NavBar() : _windowFlags(0) {
#ifndef GUI_DEBUG
    _windowFlags |= ImGuiWindowFlags_NoTitleBar;
    _windowFlags |= ImGuiWindowFlags_NoResize;
    _windowFlags |= ImGuiWindowFlags_NoBackground;
    _windowFlags |= ImGuiWindowFlags_NoMove;
#endif
}

void NavBar::render() {
    ImGui::Begin("navbar", nullptr, _windowFlags);

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
    std::vector<std::pair<std::shared_ptr<GameElement> &, double>> contenders;

    for (std::shared_ptr<GameElement> &element: _elements) {
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

void NavBar::addElement(std::shared_ptr<GameElement> element) {
    _elements.push_back(std::move(element));
}
