#include "../Header.h"

#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(std::vector<Vertex>& vertices)
{
    glCreateBuffers(1, &this->id);
    glNamedBufferData(this->id, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    this->sizePerData = sizeof(Vertex);
}

VertexBuffer::VertexBuffer(std::vector<float>& vertices)
{
    glCreateBuffers(1, &this->id);
    glNamedBufferData(this->id, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    this->sizePerData = 3 * sizeof(float);
}

VertexBuffer::VertexBuffer(const float* vertices, int count, int sizePerData)
{
    glCreateBuffers(1, &this->id);
    glNamedBufferData(this->id, count * sizeof(float), vertices, GL_STATIC_DRAW);

    this->sizePerData = sizePerData;
}

VertexBuffer::VertexBuffer(GLsizei sizePerData)
{
    glCreateBuffers(1, &this->id);
    glNamedBufferData(this->id, sizePerData, nullptr, GL_DYNAMIC_DRAW);

    this->sizePerData = sizePerData;
}

void VertexBuffer::BindToVAO(GLuint vaoID)
{
    glVertexArrayVertexBuffer(vaoID, 0, this->id, 0, this->sizePerData);
}

void VertexBuffer::UpdateData(GLintptr offset, GLsizeiptr size, const void* data)
{
    glNamedBufferSubData(this->id, offset, size, data);
}

void VertexBuffer::Delete()
{
    glDeleteBuffers(1, &this->id);
}
