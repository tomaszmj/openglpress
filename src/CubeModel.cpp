#include <CubeModel.h>
#include <cstring>

CubeModel::CubeModel()
    : vertexAttributes({
        AbstractModelItem::GlVertexAttribInput{3, GL_FLOAT, 3*sizeof(GLfloat)}, // position
        AbstractModelItem::GlVertexAttribInput{3, GL_FLOAT, 3*sizeof(GLfloat)}, // normal vector
        AbstractModelItem::GlVertexAttribInput{2, GL_FLOAT, 2*sizeof(GLfloat)}  // texture coordinates
    })
{}

CubeModel::~CubeModel() {}

GLsizeiptr CubeModel::getVBOSize() const
{
    return 24*8*sizeof(GLfloat);
}

GLsizeiptr CubeModel::getEBOSize() const
{
    return 36*sizeof(GLuint);
}

void CubeModel::fillInVBO(void *buffer) const
{
    static const GLfloat vertices[] = {
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,

         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,

         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,

        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
    };
    std::memcpy(buffer, vertices, sizeof(vertices));
}

void CubeModel::fillInEBO(void *buffer) const
{
    static const GLuint indices[] = {
        0, 1, 2,
        0, 2, 3,
        4, 5, 6,
        4, 6, 7,
        8, 9, 10,
        8, 10, 11,
        12, 13, 14,
        12, 14, 15,
        16, 17, 18,
        16, 18, 19,
        20, 21, 22,
        20, 22, 23,
    };
    std::memcpy(buffer, indices, sizeof(indices));
}

const std::vector<AbstractModelItem::GlVertexAttribInput> &CubeModel::getVertexAttributes() const
{
    return vertexAttributes;
}
