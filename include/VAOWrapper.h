#pragma once
#include <GL/glew.h>

class AbstractModelItem;

class VAOWrapper
{
public:
    VAOWrapper(const AbstractModelItem &model_item);
    ~VAOWrapper();
    void bind() const;
    void unbind() const;
    GLsizei getNumberOfVertices() const;

private:
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;
    GLsizei numberOfVertices;

    void fillInVBOAndEBO(const AbstractModelItem &model_item);
    void setUpVertexAttributes(const AbstractModelItem &model_item);
};
