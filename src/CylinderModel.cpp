#include "CylinderModel.h"
#include <cmath>

const double PI = std::atan(1)*4;

CylinderModel::CylinderModel(unsigned sides, unsigned radius_segments, unsigned height_segments)
    : vertexAttributes({
        AbstractModelItem::GlVertexAttribInput{3, GL_FLOAT, 3*sizeof(GLfloat)}, // position
        AbstractModelItem::GlVertexAttribInput{1, GL_FLOAT, 1*sizeof(GLfloat)}, // tmp
    }), sides(sides), radiusSegments(radius_segments), heightSegments(height_segments)
{}

CylinderModel::~CylinderModel() {}

GLsizeiptr CylinderModel::getVBOSize() const
{
    return sides * (heightSegments + 1) * 4 * sizeof(GLfloat);
}

GLsizeiptr CylinderModel::getEBOSize() const
{
    return sides * heightSegments * 6 * sizeof(GLuint);
}

void CylinderModel::fillInVBO(void *buffer) const
{
    GLfloat *buffer_float = reinterpret_cast<GLfloat*>(buffer);
    double sides_f = static_cast<double>(sides);
    double height_segments_f = static_cast<double>(heightSegments);
    for(unsigned i = 0; i < sides; ++i)
    {
        double alpha = static_cast<double>(i) * 2.0 * PI / sides_f;
        GLfloat x = static_cast<float>(std::cos(alpha) * 0.5);
        GLfloat z = static_cast<float>(std::sin(alpha) * 0.5);
        for(unsigned j = 0; j <= heightSegments; ++j)
        {
            GLfloat y = static_cast<float>(-0.5 + static_cast<double>(j) / height_segments_f);
            buffer_float[0] = x;
            buffer_float[1] = y;
            buffer_float[2] = z;
            buffer_float[3] = static_cast<GLfloat>(static_cast<double>(i) / sides_f);
            buffer_float += 4;
        }
    }
}

void CylinderModel::fillInEBO(void *buffer) const
{
    GLuint *buffer_uint = reinterpret_cast<GLuint*>(buffer);
    for(unsigned i = 0; i < sides; ++i)
    {
        for(unsigned j = 0; j < heightSegments; ++j)
        {
            buffer_uint[0] = indexInVBO(i, j);
            buffer_uint[1] = indexInVBO((i + 1) % sides, j);
            buffer_uint[2] = indexInVBO((i + 1) % sides, j + 1);
            buffer_uint[3] = indexInVBO(i, j);
            buffer_uint[4] = indexInVBO((i + 1) % sides, j + 1);
            buffer_uint[5] = indexInVBO(i, j + 1);
            buffer_uint += 6;
        }
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
