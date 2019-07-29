#version 410

in vec3 TexCoords;

out vec4 FragColor;
uniform samplerCube u_Skybox;

void main()
{
	FragColor=texture(u_Skybox,TexCoords);
}