#include <Form.h>
#include <imgui.h>
#include <iostream>


static auto func = []() {
    std::cout << "log in!" << std::endl;
};

Form::Form() : _button("submit", func) {
    memset(loginBuf, 0, fieldSize);
    memset(passwordBuf, 0, fieldSize);
}

void Form::render() {
    ImGui::Begin("AuthForm");

    ImGui::InputText("login", loginBuf, fieldSize, ImGuiInputTextFlags_CharsNoBlank);
    ImGui::InputText("password", passwordBuf, fieldSize, ImGuiInputTextFlags_Password | ImGuiInputTextFlags_CharsNoBlank);

    _button.render();

    ImGui::End();
}