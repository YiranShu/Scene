#version 330 core
in vec3 myColor;
in vec2 TexCoord;

out vec4 color;

uniform sampler2D myTexture;

void main()
{
	color = texture(myTexture, TexCoord);
}