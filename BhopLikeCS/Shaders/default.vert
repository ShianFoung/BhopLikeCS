#version 330 core

layout (location = 0) in vec3 position;

// 3D®y¼Ð§ë¼v¯x°}
//uniform mat4 model;
//uniform mat4 view;
//uniform mat4 projection;
uniform mat4 camera;

void main()
{
    //gl_Position = projection * view * model * vec4(position, 1.0);
    gl_Position = camera * vec4(position, 1.0);
}
