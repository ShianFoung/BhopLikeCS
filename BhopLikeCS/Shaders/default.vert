#version 460 core

layout (location = 0) in vec3 position;

uniform mat4 cameraMatrix;

void main()
{
    gl_Position = camera * vec4(position, 1.0);
}
