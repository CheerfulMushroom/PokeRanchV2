#include <Form.h>
#include <imgui.h>

Form::Form() {
    memset(loginBuf, 0, fieldSize);
    memset(passwordBuf, 0, fieldSize);
}

void Form::render() {
    ImGui::Begin("AuthForm");

    ImGui::Text("login");
    ImGui::InputText("what", loginBuf, fieldSize, ImGuiInputTextFlags_CharsNoBlank);

    ImGui::Text("password");
    ImGui::InputText("lol", passwordBuf, fieldSize, ImGuiInputTextFlags_Password | ImGuiInputTextFlags_CharsNoBlank);

    ImGui::End();
}