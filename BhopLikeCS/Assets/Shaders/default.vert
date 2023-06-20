#version 460 core

// �y��
layout (location = 0) in vec3 position;
// �C��
layout (location = 1) in vec3 color;
// ����UV
layout (location = 2) in vec2 textureUV;

// ��X�� Fragment ������
out vec2 fragTextureCoords;

// �۾�����v�x�}
uniform mat4 cameraMatrix;

void main()
{
    gl_Position = cameraMatrix * vec4(position, 1.0);

    fragTextureCoords = textureUV;
}
