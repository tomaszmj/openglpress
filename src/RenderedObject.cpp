#include <RenderedObject.h>
#include <ShaderProgram.h>
#include <VAOWrapper.h>
#include <ModelMatrix.h>
#include <Textures.h>
#include <glm/gtc/type_ptr.hpp>

RenderedObject::RenderedObject(const ShaderProgram &shader_program, const VAOWrapper &vao_wrapper,
                               ModelMatrix &model_matrix, const Texture &texture)
    : shaderProgram(shader_program), vaoWrapper(vao_wrapper), modelMatrix(model_matrix), texture(texture)
{ }

RenderedObject::~RenderedObject()
{

}

void RenderedObject::prepareRender() const
{
    shaderProgram.use();
    vaoWrapper.bind();
    texture.bind(shaderProgram.getId(), "Texture");
    shaderProgram.setMat4Uniform("model", modelMatrix.get());
}

void RenderedObject::render() const
{
    glDrawElements(GL_TRIANGLES, vaoWrapper.getNumberOfVertices(), GL_UNSIGNED_INT, nullptr);
}

void RenderedObject::endRender() const
{
    vaoWrapper.unbind();
}

void RenderedObject::animationStep(double)
{

}

const ShaderProgram &RenderedObject::getShaderProgram() const
{
    return shaderProgram;
}

const VAOWrapper &RenderedObject::getVaoWrapper() const
{
    return vaoWrapper;
}

const ModelMatrix &RenderedObject::getModelMatrix() const
{
    return modelMatrix;
}

const Texture &RenderedObject::getTexture() const
{
    return texture;
}
