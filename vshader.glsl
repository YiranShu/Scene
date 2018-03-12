#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;

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