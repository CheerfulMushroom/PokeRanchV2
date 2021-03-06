#ifndef POKERANCH_V2_GUI_IMAGE_BUTTON_H_
#define POKERANCH_V2_GUI_IMAGE_BUTTON_H_

#include <GameElement.h>
#include <functional>
#include <imgui.h>

class ImageButton : public GameElement {
public:
    ImageButton(const std::string &path, ImVec2 size, int padding, bool isActive, const std::function<void()> &func);

    void render() override;
    bool isClicked() override;
    double getDistance() override;
    void exec() override;

private:
    std::string _pathToPicture;

    bool _isActive;
    int _padding;
    int _texture;
    bool _isClicked;

    ImVec2 _size;

    std::function<void ()> _execFunc;
};

#endif