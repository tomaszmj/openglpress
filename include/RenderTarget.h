#pragma once
#include <glm/glm.hpp>
#include <memory>

class VAOWrapper;
class ShaderProgram;
class Textures;

class RenderTarget
{
public:
    glm::mat4 modelMatrix;

    RenderTarget(const ShaderProgram &shader_program, std::unique_ptr<VAOWrapper> vao_wrapper);
    RenderTarget(const ShaderProgram &shader_program, std::unique_ptr<VAOWrapper> vao_wrapper, const glm::mat4 &model_matrix);
    void attachTextures(const Textures *textures);
    void render(const glm::mat4 &view_projection_matrix);

private:
    const ShaderProgram &shaderProgram;
    std::unique_ptr<VAOWrapper> vaoWrapper;
    const Textures *textures;
};
