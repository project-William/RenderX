#version 410 

layout (location = 0) in vec3 VertexPos;
layout (location = 1) in vec2 TexCoords;

out vec2 texCoords;

uniform mat4 u_projection;
uniform mat4 u_view;
uniform mat4 u_model;

void main()
{
	texCoords=TexCoords;
	gl_Position=vec4(VertexPos,1.0f);
}