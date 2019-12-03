#include <ImageButton.h>
#include <GL/glew.h>
#include <opencv2/opencv.hpp>
#include <imgui_internal.h>

static unsigned int texture_from_file(std::string &path) {  // Перенести в utils
    unsigned int texture_id;
    glGenTextures(1, &texture_id);

    cv::Mat image = cv::imread(path);

    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.cols, image.rows, 0, GL_BGR, GL_UNSIGNED_BYTE, image.ptr());

    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    cv::flip(image, image, 0);

    glBindTexture(GL_TEXTURE_2D, 0);

    return texture_id;
}

ImageButton::ImageButton(const std::string &path, ImVec2 size, int padding, bool disable, const std::function<void()> &func) :
    _pathToPicture(path),
    _size(size),
    _padding(padding),
    _disabled(disable),
    _execFunc(func) {
    _texture = texture_from_file(_pathToPicture);
}

void ImageButton::exec() {
    _execFunc();
}

void ImageButton::render() {
    if (_disabled) {
        ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
        ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.2f);
    }
    // будет ли работать без PushID ?

    if (ImGui::ImageButton((ImTextureID) _texture,
            _size,
            ImVec2(0, 0),
            ImVec2(1, 1),
            _padding,
            ImVec4(0.0f, 0.0f, 0.f, 1.0f))) {
        exec();
    }

    if (_disabled) {
        ImGui::PopItemFlag();
        ImGui::PopStyleVar();
    }
}