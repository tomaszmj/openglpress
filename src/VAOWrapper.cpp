#include <VAOWrapper.h>
#include <AbstractModelItem.h>
#include <algorithm>

VAOWrapper::VAOWrapper(const std::unique_ptr<AbstractModelItem> model_item)
    : VAO(0), VBO(0), EBO(0), numberOfVertices(static_cast<GLuint>(model_item->getEBOSize()) / sizeof(GLuint))
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    bind();
    fillInVBOAndEBO(model_item);
    setUpVertexAttributes(model_item);
    unbind();
}

VAOWrapper::~VAOWrapper()
{
    if(VAO)
        glDeleteVertexArrays(1, &VAO);
    if(VBO)
        glDeleteBuffers(1, &VBO);
    if(EBO)
        glDeleteBuffers(1, &EBO);
}

void VAOWrapper::bind() const
{
    glBindVertexArray(VAO);
}

void VAOWrapper::unbind() const
{
    glBindVertexArray(0);
}

GLsizei VAOWrapper::getNumberOfVertices()
{
    return numberOfVertices;
}

void VAOWrapper::fillInVBOAndEBO(const std::unique_ptr<AbstractModelItem> &model_item)
{
    std::vector<char> buffer(static_cast<size_t>(std::max(model_item->getVBOSize(), model_item->getEBOSize())));
    model_item->fillInVBO(buffer.data());
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, model_item->getVBOSize(), buffer.data(), GL_STATIC_DRAW);
    model_item->fillInEBO(buffer.data());
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, model_item->getEBOSize(), buffer.data(), GL_STATIC_DRAW);
}

void VAOWrapper::setUpVertexAttributes(const std::unique_ptr<AbstractModelItem> &model_item)
{
    const auto stride = model_item->getVertexAttributesStride();
    GLuint index = 0;
    GLsizei offset = 0;
    for(AbstractModelItem::GlVertexAttribInput attrib_input : model_item->getVertexAttributes())
    {
        glVertexAttribPointer(index, attrib_input.numberOfParameters, attrib_input.type,
                              GL_FALSE, stride, reinterpret_cast<GLvoid*>(offset));
        glEnableVertexAttribArray(index);
        offset += attrib_input.sizeInBytes;
        ++index;
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
