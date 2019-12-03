#ifndef POKERANCH_V2_GUI_IMAGE_BUTTON_H_
#define POKERANCH_V2_GUI_IMAGE_BUTTON_H_

#include <ImageButton.h>
#include <IGameElement.h>
#include <functional>
#include <imgui.h>

class ImageButton : IGameElement {
public:
    ImageButton(const std::string &path, ImVec2 size, int padding, bool disable, const std::function<void()> &func);

    bool isClicked() = delete;
    double getDistance() = delete;
    std::string getMeta(std::string) = delete;


    void exec();
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