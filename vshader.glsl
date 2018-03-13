#version 130
in vec3 position;
in vec3 color;
in vec2 texCoord;

out vec3 myColor;
out vec2 TexCoord;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

void main()
{
	gl_Position = Projection * View *  Model * vec4(position, 1.0f);
	myColor = color;
	TexCoord = vec2(texCoord.x, 1.0 - texCoord.y);
}
