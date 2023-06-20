#version 460 core

// 輸出色彩
out vec4 outFragColor;

// 由 OpenGL 傳入的材質資料
uniform sampler2D textureImage;

// 從 Vertex 傳入的材質
in vec2 fragTextureCoords;

void main()
{
	outFragColor = texture(textureImage, fragTextureCoords);
}
