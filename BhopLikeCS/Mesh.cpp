#include "Header.h"

#include "Mesh.h"

#include "Texture.h"

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<int>& indices)
{
    this->vertices = vertices;
    this->indices = indices;
}
