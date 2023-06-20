#version 460 core

// 座標
layout (location = 0) in vec3 position;
// 顏色
layout (location = 1) in vec3 color;
// 材質UV
layout (location = 2) in vec2 textureUV;

// 輸出給 Fragment 的顏色
out vec3 fragColor;

// 相機的投影矩陣
uniform mat4 cameraMatrix;

void main()
{
    gl_Position = cameraMatrix * vec4(position, 1.0);

    fragColor = color;
}
