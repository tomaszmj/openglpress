#pragma once
#include <vector>
#include <GL/glew.h>

class AbstractModelItem
{
    struct GlVertexAttribInput
    {
        GLint size;
        GLenum type;
    };
public:
    virtual size_t getVBOSize() = 0;
    virtual size_t getEBOSize() = 0;
    virtual void fillInVBO(char *buffer) = 0;
    virtual void fillInEBO(char *buffer) = 0;
    virtual const std::vector<GlVertexAttribInput> &getVertexAttributes() = 0;

    virtual GLsizei getVertexAttributesStride()
    {
        const auto attributes = getVertexAttributes();
        GLsizei retval = 0;
        for(const auto &attribute : attributes)
            retval += static_cast<GLsizei>(attribute.size);
        return retval;
    }
};
