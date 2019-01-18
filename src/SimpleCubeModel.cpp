#include <SimpleCubeModel.h>
#include <cstring>

SimpleCubeModel::SimpleCubeModel()
    : vertexAttributes({
        AbstractModelItem::GlVertexAttribInput{3, GL_FLOAT, 3*sizeof(GLfloat)}, // position
    })
{}

SimpleCubeModel::~SimpleCubeModel() {}

GLsizeiptr SimpleCubeModel::getVBOSize() const
{
    return 8*8*sizeof(GLfloat);
}

GLsizeiptr SimpleCubeModel::getEBOSize() const
{
    return 36*sizeof(GLuint);
}

void SimpleCubeModel::fillInVBO(void *buffer) const
{
    static const GLfloat vertices[] = {
        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
    };
    std::memcpy(buffer, vertices, sizeof(vertices));
}

void SimpleCubeModel::fillInEBO(void *buffer) const
{
    static const GLuint indices[] = {
        0, 1, 2,
        0, 2, 3,
        1, 5, 6,
        1, 6, 2,
        5, 4, 7,
        5, 7, 6,
        4, 0, 3,
        4, 3, 7,
        3, 2, 6,
        3, 6, 7,
        5, 1, 0,
        5, 0, 4
    };
    std::memcpy(buffer, indices, sizeof(indices));
}

const std::vector<AbstractModelItem::GlVertexAttribInput> &SimpleCubeModel::getVertexAttributes() const
{
    return vertexAttributes;
}
