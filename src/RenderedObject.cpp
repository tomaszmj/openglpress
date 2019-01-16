#include <RenderedObject.h>
#include <Shprogram.h>
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
    shaderProgram.Use();
    if(textures)
        textures->bindAll(shaderProgram.get_programID());
    vaoWrapper.bind();
    glm::mat4 transform = view_projection_matrix * modelMatrix;
    GLint transform_loc = glGetUniformLocation(shaderProgram.get_programID(), "transform");
    glUniformMatrix4fv(transform_loc, 1, GL_FALSE, glm::value_ptr(transform));
    glDrawElements(GL_TRIANGLES, vaoWrapper.getNumberOfVertices(), GL_UNSIGNED_INT, nullptr);
    vaoWrapper.unbind();
}
