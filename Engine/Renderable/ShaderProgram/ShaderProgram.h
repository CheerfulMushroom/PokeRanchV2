#ifndef PROJECT_INCLUDE_SHADER_HPP_
#define PROJECT_INCLUDE_SHADER_HPP_

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <tuple>
#include <glm/glm.hpp>
#include <GL/glew.h>

class ShaderProgram {
 public:
    ShaderProgram(std::tuple<std::string, std::string> shader_sources);

    ShaderProgram() = default;

    void use();
    GLuint getProgram();

    bool setSources(std::tuple<std::string, std::string> shader_sources);

    bool compileSources();

    void set_mat4_uniform(const std::string &name, const glm::mat4 &value) const;

 private:
    GLuint _program;

    std::string _vs;
    std::string _fs;

};

#endif  // PROJECT_INCLUDE_SHADER_HPP_
