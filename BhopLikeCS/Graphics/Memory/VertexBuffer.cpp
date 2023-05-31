#include "../Header.h"

#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(std::vector<Vertex>& vertices)
{
    glCreateBuffers(1, &this->id);
    glNamedBufferData(this->id, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    this->size = sizeof(Vertex);
}

VertexBuffer::VertexBuffer(GLsizei size)
{
    glCreateBuffers(1, &this->id);
    glNamedBufferData(this->id, size, nullptr, GL_DYNAMIC_DRAW);
    this->size = size;
}

void VertexBuffer::BindToVAO(GLuint vaoID)
{
    glVertexArrayVertexBuffer(vaoID, 0, this->id, 0, this->size);
}

void VertexBuffer::UpdateData(GLintptr offset, GLsizeiptr size, const void* data)
{
    glNamedBufferSubData(this->id, offset, size, data);
}

void VertexBuffer::Delete()
{
    glDeleteBuffers(1, &this->id);
}
