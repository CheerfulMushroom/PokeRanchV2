#include "ShaderProgram.h"
#include <cstring>

ShaderProgram::ShaderProgram(std::tuple<std::string, std::string> shader_sources) : _program(0) {
    setSources(std::move(shader_sources));
    compileSources();
}

void ShaderProgram::use() {
    glUseProgram(_program);
}

bool ShaderProgram::setSources(std::tuple<std::string, std::string> shader_sources) {
    std::ifstream v_shader_file(std::get<0>(shader_sources));
    std::ifstream f_shader_file(std::get<1>(shader_sources));

    if (!(v_shader_file && f_shader_file)) {
        return false;
    }

    std::stringstream v_shader_stream;
    std::stringstream f_shader_stream;

    v_shader_stream << v_shader_file.rdbuf();
    f_shader_stream << f_shader_file.rdbuf();

    _vs = v_shader_stream.str();
    _fs = f_shader_stream.str();

    return true;
}

bool ShaderProgram::compileSources() {
    const char *v_shader_source = _vs.c_str();
    const char *f_shader_source = _fs.c_str();

    //  Компиляция и сборка шейдеров

    GLuint vertices_shader = 0;
    GLuint fragment_shader = 0;

    vertices_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertices_shader, 1, &(v_shader_source), nullptr);
    glCompileShader(vertices_shader);


    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &(f_shader_source), nullptr);
    glCompileShader(fragment_shader);

    // Проверка шейдеров и вывод лога в случае ошибки

    GLint success;
    GLchar infoLog[1024];


    glGetShaderiv(vertices_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertices_shader, 1024, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        return false;
    }

    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment_shader, 1024, nullptr, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        return false;
    }

    _program = glCreateProgram();
    glAttachShader(_program, vertices_shader);
    glAttachShader(_program, fragment_shader);
    glLinkProgram(_program);

    glDeleteShader(vertices_shader);
    glDeleteShader(fragment_shader);

    _vs.clear();
    _fs.clear();

    return true;
}

GLuint ShaderProgram::getProgram() {
    return _program;
}

void ShaderProgram::setMat4Uniform(const std::string &name, const glm::mat4 &value) const {
    glUniformMatrix4fv(glGetUniformLocation(_program, name.c_str()), 1, GL_FALSE, &value[0][0]);
}