#version 130
in vec3 myColor;
in vec2 TexCoord;

out vec4 color;

uniform sampler2D myTexture;

void main()
{
	color = texture(myTexture, TexCoord);
}
