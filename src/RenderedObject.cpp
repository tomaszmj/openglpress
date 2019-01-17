#include <RenderedObject.h>
#include <ShaderProgram.h>
#include <Textures.h>
#include <VAOWrapper.h>
#include <glm/gtc/type_ptr.hpp>

RenderedObject::RenderedObject(const ShaderProgram &shader_program, const VAOWrapper &vao_wrapper,
                               glm::mat4 model_matrix, Textures *textures)
    : modelMatrix(model_matrix), shaderProgram(shader_program), vaoWrapper(vao_wrapper), textures(textures)
{
}

void RenderedObject::render(const glm::mat4 &view_projection_matrix) const
{
    shaderProgram.use();
    if(textures)
        textures->bindAll(shaderProgram.getId());
    vaoWrapper.bind();
    shaderProgram.setMat4Uniform("transform", view_projection_matrix * modelMatrix);
    glDrawElements(GL_TRIANGLES, vaoWrapper.getNumberOfVertices(), GL_UNSIGNED_INT, nullptr);
    vaoWrapper.unbind();
}
