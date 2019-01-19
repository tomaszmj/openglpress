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
    shaderProgram.setMat4Uniform("model", modelMatrix);
    shaderProgram.setVec3Uniform("lightColor", glm::vec3(1.0, 1.0, 1.0));
    shaderProgram.setVec3Uniform("lightPosition", glm::vec3(14.0f, 29.0f, 14.0f));
    shaderProgram.setVec3Uniform("objectColor", glm::vec3(0.0, 1.0, 0.0));
    glDrawElements(GL_TRIANGLES, vaoWrapper.getNumberOfVertices(), GL_UNSIGNED_INT, nullptr);
    vaoWrapper.unbind();
}
