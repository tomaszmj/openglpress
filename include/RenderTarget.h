#pragma once
#include <Shprogram.h>
#include <Textures.h>
#include <AbstractModelItem.h>
#include <glm/glm.hpp>

class RenderTarget
{
public:
   RenderTarget(const ShaderProgram &shader_program, const AbstractModelItem &model_item);
   RenderTarget(const ShaderProgram &shader_program, const AbstractModelItem &model_item, const glm::mat4 &model_matrix);
   ~RenderTarget();
   void attachTextures(const Textures *textures);
   void setModelMatrix(const glm::mat4 model_matrix);
   void render(const glm::mat4 &view_projection_matrix);

private:
    GLuint VAO;
    const ShaderProgram &shaderProgram;
    const AbstractModelItem &modelItem;
    glm::mat4 modelMatrix;
    const Textures *textures;

    void initializeOpenGLBuffers();
};
