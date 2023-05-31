#include "../Header.h"

#include "ElementBuffer.h"

ElementBuffer::ElementBuffer(std::vector<GLuint>& indices)
{
    glCreateBuffers(1, &this->id);
    glNamedBufferData(this->id, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
}

void ElementBuffer::BindToVAO(GLuint vaoID)
{
    glVertexArrayElementBuffer(vaoID, this->id);
}

void ElementBuffer::Delete()
{
    glDeleteBuffers(1, &this->id);
}
