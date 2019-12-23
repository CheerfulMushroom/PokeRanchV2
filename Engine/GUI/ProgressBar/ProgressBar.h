#ifndef GUI_PROGRESS_BAR_H_
#define GUI_PROGRESS_BAR_H_

#include <GameElement.h>
#include <imgui.h>
#include <sstream>

class ProgressBar : public GameElement {
 public:
    ProgressBar(ImVec2 size, const std::string &title);

    void render() override;

    void setProgress(float value);
    void setCapacity(float value);

 private:
    ImVec2 _size;

    float _progress;
    float _capacity;

    std::string _title;
    std::string _capacityBuf;
};


#endif  // GUI_PROGRESS_BAR_H_