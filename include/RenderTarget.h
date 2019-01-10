#pragma once
#include <glm/glm.hpp>
#include <memory>

class VAOWrapper;
class ShaderProgram;
class Textures;

class RenderTarget
{
public:
   RenderTarget(const ShaderProgram &shader_program, std::unique_ptr<VAOWrapper> vao_wrapper);
   RenderTarget(const ShaderProgram &shader_program, std::unique_ptr<VAOWrapper> vao_wrapper, const glm::mat4 &model_matrix);
   ~RenderTarget();
   void attachTextures(const Textures *textures);
   void setModelMatrix(const glm::mat4 model_matrix);
   void render(const glm::mat4 &view_projection_matrix);

private:
    const ShaderProgram &shaderProgram;
    std::unique_ptr<VAOWrapper> vaoWrapper;
    glm::mat4 modelMatrix;
    const Textures *textures;

    void initializeOpenGLBuffers();
};
