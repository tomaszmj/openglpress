#pragma once
#include <vector>
#include <GL/glew.h>

class AbstractModelItem
{
public:
    struct GlVertexAttribInput
    {
        GLint numberOfParameters;
        GLenum type;
        GLsizei sizeInBytes;
    };

    virtual ~AbstractModelItem();
    virtual GLsizeiptr getVBOSize() const = 0;
    virtual GLsizeiptr getEBOSize() const = 0;
    virtual void fillInVBO(void *buffer) const = 0;
    virtual void fillInEBO(void *buffer) const = 0;
    virtual const std::vector<GlVertexAttribInput> &getVertexAttributes() const = 0;
    virtual GLsizei getVertexAttributesStride() const;
};
