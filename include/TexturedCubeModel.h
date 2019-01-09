#pragma once
#include "AbstractModelItem.h"

class TexturedCubeModel: public AbstractModelItem
{
public:
    TexturedCubeModel();
    virtual ~TexturedCubeModel();
    virtual GLsizeiptr getVBOSize();
    virtual GLsizeiptr getEBOSize();
    virtual void fillInVBO(void *buffer);
    virtual void fillInEBO(void *buffer);
    virtual const std::vector<GlVertexAttribInput> &getVertexAttributes();

private:
    std::vector<GlVertexAttribInput> vertexAttributes;
};
