#include <RenderTarget.h>

RenderTarget::RenderTarget(const ShaderProgram &shader_program, const AbstractModelItem &model_item)
    : VAO(0), shaderProgram(shader_program), modelItem(model_item), modelMatrix(1), textures(nullptr)
{
    initializeOpenGLBuffers();
}

RenderTarget::RenderTarget(const ShaderProgram &shader_program, const AbstractModelItem &model_item, const glm::mat4 &model_matrix)
    : VAO(0), shaderProgram(shader_program), modelItem(model_item), modelMatrix(model_matrix), textures(nullptr)
{
    initializeOpenGLBuffers();
}

RenderTarget::~RenderTarget()
{

}

void RenderTarget::attachTextures(const Textures *textures)
{
    this->textures = textures;
}

void RenderTarget::setModelMatrix(const glm::mat4 model_matrix)
{
    modelMatrix = model_matrix;
}

void RenderTarget::render(const glm::mat4 &view_projection_matrix)
{

}

void RenderTarget::initializeOpenGLBuffers()
{

}
