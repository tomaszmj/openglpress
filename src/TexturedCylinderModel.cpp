#include <TexturedCylinderModel.h>
#include <cmath>

const double PI = std::atan(1)*4;

TexturedCylinderModel::TexturedCylinderModel(unsigned sides, unsigned height_segments)
    : vertexAttributes({
        AbstractModelItem::GlVertexAttribInput{3, GL_FLOAT, 3*sizeof(GLfloat)}, // position
        AbstractModelItem::GlVertexAttribInput{3, GL_FLOAT, 3*sizeof(GLfloat)}, // normal vector
        AbstractModelItem::GlVertexAttribInput{2, GL_FLOAT, 2*sizeof(GLfloat)}, // texture coordinates
    }), sides(sides), heightSegments(height_segments)
{}

TexturedCylinderModel::~TexturedCylinderModel() {}

GLsizeiptr TexturedCylinderModel::getVBOSize() const
{
    return (sides * (heightSegments + 1) + sides * 2 + 2) * 8 * sizeof(GLfloat);
}

GLsizeiptr TexturedCylinderModel::getEBOSize() const
{
    return (sides * heightSegments * 2) * 3 * sizeof(GLuint);
}

void TexturedCylinderModel::fillInVBO(void *buffer) const
{
    GLfloat *buffer_float = reinterpret_cast<GLfloat*>(buffer);
    buffer_float = fillInVBOCurvedSurface(buffer_float);
    fillInVBOBases(buffer_float);
}

void TexturedCylinderModel::fillInEBO(void *buffer) const
{
    GLuint *buffer_uint = reinterpret_cast<GLuint*>(buffer);
    buffer_uint = fillInEBOCurvedSurface(buffer_uint);
    fillInEBOBases(buffer_uint);
}

const std::vector<AbstractModelItem::GlVertexAttribInput> &TexturedCylinderModel::getVertexAttributes() const
{
    return vertexAttributes;
}

GLuint TexturedCylinderModel::indexInVBO(unsigned side_index, unsigned height_index) const
{
    return side_index * (heightSegments + 1) + height_index;
}

GLfloat *TexturedCylinderModel::fillInVBOCurvedSurface(GLfloat *buffer) const
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texture_coords;
    normal.y = 0.0;
    for(unsigned i = 0; i < sides; ++i)
    {
        double circumference_fraction = static_cast<double>(i) / static_cast<double>(sides);
        double alpha = circumference_fraction * 2.0 * PI;
        double sin = std::sin(alpha);
        double cos = std::cos(alpha);
        position.x = static_cast<GLfloat>(cos * 0.5);
        position.z = static_cast<GLfloat>(sin * 0.5);
        normal.x = position.x;
        normal.z = position.z;
        texture_coords.x = static_cast<GLfloat>(std::fabs(1.0 - circumference_fraction * 2.0)); // wrap texture twice to avoid glitches
        for(unsigned j = 0; j <= heightSegments; ++j)
        {
            double height_fraction = static_cast<double>(j) / static_cast<double>(heightSegments);
            texture_coords.y = static_cast<GLfloat>(height_fraction);
            position.y = static_cast<GLfloat>(-0.5 + height_fraction);
            buffer = fillOneVertexInVBO(buffer, position, normal, texture_coords);
        }
    }
    buffer = fillOneVertexInVBO(buffer, glm::vec3(0.0, -0.5, 0.0), glm::vec3(0.0, -1.0, 0.0), glm::vec2(0.0, 0.0));
    buffer = fillOneVertexInVBO(buffer, glm::vec3(0.0, 0.5, 0.0), glm::vec3(0.0, 1.0, 0.0), glm::vec2(0.0, 0.0));
    return buffer;
}

GLfloat *TexturedCylinderModel::fillInVBOBases(GLfloat *buffer) const
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texture_coords;
    normal.x = normal.y = 0.0f;
    for(unsigned i = 0; i < sides; ++i)
    {
        double circumference_fraction = static_cast<double>(i) / static_cast<double>(sides);
        double alpha = circumference_fraction * 2.0 * PI;
        double sin = std::sin(alpha);
        double cos = std::cos(alpha);
        position.x = static_cast<GLfloat>(cos * 0.5);
        position.z = static_cast<GLfloat>(sin * 0.5);
        texture_coords.x = static_cast<GLfloat>((cos + 1.0)/2.0);
        texture_coords.y = static_cast<GLfloat>((sin + 1.0)/2.0);
        for(GLfloat normal_y = -1.0f; normal_y < 1.1f; normal_y += 2.0f)
        {
            normal.y = normal_y;
            position.y = normal_y / 2.0f;
            buffer = fillOneVertexInVBO(buffer, position, normal, texture_coords);
        }
    }
    return buffer;
}

GLuint *TexturedCylinderModel::fillInEBOCurvedSurface(GLuint *buffer) const
{
    for(unsigned i = 0; i < sides; ++i)
    {
        for(unsigned j = 0; j < heightSegments; ++j)
        {
            buffer[0] = indexInVBO(i, j);
            buffer[1] = indexInVBO((i + 1) % sides, j);
            buffer[2] = indexInVBO((i + 1) % sides, j + 1);
            buffer[3] = indexInVBO(i, j);
            buffer[4] = indexInVBO((i + 1) % sides, j + 1);
            buffer[5] = indexInVBO(i, j + 1);
            buffer += 6;
        }
    }
    return buffer;
}

GLuint *TexturedCylinderModel::fillInEBOBases(GLuint *buffer) const
{
//    GLuint lower_base_begin_in_vbo = sides * (heightSegments + 1);
//    GLuint upper_base_begin_in_vbo = lower_base_begin_in_vbo + sides;
//    for(unsigned i = 0; i < sides; ++i)
//    {
//        // lower base:
//        buffer_uint[0] = lower_base_begin_in_vbo;
//        buffer_uint[1] = lower_base_center_in_vbo;
//        buffer_uint[2] = indexInVBO((i + 1) % sides, 0);
//        // upper base:
//        buffer_uint[3] = indexInVBO(i, heightSegments);
//        buffer_uint[4] = lower_base_center_in_vbo + 1;
//        buffer_uint[5] = indexInVBO((i + 1) % sides, heightSegments);
//        buffer_uint += 6;
//    }
}

GLfloat *TexturedCylinderModel::fillOneVertexInVBO(GLfloat *buffer, const glm::vec3 &position, const glm::vec3 &normal_vector, const glm::vec2 &texture) const
{
    buffer[0] = position.x;
    buffer[1] = position.y;
    buffer[2] = position.z;
    buffer[3] = normal_vector.x;
    buffer[4] = normal_vector.y;
    buffer[5] = normal_vector.z;
    buffer[6] = texture.x;
    buffer[7] = texture.y;
    buffer += 8;
    return buffer;
}
