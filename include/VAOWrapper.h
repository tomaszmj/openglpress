#pragma once
#include <memory>
#include <GL/glew.h>

class AbstractModelItem;

class VAOWrapper
{
public:
    VAOWrapper(const std::unique_ptr<AbstractModelItem> model_item);
    ~VAOWrapper();
    void bind() const;
    void unbind() const;
    GLsizei getNumberOfVertices() const;

private:
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;
    GLsizei numberOfVertices;

    void fillInVBOAndEBO(const std::unique_ptr<AbstractModelItem> &model_item);
    void setUpVertexAttributes(const std::unique_ptr<AbstractModelItem> &model_item);
};
