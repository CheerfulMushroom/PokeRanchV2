#include <Button.h>
#include <imgui.h>
#include <iostream>

Button::Button(std::string _label) {
    assert(_label.size() < labelSize);
    memcpy(label, _label.c_str(), labelSize);
}

void Button::render() {
    if (ImGui::Button(label)) {
        std::cout << "Win ";
    }
}