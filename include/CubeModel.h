#pragma once
#include "AbstractModelItem.h"

class CubeModel: public AbstractModelItem
{
public:
    CubeModel();
    virtual ~CubeModel() override;
    virtual GLsizeiptr getVBOSize() const override;
    virtual GLsizeiptr getEBOSize() const override;
    virtual void fillInVBO(void *buffer) const override;
    virtual void fillInEBO(void *buffer) const override;
    virtual const std::vector<GlVertexAttribInput> &getVertexAttributes() const override;

private:
    std::vector<GlVertexAttribInput> vertexAttributes;
};
