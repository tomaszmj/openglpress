#include <RenderedObject.h>
#include <Shprogram.h>
#include <Textures.h>
#include <VAOWrapper.h>
#include <glm/gtc/type_ptr.hpp>

RenderedObject::RenderedObject(const ShaderProgram &shader_program, std::unique_ptr<VAOWrapper> vao_wrapper)
    :  modelMatrix(1), shaderProgram(shader_program), vaoWrapper(std::move(vao_wrapper)), textures(nullptr)
{ }

RenderedObject::RenderedObject(const ShaderProgram &shader_program, std::unique_ptr<VAOWrapper> vao_wrapper, const glm::mat4 &model_matrix)
    : modelMatrix(model_matrix), shaderProgram(shader_program), vaoWrapper(std::move(vao_wrapper)), textures(nullptr)
{ }

void RenderedObject::attachTextures(const Textures *textures)
{
    this->textures = textures;
}

void RenderedObject::render(const glm::mat4 &view_projection_matrix)
{
    shaderProgram.Use();
    if(textures)
        textures->bindAll(shaderProgram.get_programID());
    vaoWrapper->bind();
    glm::mat4 transform = view_projection_matrix * modelMatrix;
    GLint transform_loc = glGetUniformLocation(shaderProgram.get_programID(), "transform");
    glUniformMatrix4fv(transform_loc, 1, GL_FALSE, glm::value_ptr(transform));
    glDrawElements(GL_TRIANGLES, vaoWrapper->getNumberOfVertices(), GL_UNSIGNED_INT, nullptr);
    vaoWrapper->unbind();
}
