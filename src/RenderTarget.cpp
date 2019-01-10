#include <RenderTarget.h>
#include <Shprogram.h>
#include <Textures.h>
#include <VAOWrapper.h>

RenderTarget::RenderTarget(const ShaderProgram &shader_program, std::unique_ptr<VAOWrapper> vao_wrapper)
    : shaderProgram(shader_program), vaoWrapper(std::move(vao_wrapper)), modelMatrix(1), textures(nullptr)
{
    initializeOpenGLBuffers();
}

RenderTarget::RenderTarget(const ShaderProgram &shader_program, std::unique_ptr<VAOWrapper> vao_wrapper, const glm::mat4 &model_matrix)
    : shaderProgram(shader_program), vaoWrapper(std::move(vao_wrapper)), modelMatrix(model_matrix), textures(nullptr)
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
