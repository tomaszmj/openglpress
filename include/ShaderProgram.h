#pragma once
#define GLEW_STATIC
#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>

class ShaderProgram
{
public:
    ShaderProgram(const std::string &vertexPath, const std::string &fragmentPath);
    void use() const;
    GLint getId() const;
    void setFloatUniform(const std::string &name, const float value) const;
    void setVec3Uniform(const std::string &name, const glm::vec3 &value) const;
    void setMat4Uniform(const std::string &name, const glm::mat4 &value) const;

private:
    GLint id;

    static std::string readShaderCode(const std::string &shader_path);
    static GLuint compileShader(const GLchar* shader_code, GLenum shader_type);
};
