#include "AbstractModelItem.h"

AbstractModelItem::~AbstractModelItem() {}

GLsizei AbstractModelItem::getVertexAttributesStride()
{
    const auto attributes = getVertexAttributes();
    GLsizei retval = 0;
    for(const auto &attribute : attributes)
        retval += static_cast<GLsizei>(attribute.sizeInBytes);
    return retval;
}
