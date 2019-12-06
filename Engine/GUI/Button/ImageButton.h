#ifndef POKERANCH_V2_GUI_IMAGE_BUTTON_H_
#define POKERANCH_V2_GUI_IMAGE_BUTTON_H_

#include <GameElement.h>
#include <functional>
#include <imgui.h>

class ImageButton : public GameElement {
public:
    ImageButton(const std::string &path, ImVec2 size, int padding, bool disable, const std::function<void()> &func);

    void exec() override;
    void render() override;
    void update(double) override {}

private:
    std::string _pathToPicture;

    bool _disabled;
    int _padding;
    int _texture;

    ImVec2 _size;

    std::function<void ()> _execFunc;
};

#endif