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
    virtual GLsizeiptr getVBOSize() = 0;
    virtual GLsizeiptr getEBOSize() = 0;
    virtual void fillInVBO(void *buffer) = 0;
    virtual void fillInEBO(void *buffer) = 0;
    virtual const std::vector<GlVertexAttribInput> &getVertexAttributes() = 0;
    virtual GLsizei getVertexAttributesStride();
};
