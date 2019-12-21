#include <vector>

#include "Engine.h"
#include "Camera.h"
#include "GameElement.h"
#include "PathManager.h"

// Предназначен для перебора заданных моделей в статической позиции
template <class modelType>
class ModelSwitcher : public GameElement {
 public:
    ModelSwitcher(GameState &state,
                  std::vector<std::string> &modelNames,
                  Camera *camera,
                  glm::vec3 translate,
                  float scale,
                  glm::vec3 angles,
                  int width,
                  int height,
                  std::string type,
                  std::string animationName);

    void switchToLeft();
    void switchToRight();

    std::string returnCurrentModelName();

 private:
    GameState &_state;
    int _id;
    std::vector<std::string> _modelNames;
    PathManager _pathManager;

    Camera *_camera;
    glm::vec3 _translate;
    float _scale;
    glm::vec3 _angles;
    int _width;
    int _height;

    std::string _type;
    std::string _animationName;
};