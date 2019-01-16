#pragma once
#include "AbstractModelItem.h"

class CylinderModel: public AbstractModelItem
{
public:
    CylinderModel(unsigned sides, unsigned height_segments);
    virtual ~CylinderModel() override;
    virtual GLsizeiptr getVBOSize() const override;
    virtual GLsizeiptr getEBOSize() const override;
    virtual void fillInVBO(void *buffer) const override;
    virtual void fillInEBO(void *buffer) const override;
    virtual const std::vector<GlVertexAttribInput> &getVertexAttributes() const override;

private:
    std::vector<GlVertexAttribInput> vertexAttributes;
    unsigned sides;
    unsigned heightSegments;

    GLuint indexInVBO(unsigned side_index, unsigned height_index) const;
    GLfloat *fillOneVertexInVBO(GLfloat *buffer, GLfloat x, GLfloat y, GLfloat z, GLfloat tmp_parameter) const;
};
