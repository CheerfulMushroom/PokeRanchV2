#include <ProgressBar.h>

ProgressBar::ProgressBar(ImVec2 size, const std::string &title) :
    _size(size),
    _progress(0.0f),
    _capacity(0.0f),
    _title(title) {}

void ProgressBar::setProgress(float value) {
    _progress = value;
}

void ProgressBar::setCapacity(float value) {
    _capacity = value;
}

void ProgressBar::render() {
    _capacityBuf = std::to_string((int) (_progress * _capacity)) + '/' + std::to_string((int)_capacity);
    ImGui::ProgressBar(_progress, _size, _capacityBuf.c_str());
    ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
    ImGui::Text(_title.c_str());
}