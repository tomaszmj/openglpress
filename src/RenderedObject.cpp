#include <RenderedObject.h>
#include <ShaderProgram.h>
#include <VAOWrapper.h>
#include <Textures.h>
#include <glm/gtc/type_ptr.hpp>

RenderedObject::RenderedObject(const ShaderProgram &shader_program, const VAOWrapper &vao_wrapper,
                               glm::mat4 model_matrix, const Texture &texture)
    : modelMatrix(model_matrix), shaderProgram(shader_program), vaoWrapper(vao_wrapper), texture(texture)
{ }

void RenderedObject::prepareRender() const
{
    shaderProgram.use();
    vaoWrapper.bind();
    texture.bind(shaderProgram.getId(), "Texture");
    shaderProgram.setMat4Uniform("model", modelMatrix);
}

void RenderedObject::render() const
{
    glDrawElements(GL_TRIANGLES, vaoWrapper.getNumberOfVertices(), GL_UNSIGNED_INT, nullptr);
}

void RenderedObject::endRender() const
{
    vaoWrapper.unbind();
}

const ShaderProgram &RenderedObject::getShaderProgram() const
{
    return shaderProgram;
}

const VAOWrapper &RenderedObject::getVaoWrapper() const
{
    return vaoWrapper;
}

const Texture &RenderedObject::getTexture() const
{
    return texture;
}
