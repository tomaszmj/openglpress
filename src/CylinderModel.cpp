#include <CylinderModel.h>
#include <cmath>

const double PI = std::atan(1)*4;

CylinderModel::CylinderModel(unsigned sides, unsigned height_segments)
    : vertexAttributes({
        AbstractModelItem::GlVertexAttribInput{3, GL_FLOAT, 3*sizeof(GLfloat)}, // position
        AbstractModelItem::GlVertexAttribInput{1, GL_FLOAT, 1*sizeof(GLfloat)}, // tmp
    }), sides(sides), heightSegments(height_segments)
{}

CylinderModel::~CylinderModel() {}

GLsizeiptr CylinderModel::getVBOSize() const
{
    return (sides * (heightSegments + 1) + 2) * 4 * sizeof(GLfloat);
}

GLsizeiptr CylinderModel::getEBOSize() const
{
    return (sides * heightSegments * 2 + sides * 2) * 3 * sizeof(GLuint);
}

void CylinderModel::fillInVBO(void *buffer) const
{
    GLfloat *buffer_float = reinterpret_cast<GLfloat*>(buffer);
    double sides_f = static_cast<double>(sides);
    double height_segments_f = static_cast<double>(heightSegments);
    for(unsigned i = 0; i < sides; ++i)
    {
        double alpha = static_cast<double>(i) * 2.0 * PI / sides_f;
        GLfloat x = static_cast<GLfloat>(std::cos(alpha) * 0.5);
        GLfloat z = static_cast<GLfloat>(std::sin(alpha) * 0.5);
        GLfloat tmp = static_cast<GLfloat>(static_cast<double>(i) / sides_f);
        for(unsigned j = 0; j <= heightSegments; ++j)
        {
            GLfloat y = static_cast<GLfloat>(-0.5 + static_cast<double>(j) / height_segments_f);
            buffer_float = fillOneVertexInVBO(buffer_float, x, y, z, tmp);
        }
    }
    buffer_float = fillOneVertexInVBO(buffer_float, 0.0, -0.5, 0.0, 0.0);
    fillOneVertexInVBO(buffer_float, 0.0, 0.5, 0.0, 1.0);
}

void CylinderModel::fillInEBO(void *buffer) const
{
    GLuint *buffer_uint = reinterpret_cast<GLuint*>(buffer);
    GLuint lower_base_center_in_vbo = sides * (heightSegments + 1);
    for(unsigned i = 0; i < sides; ++i)
    {
        for(unsigned j = 0; j < heightSegments; ++j)
        {
            // sides:
            buffer_uint[0] = indexInVBO(i, j);
            buffer_uint[1] = indexInVBO((i + 1) % sides, j);
            buffer_uint[2] = indexInVBO((i + 1) % sides, j + 1);
            buffer_uint[3] = indexInVBO(i, j);
            buffer_uint[4] = indexInVBO((i + 1) % sides, j + 1);
            buffer_uint[5] = indexInVBO(i, j + 1);
            buffer_uint += 6;
        }
        // lower base:
        buffer_uint[0] = indexInVBO(i, 0);
        buffer_uint[1] = lower_base_center_in_vbo;
        buffer_uint[2] = indexInVBO((i + 1) % sides, 0);
        // upper base:
        buffer_uint[3] = indexInVBO(i, heightSegments);
        buffer_uint[4] = lower_base_center_in_vbo + 1;
        buffer_uint[5] = indexInVBO((i + 1) % sides, heightSegments);
        buffer_uint += 6;
    }
}

const std::vector<AbstractModelItem::GlVertexAttribInput> &CylinderModel::getVertexAttributes() const
{
    return vertexAttributes;
}

GLuint CylinderModel::indexInVBO(unsigned side_index, unsigned height_index) const
{
    return side_index * (heightSegments + 1) + height_index;
}

GLfloat *CylinderModel::fillOneVertexInVBO(GLfloat *buffer, GLfloat x, GLfloat y, GLfloat z, GLfloat tmp_parameter) const
{
    buffer[0] = x;
    buffer[1] = y;
    buffer[2] = z;
    buffer[3] = tmp_parameter;
    buffer += 4;
    return buffer;
}
