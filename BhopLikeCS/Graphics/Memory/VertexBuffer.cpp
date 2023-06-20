#include "../Header.h"

#include "VertexBuffer.h"

VertexBuffer::VertexBuffer()
{

}

VertexBuffer::VertexBuffer(std::vector<Vertex>& vertices)
{
    glCreateBuffers(1, &this->id);
    glNamedBufferData(this->id, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    this->sizePerVertex = sizeof(Vertex);
}

VertexBuffer::VertexBuffer(std::vector<float>& vertices)
{
    glCreateBuffers(1, &this->id);
    glNamedBufferData(this->id, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    this->sizePerVertex = 3 * sizeof(float);
}

VertexBuffer::VertexBuffer(std::vector<float>& vertices, GLsizei sizePerVertex)
{
    glCreateBuffers(1, &this->id);
    glNamedBufferData(this->id, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    this->sizePerVertex = sizePerVertex;
}

VertexBuffer::VertexBuffer(const float* vertices, int count)
{
    glCreateBuffers(1, &this->id);
    glNamedBufferData(this->id, count * sizeof(float), vertices, GL_STATIC_DRAW);

    this->sizePerVertex = 3 * sizeof(float);
}

VertexBuffer::VertexBuffer(const float* vertices, int count, GLsizei sizePerVertex)
{
    glCreateBuffers(1, &this->id);
    glNamedBufferData(this->id, count * sizeof(float), vertices, GL_STATIC_DRAW);

    this->sizePerVertex = sizePerVertex;
}

VertexBuffer::VertexBuffer(GLsizei totalSize)
{
    glCreateBuffers(1, &this->id);
    glNamedBufferData(this->id, totalSize, nullptr, GL_DYNAMIC_DRAW);
}

void VertexBuffer::BindToVAO(GLuint vaoID)
{
    glVertexArrayVertexBuffer(vaoID, 0, this->id, 0, this->sizePerVertex);
}

void VertexBuffer::UpdateData(GLintptr offset, GLsizeiptr size, const void* data)
{
    glNamedBufferSubData(this->id, offset, size, data);
}

void VertexBuffer::Delete()
{
    glDeleteBuffers(1, &this->id);
}
