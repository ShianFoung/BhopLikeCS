#version 460 core

// 輸出色彩
out vec4 outFragColor;

// 由 OpenGL 傳入的材質資料
uniform sampler2D textureImage;

// 從 Vertex 傳入的顏色
in vec3 fragColor;

void main()
{
	outFragColor = vec4(fragColor, 1.0);
}
