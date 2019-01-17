#pragma once
#include "AbstractModelItem.h"

class SimpleCubeModel: public AbstractModelItem
{
public:
    SimpleCubeModel();
    virtual ~SimpleCubeModel() override;
    virtual GLsizeiptr getVBOSize() const override;
    virtual GLsizeiptr getEBOSize() const override;
    virtual void fillInVBO(void *buffer) const override;
    virtual void fillInEBO(void *buffer) const override;
    virtual const std::vector<GlVertexAttribInput> &getVertexAttributes() const override;

private:
    std::vector<GlVertexAttribInput> vertexAttributes;
};
