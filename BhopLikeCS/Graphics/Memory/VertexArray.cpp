#include "../Header.h"

#include "VertexArray.h"

VertexArray::VertexArray()
{
    glCreateVertexArrays(1, &this->id);
}

void VertexArray::AddAttribute(GLuint attributeIndex, GLuint dataCount, GLenum type, GLuint offset)
{
    glEnableVertexArrayAttrib(this->id, attributeIndex);
    glVertexArrayAttribBinding(this->id, attributeIndex, 0);
    glVertexArrayAttribFormat(this->id, attributeIndex, dataCount, type, GL_FALSE, offset);
}

void VertexArray::AddAttributeInt(GLuint attributeIndex, GLuint dataCount, GLenum type, GLuint offset)
{
    glEnableVertexArrayAttrib(this->id, attributeIndex);
    glVertexArrayAttribBinding(this->id, attributeIndex, 0);
    glVertexArrayAttribIFormat(this->id, attributeIndex, dataCount, type, offset);
}

void VertexArray::BindBuffer(VertexBuffer& vbo)
{
    vbo.BindToVAO(this->id);
}


void VertexArray::BindBuffers(VertexBuffer& vbo, ElementBuffer& ebo)
{
    vbo.BindToVAO(this->id);
    ebo.BindToVAO(this->id);
}

void VertexArray::Bind()
{
    glBindVertexArray(this->id);
}

void VertexArray::Unbind()
{
    glBindVertexArray(0);
}

void VertexArray::Delete()
{
    glDeleteVertexArrays(1, &this->id);
}
