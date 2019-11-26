#version 410

layout (location = 0) in vec3 a_VertexPos;
layout (location = 1) in vec2 a_TexCoord;
layout (location = 2) in vec3 a_Normal;

uniform mat4 view;
uniform mat4 model;
uniform mat4 projection;

out vec2 tex;

void main()
{
	tex=a_TexCoord;
	gl_Position = projection * view * model*vec4(a_VertexPos,1.0f);
}