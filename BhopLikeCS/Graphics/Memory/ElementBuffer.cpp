#include "../Header.h"

#include "ElementBuffer.h"

ElementBuffer::ElementBuffer(std::vector<int>& indices)
{
    glCreateBuffers(1, &this->id);
    glNamedBufferData(this->id, indices.size() * sizeof(int), indices.data(), GL_STATIC_DRAW);
}

ElementBuffer::ElementBuffer(const int* indices, int count)
{
    glCreateBuffers(1, &this->id);
    glNamedBufferData(this->id, count * sizeof(int), indices, GL_STATIC_DRAW);
}

void ElementBuffer::BindToVAO(GLuint vaoID)
{
    glVertexArrayElementBuffer(vaoID, this->id);
}

void ElementBuffer::Delete()
{
    glDeleteBuffers(1, &this->id);
}
