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
    void render(const glm::mat4 &view_projection_matrix) const;

private:
    const ShaderProgram &shaderProgram;
    const VAOWrapper &vaoWrapper;
    const Texture &texture;
};
