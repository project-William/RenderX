#version 410

layout (location = 0) in vec3 VertexPos;
layout (location = 1) in vec2 TexCoords;
layout (location = 2) in vec3 Normals;

out vec2 texCoords;
out vec3 WorldPos;
out vec3 Normal;

uniform mat4 u_projection;
uniform mat4 u_view;
uniform mat4 u_model;

void main()
{
    texCoords = TexCoords;
    WorldPos = vec3(u_model * vec4(VertexPos, 1.0));
    Normal = mat3(u_model) * Normals;   

    gl_Position = u_projection*u_view*u_model*vec4(VertexPos, 1.0);
}