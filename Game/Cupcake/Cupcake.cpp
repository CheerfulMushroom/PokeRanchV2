#include "Cupcake.h"
#include "PathManager.h"


Cupcake::Cupcake(std::string basePath,
                 std::shared_ptr<Camera> camera,
                 glm::vec3 translate,
                 float scale,
                 glm::vec3 angles,
                 int width,
                 int height) :
        _rootPath(std::move(basePath)),
        _camera(std::move(camera)),
        _translate(translate),
        _scale(scale),
        _angles(angles),
        _width(width),
        _height(height),
        _currCake(1) {
    PathManager pathManager;
    std::string modelPath = pathManager.getStaticModelPath(_rootPath + std::to_string(_currCake));
    _model = Model(modelPath,
                   _camera.get(),
                   _translate,
                   _scale,
                   _angles,
                   _width,
                   _height,
                   std::string("puff"));
}
void Cupcake::render() {
   _model.render();
}
int Cupcake::eat() {
    _currCake++;
    if (_currCake > 6) {
        _currCake = 6;
        return 0;
    }

    PathManager pathManager;
    std::string modelPath = pathManager.getStaticModelPath(_rootPath + std::to_string(_currCake));
    _model = Model(modelPath,
                   _camera.get(),
                   _translate,
                   _scale,
                   _angles,
                   _width,
                   _height,
                   std::string("puff"));
    return 10;
}
