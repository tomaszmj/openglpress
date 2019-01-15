#include "CylinderModel.h"
#include <cmath>

CylinderModel::CylinderModel(unsigned sides, unsigned radius_segments, unsigned height_segments)
    : vertexAttributes({
        AbstractModelItem::GlVertexAttribInput{3, GL_FLOAT, 3*sizeof(GLfloat)}, // position
    }), sides(sides), radiusSegments(radius_segments), heightSegments(height_segments)
{}

CylinderModel::~CylinderModel() {}

GLsizeiptr CylinderModel::getVBOSize() const
{
    return 1*sizeof(GLfloat);
}

GLsizeiptr CylinderModel::getEBOSize() const
{
    return 1*sizeof(GLuint);
}

void CylinderModel::fillInVBO(void *buffer) const
{
}

void CylinderModel::fillInEBO(void *buffer) const
{
}

const std::vector<AbstractModelItem::GlVertexAttribInput> &CylinderModel::getVertexAttributes() const
{
    return vertexAttributes;
}
