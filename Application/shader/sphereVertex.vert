#version 410

layout (location = 0) in vec3 VertexPos;
layout (location = 1) in vec2 TexCoords;
layout (location = 2) in vec3 Normals;

out vec2 texCoords;
out vec3 normals;
out vec3 fragPos;


uniform mat4 u_projection;
uniform mat4 u_view;
uniform mat4 u_model;


void main()
{
    texCoords = TexCoords;
    normals = mat3(u_model) * Normals;   
	fragPos=vec3(u_model*vec4(VertexPos,1.0f));
    gl_Position = u_projection*u_view*u_model*vec4(VertexPos, 1.0);
}