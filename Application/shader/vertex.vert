#version 410

layout (location = 0) in vec3 a_VertexPos;
layout (location = 1) in vec2 a_TexCoords;
layout (location = 2) in vec3 a_Normals;

out VS_OUT {
	vec2 v_texCoords;
	vec3 v_normals;
	vec3 v_fragPos;
}vs_out;

uniform MatrixUniform
{
	mat4 projection;
	mat4 view;
	mat4 model;
}matrices;


uniform mat4 u_projection;
uniform mat4 u_view;
uniform mat4 u_model;


void main()
{
    vs_out.v_texCoords = a_TexCoords;
    vs_out.v_normals = mat3(u_model) * a_Normals;   
	vs_out.v_fragPos=vec3(u_model*vec4(a_VertexPos,1.0f));
    gl_Position = u_projection*u_view*u_model*vec4(vs_out.v_fragPos, 1.0);
}
