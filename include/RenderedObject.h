#pragma once
#include <glm/glm.hpp>
#include <memory>

class ShaderProgram;
class VAOWrapper;
class Textures;

class RenderedObject
{
public:
    glm::mat4 modelMatrix;

    RenderedObject(const ShaderProgram &shader_program, const VAOWrapper &vao_wrapper,
                   glm::mat4 model_matrix=glm::mat4(1), Textures *textures=nullptr);
    void render(const glm::mat4 &view_projection_matrix) const;

private:
    const ShaderProgram &shaderProgram;
    const VAOWrapper &vaoWrapper;
    const Textures *textures;
};
