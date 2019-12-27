#ifndef POKERANCHV2_CUPCAKE_H
#define POKERANCHV2_CUPCAKE_H

#include <memory>
#include <glm/glm.hpp>

#include "GameElement.h"
#include "Camera.h"
#include "Model.h"

class Cupcake : public GameElement {
public:
    Cupcake(std::string basePath,
            std::shared_ptr<Camera> camera,
            glm::vec3 translate,
            float scale,
            glm::vec3 angles,
            int width,
            int height);
    void render() override;

    int eat();

private:
    std::shared_ptr<Camera> _camera;
    glm::vec3 _translate;
    float _scale;
    glm::vec3 _angles;
    int _width;
    int _height;
    std::string _rootPath;
    int _currCake;
    Model _model;
};


#endif //POKERANCHV2_CUPCAKE_H
