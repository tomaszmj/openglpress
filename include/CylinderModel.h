#pragma once
#include "AbstractModelItem.h"

class CylinderModel: public AbstractModelItem
{
public:
    CylinderModel(unsigned sides, unsigned radius_segments, unsigned height_segments);
    virtual ~CylinderModel() override;
    virtual GLsizeiptr getVBOSize() const override;
    virtual GLsizeiptr getEBOSize() const override;
    virtual void fillInVBO(void *buffer) const override;
    virtual void fillInEBO(void *buffer) const override;
    virtual const std::vector<GlVertexAttribInput> &getVertexAttributes() const override;

private:
    std::vector<GlVertexAttribInput> vertexAttributes;
    unsigned sides;
    unsigned radiusSegments;
    unsigned heightSegments;

    GLuint indexInVBO(unsigned side_index, unsigned height_index) const;
};
