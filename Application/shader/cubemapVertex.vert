#version 410 

layout (location=0) in vec3 VertexPos;

out vec3 TexCoords;

uniform mat4 u_projection;
uniform mat4 u_view;

void main()
{
	TexCoords=VertexPos;
	gl_Position=u_projection*u_view*vec4(VertexPos.x,-VertexPos.y,VertexPos.z,1.0f);
}