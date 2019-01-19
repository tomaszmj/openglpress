#pragma once
#include "AbstractModelItem.h"
#include <glm/glm.hpp>

class TexturedCylinderModel: public AbstractModelItem
{
public:
    TexturedCylinderModel(unsigned sides, unsigned height_segments);
    virtual ~TexturedCylinderModel() override;
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
    GLfloat *fillInVBOCurvedSurface(GLfloat *buffer) const;
    GLfloat *fillInVBOBases(GLfloat *buffer) const;
    GLuint *fillInEBOCurvedSurface(GLuint *buffer) const;
    GLuint *fillInEBOBases(GLuint *buffer) const;
    GLfloat *fillOneVertexInVBO(GLfloat *buffer, const glm::vec3 &position,
                                const glm::vec3 &normal_vector, const glm::vec2 &texture) const;
};
