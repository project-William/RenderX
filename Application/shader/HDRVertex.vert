#version 410 
layout (location = 0) in vec3 a_VertexPos;
layout (location = 1) in vec2 a_TexCoords;

out vec2 TexCoords;

void main()
{
    TexCoords = a_TexCoords;
    gl_Position = vec4(a_VertexPos, 1.0);
}