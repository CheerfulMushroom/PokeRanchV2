#include <iostream>

<<<<<<< HEAD
static auto func = []() {
    std::cout << "log in!" << std::endl;
};
=======
#include "Form.h"
#include "imgui.h"

>>>>>>> 995b53d2eb7d35290f9e8d15619421eed58bcd92

Form::Form(): _windowFlags(0) {
#ifndef GUI_DEBUG
    _windowFlags |= ImGuiWindowFlags_NoTitleBar;
    _windowFlags |= ImGuiWindowFlags_NoResize;
    _windowFlags |= ImGuiWindowFlags_NoBackground;
    _windowFlags |= ImGuiWindowFlags_NoMove;
#endif
}

void Form::addElement(std::shared_ptr<GameElement> element) {
    _elements.push_back(std::move(element));
}

void Form::render() {
    ImGui::Begin("form", nullptr, _windowFlags);

    for (const auto &element:_elements) {
        element->render();
    }

    ImGui::End();
}

bool Form::isClicked() {
    for (const auto &element: _elements) {
        if (element->isClicked()) {
            return true;
        }
    }
    return false;
}

double Form::getDistance() {
    double minDistance = 0;
    for (const auto &element: _elements) {
        if (element->getDistance() < minDistance) {
            minDistance = element->getDistance();
        }
    }
    return minDistance;
}

void Form::exec() {
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


