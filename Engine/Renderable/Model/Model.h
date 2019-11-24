#ifndef PREP_POKEMON_RANCH_MODEL_H
#define PREP_POKEMON_RANCH_MODEL_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <opencv2/opencv.hpp>
#include <glm/glm.hpp>

#include <IGameElement.h>

#include "Mesh.h"

class Camera;

class Model : public IGameElement {
public:
    Model(std::string const &path,
          Camera *camera,
          glm::vec3 translate,
          glm::vec3 scale,
          glm::vec3 rotate,
          float angle,
          int width, // выкинуть
          int heigth);

//    ~Model() override  = default;

    void render() override;

    bool isClicked() = delete;
    double getDistance() = delete;
    std::string getMeta(std::string) = delete;
    void exec() = delete;

    void update(double) override {}

    ShaderProgram shader;  // temporary public
private:
    std::vector<Mesh> _meshes;
    std::vector<Texture> _texturesLoaded;
    std::string _directory;

    //ShaderProgram shader;

    Camera *_camera;

    glm::vec3 _translate;
    glm::vec3 _scale;
    glm::vec3 _rotate;

    float _angle;
    int _width;
    int _height;

    void loadModel(std::string const &path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);

    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string type_name);
};

#endif // PREP_POKEMON_RANCH_MODEL_H