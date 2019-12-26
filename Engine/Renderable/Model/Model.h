#ifndef PREP_POKEMON_RANCH_MODEL_H
#define PREP_POKEMON_RANCH_MODEL_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <opencv2/opencv.hpp>
#include <glm/glm.hpp>

#include <GameElement.h>

#include "Mesh.h"

class Camera;

class Model : public GameElement {
public:
    Model() = default;
    Model(std::string const &path,
          Camera *camera,
          glm::vec3 translate,
          float scale,
          glm::vec3 _angles,
          //float angle,
          int width,
          int height,
          std::string name);

//    ~Model() override  = default;

    void render() override;
    std::string name;

    void update(double) override {}

    #ifdef DEBUG_MODEL
    ShaderProgram shader;
    glm::vec3 _translate;
    float _scaleFactor;
    //glm::vec3 _rotate;
    glm::vec3 _angles;
    //float _angle;
    #endif

private:
    std::vector<Mesh> _meshes;
    std::vector<Texture> _texturesLoaded;
    std::string _directory;

    Camera *_camera;

    #ifndef DEBUG_MODEL
    ShaderProgram shader;
    glm::vec3 _translate;
    float _scaleFactor;
    //glm::vec3 _rotate;
    glm::vec3 _angles;
    //float _angle;
    #endif

    int _width;
    int _height;

    void loadModel(std::string const &path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);

    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string type_name);
};

#endif // PREP_POKEMON_RANCH_MODEL_H