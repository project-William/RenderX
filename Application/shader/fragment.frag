#version 410

in VS_OUT{
	vec2 v_texCoords;
	vec3 v_normals;
	vec3 v_fragPos;
}fs_in;

out vec4 FragColor;

//light position
uniform vec3 u_lightPos;
//view position
uniform vec3 u_viewPos;
//uniform color
uniform vec3 u_color;

//textureSamples
uniform sampler2D u_albedoMap;

//is color texture
uniform bool u_isTexture;

vec4 BlinnPhong()
{
	vec4 result;
	//ambient
	vec3 ambient;
	vec3 texture_color;
	if(u_isTexture)
	{
		vec3 texture_color=texture(u_albedoMap,fs_in.v_texCoords).rgb;
		ambient=0.5f* texture_color;
	}
	else
	{
		ambient=0.5f* u_color;
	}
	//diffuse
	vec3 normals=normalize(fs_in.v_normals);
	vec3 lightDir=normalize(u_lightPos);
	float diff=max(dot(normals,lightDir),0.0f);
	vec3 diffuse;
    if(u_isTexture)
	{
		diffuse=diff* texture_color;
	}
	else
	{
		diffuse= diff* u_color;
	}
	//specular
	vec3 viewDir = normalize(u_viewPos - fs_in.v_fragPos);
    vec3 reflectDir = reflect(-lightDir, normals);
    float spec = 0.0;
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    spec = pow(max(dot(normals, halfwayDir), 0.0), 32.0);
    vec3 specular = vec3(0.3) * spec;

	result=vec4(ambient+diffuse+specular,1.0f);
	return result;
}


void main()
{
	FragColor= BlinnPhong();
}