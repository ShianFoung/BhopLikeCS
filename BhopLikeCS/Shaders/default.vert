#version 460 core

layout (location = 0) in vec3 position;

uniform mat4 cameraMatrix;

void main()
{
    // gl_Position = cameraMatrix * vec4(position.x, position.z, -position.y, 1.0);
    gl_Position = cameraMatrix * vec4(position, 1.0);
}
