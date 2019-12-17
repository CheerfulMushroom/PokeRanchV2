#include "Button.h"
#include "imgui.h"

Button::Button(std::string label, std::function<void()> func) :
        _label(std::move(label)),
        _execFunc(std::move(func)),
        _isClicked(false) {}


void Button::render() {
    if (ImGui::Button(_label.c_str())) {
        _isClicked = true;
    }
}

bool Button::isClicked() {
    return _isClicked;
}

double Button::getDistance() {
    return 0;
}

void Button::exec() {
    _isClicked = false;
    _execFunc();
}


