#include "../Header.h"

#include "VertexBuffer.h"
#include "ElementBuffer.h"

#include "VertexArray.h"

VertexArray::VertexArray()
{
    glCreateVertexArrays(1, &this->id);
}

void VertexArray::AddAttribute(GLuint attributeIndex, GLuint dataCount, GLenum type, GLboolean normalized, GLuint offset)
{
    glEnableVertexArrayAttrib(this->id, attributeIndex);
    glVertexArrayAttribBinding(this->id, attributeIndex, 0);
    glVertexArrayAttribFormat(this->id, attributeIndex, dataCount, type, normalized, offset);
}

void VertexArray::BindToBuffers(VertexBuffer vbo, ElementBuffer ebo)
{
    vbo.BindToVAO(this->id);
    ebo.BindToVAO(this->id);
}

void VertexArray::Delete()
{
    glDeleteVertexArrays(1, &this->id);
}
