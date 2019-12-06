#include <Button.h>
#include <imgui.h>
#include <iostream>

Button::Button(std::string _label, const std::function<void()> &func)  : _execFunc(func){
    assert(_label.size() < labelSize);
    memcpy(label, _label.c_str(), labelSize);
}

void Button::exec() {
    _execFunc();
}


void Button::render() {
    if (ImGui::Button(label)) {
        exec();
    }
}

