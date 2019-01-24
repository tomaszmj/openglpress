#include <ShaderProgram.h>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <glm/gtc/type_ptr.hpp>

ShaderProgram::ShaderProgram(const std::string &vertexPath, const std::string &fragmentPath)
{
    std::string vertex_code = readShaderCode(vertexPath);
    GLuint vertex_id = compileShader(vertex_code.c_str(), GL_VERTEX_SHADER);

    std::string fragment_code = readShaderCode(fragmentPath);
    GLuint fragment_id = compileShader(fragment_code.c_str(), GL_FRAGMENT_SHADER);

    id = static_cast<GLint>(glCreateProgram());
    glAttachShader(id, vertex_id);
    glAttachShader(id, fragment_id);
    glLinkProgram(id);

    GLint success;
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if(!success)
    {
        GLchar infoLog[512];
        glGetProgramInfoLog(id, sizeof(infoLog), nullptr, infoLog);
        std::string msg = std::string("Shader program linking: ") + infoLog;
        throw std::runtime_error(msg);
    }

    glDeleteShader(vertex_id);
    glDeleteShader(fragment_id);
}

void ShaderProgram::use() const
{
    glUseProgram(getId());
}

GLint ShaderProgram::getId() const
{
    return id;
}

void ShaderProgram::setFloatUniform(const std::string &name, const float value) const
{
    GLint location = glGetUniformLocation(id, name.c_str());
    glUniform1f(location, value);
}

void ShaderProgram::setVec3Uniform(const std::string &name, const glm::vec3 &value) const
{
    GLint location = glGetUniformLocation(id, name.c_str());
    glUniform3f(location, value.x, value.y, value.z);
}

void ShaderProgram::setMat4Uniform(const std::string &name, const glm::mat4 &value) const
{
    GLint location = glGetUniformLocation(id, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

std::string ShaderProgram::readShaderCode(const std::string &shader_path)
{
    std::ifstream shader_file;
    shader_file.exceptions(std::ifstream::badbit);
    shader_file.open(shader_path);
    std::stringstream shader_stream;
    shader_stream << shader_file.rdbuf();
    shader_file.close();
    return shader_stream.str();
}

GLuint ShaderProgram::compileShader(const GLchar* shader_code, GLenum shader_type)
{
    GLuint shader_id = glCreateShader(shader_type);
    glShaderSource(shader_id, 1, &shader_code, nullptr);
    glCompileShader(shader_id);

    GLint success = 0;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        GLchar infoLog[512];
        glGetShaderInfoLog(shader_id, sizeof(infoLog), nullptr, infoLog);
        std::string msg = std::string("Shader compilation: ") + infoLog;
        throw std::runtime_error(msg);
    }
    return shader_id;
}
