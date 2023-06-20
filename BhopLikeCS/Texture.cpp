#include "../Header.h"

#include "Texture.h"

Texture::Texture(const std::string& imagePath)
{
    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);
    uint8_t* bytes = stbi_load(imagePath.c_str(), &width, &height, &channels, 0);

    glCreateTextures(GL_TEXTURE_2D, 1, &this->id);

    glTextureParameteri(this->id, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTextureParameteri(this->id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTextureParameteri(this->id, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(this->id, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTextureStorage2D(this->id, 1, channels == 3 ? GL_RGB8 : GL_RGBA8, width, height);
    glTextureSubImage2D(this->id, 0, 0, 0, width, height, channels == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, bytes);

    stbi_image_free(bytes);
}

void Texture::Activate(GLuint unit)
{
    glBindTextureUnit(unit, this->id);
}

void Texture::Delete()
{
    glDeleteTextures(1, &this->id);
}
