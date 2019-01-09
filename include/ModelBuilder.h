#pragma once
#include <AbstractModelItem.h>
#include <memory>

class ModelBuilder
{
public:
    ModelBuilder();
    ~ModelBuilder();
    void registerItem(std::unique_ptr<AbstractModelItem> item);
    void generateOpenglBuffers();
    const std::vector<GLuint> &getVAOs();

private:
    std::vector<std::unique_ptr<AbstractModelItem>> registeredModels;
    std::vector<GLuint> VAOs;
    std::vector<GLuint> VBOs;
    std::vector<GLuint> EBOs;
};
