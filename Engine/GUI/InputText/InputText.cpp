#include "InputText.h"
#include "imgui.h"

InputText::InputText(std::string label, bool spacesAllowed, bool isPassword) :
        _label(std::move(label)),
        _bufferSize(64),
        _windowFlags(0) {
    _buffer.reserve(_bufferSize);

    if (!spacesAllowed) {
        _windowFlags |= ImGuiInputTextFlags_CharsNoBlank;
    }
    if (isPassword) {
        _windowFlags |= ImGuiInputTextFlags_Password;
    }

}


void InputText::render() {
    ImGui::InputText(_label.c_str(), _buffer.data(), _bufferSize, _windowFlags);
    _buffer.resize(strlen(_buffer.data()));
}

std::string InputText::getBuffer() {
    return _buffer;
}
