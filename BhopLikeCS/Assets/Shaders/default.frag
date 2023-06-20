#version 460 core

// ��X��m
out vec4 outFragColor;

// �� OpenGL �ǤJ��������
uniform sampler2D textureImage;

// �q Vertex �ǤJ������
in vec2 fragTextureCoords;

void main()
{
	outFragColor = texture(textureImage, fragTextureCoords);
}
