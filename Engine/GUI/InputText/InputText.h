#ifndef POKERANCHV2_INPUTTEXT_H
#define POKERANCHV2_INPUTTEXT_H

#include <functional>

#include "imgui.h"
#include "GameElement.h"


class InputText : public GameElement {
public:
    InputText(std::string label, bool spacesAllowed, bool isPassword);

    void render() override;
    std::string getBuffer();

private:
    std::string _label;
    const int _bufferSize;
    std::string _buffer;
    ImGuiWindowFlags _windowFlags;
};


#endif //POKERANCHV2_INPUTTEXT_H
