#version 460 core

// ��X��m
out vec4 outFragColor;

// �� OpenGL �ǤJ��������
uniform sampler2D textureImage;

// �q Vertex �ǤJ���C��
in vec3 fragColor;

void main()
{
	outFragColor = vec4(fragColor, 1.0);
}
