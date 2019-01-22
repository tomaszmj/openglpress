#pragma once
#include <glm/glm.hpp>
#include <memory>

class ShaderProgram;
class VAOWrapper;
class Texture;

class RenderedObject
{
public:
    glm::mat4 modelMatrix;

    RenderedObject(const ShaderProgram &shader_program, const VAOWrapper &vao_wrapper,
                   glm::mat4 model_matrix, const Texture &texture);
    void prepareRender() const;
    void render() const;
    void endRender() const;
    const ShaderProgram &getShaderProgram() const;
    const VAOWrapper &getVaoWrapper() const;
    const Texture &getTexture() const;

private:
    const ShaderProgram &shaderProgram;
    const VAOWrapper &vaoWrapper;
    const Texture &texture;
};
