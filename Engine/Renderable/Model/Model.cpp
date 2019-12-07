#include "Model.h"
#include "Camera.h"
#include "imgui.h"

static unsigned int textureFromFile(const char *path, const std::string &directory);

Model::Model(std::string const &path,
             Camera *camera,
             glm::vec3 translate,
             float scale,
             glm::vec3 angles,
             //float angle,
             int width,
             int height,
             std::string name) {
    loadModel(path);
    this->_translate = translate;
    this->_scaleFactor = scale;
    this->_angles = angles;
    this->_camera = camera;
    this->_width = width;
    this->_height = height;
    this->name = name;


    #ifndef DEBUG_MODEL
    std::tuple<std::string, std::string> sources = std::make_tuple("Engine/Renderable/Shaders/v_model_shader.vs",
                                                                   "Engine/Renderable/Shaders/f_model_shader.fs");
    shader = ShaderProgram(sources);
    #endif
}

void Model::loadModel(std::string const &path) {
    Assimp::Importer import;

    const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "Assimp import error" << std::endl;
        return;
    }

    _directory = path.substr(0, path.find_last_of('/'));

    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode *node, const aiScene *scene) {
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        _meshes.push_back(processMesh(mesh, scene));
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene) {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex = {};

        glm::vec3 vector;

        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.position = vector;

        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.normal = vector;

        if (mesh->mTextureCoords[0]) {
            glm::vec2 vec;

            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.tex_coords = vec;
        } else {
            vertex.tex_coords = glm::vec2(0.0f, 0.0f);
        }


        vertices.push_back(vertex);

    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

    std::vector<Texture> diffuse_maps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuse_maps.begin(), diffuse_maps.end());

    std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    // 3. normal maps
    std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
    // 4. height maps
    std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

    return Mesh(vertices, indices, textures);  // TODO rvalue
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string type_name) {
    std::vector<Texture> textures;

    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {

        aiString str;
        mat->GetTexture(type, i, &str);

        bool skip = false;
        for (unsigned int j = 0; j < _texturesLoaded.size(); j++) {
            if (std::strcmp(_texturesLoaded[j].path.data(), str.C_Str()) == 0) {
                textures.push_back(_texturesLoaded[j]);
                skip = true;
                break;
            }
        }

        if (!skip) {
            Texture texture;
            texture.id = textureFromFile(str.C_Str(), this->_directory);
            texture.type = type_name;
            texture.path = str.C_Str();
            textures.push_back(texture);
            _texturesLoaded.push_back(texture);
        }

    }

    return textures;
}

void Model::render() {

    #ifdef DEBUG_MODEL
        ImGui::Begin(this->name.c_str());
        ImGui::SliderFloat("scaleFactor", &this->_scaleFactor, 0.0f, 0.5f);
        ImGui::SliderFloat("translate.x", &this->_translate.x, -5.0f, 5.0f);
        ImGui::SliderFloat("translate.y", &this->_translate.y, -5.0f, 5.0f);
        ImGui::SliderFloat("translate.z", &this->_translate.z, -5.0f, 5.0f);
        ImGui::SliderFloat("angle.x", &this->_angles.x, -360.0f, 360.0f);
        ImGui::SliderFloat("angle.y", &this->_angles.y, -360.0f, 360.0f);
        ImGui::SliderFloat("angle.z", &this->_angles.z, -360.0f, 360.0f);
        ImGui::End();
    #endif

    glEnable(GL_DEPTH_TEST);
    shader.use();
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float) _width / (float) _height, 0.1f, 100.0f);  //TODO получать ширину и высоту от класса "мега-мозг"

    glm::mat4 view = _camera->GetViewMatrix();

    shader.setMat4Uniform("projection", projection);
    shader.setMat4Uniform("view", view);

    glm::mat4 pikachu_mod = glm::mat4(1.0f);
    pikachu_mod = glm::translate(pikachu_mod, _translate);
    pikachu_mod = glm::scale(pikachu_mod, glm::vec3(_scaleFactor));
    pikachu_mod = glm::rotate(pikachu_mod, glm::radians(_angles.x), glm::vec3(1.0f, 0.0f, 0.0f));
    pikachu_mod = glm::rotate(pikachu_mod, glm::radians(_angles.y), glm::vec3(0.0f, 1.0f, 0.0f));
    pikachu_mod = glm::rotate(pikachu_mod, glm::radians(_angles.z), glm::vec3(0.0f, 0.0f, 1.0f));

    shader.setMat4Uniform("model", pikachu_mod);

    for (auto mesh: _meshes) {
        mesh.drawMesh(shader);
    }

    glDisable(GL_DEPTH_TEST);

}

static unsigned int textureFromFile(const char *path, const std::string &directory) {
    std::string filename = std::string(path);

    filename = directory + '/' + filename;

    unsigned int texture_id;
    glGenTextures(1, &texture_id);

    cv::Mat image = cv::imread(filename);

    glBindTexture(GL_TEXTURE_2D, texture_id);

    bool has_alpha = image.channels() == 4;

    if (has_alpha) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.cols, image.rows, 0, GL_BGRA, GL_UNSIGNED_BYTE, image.ptr());
    } else {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.cols, image.rows, 0, GL_BGR, GL_UNSIGNED_BYTE, image.ptr());
    }

    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.cols, image.rows, 0, GL_BGR, GL_UNSIGNED_BYTE, image.ptr());
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.cols, image.rows, 0, GL_BGRA, GL_UNSIGNED_BYTE, image.ptr());
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    cv::flip(image, image, 0);

    glBindTexture(GL_TEXTURE_2D, 0);

    return texture_id;
}
