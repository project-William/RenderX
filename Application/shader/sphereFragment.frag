#version 410


in VS_OUT{
	vec2 v_texCoords;
	vec3 v_normals;
	vec3 v_fragPos;
}fs_in;

out vec4 FragColor;

uniform vec4 u_color;

uniform vec3 u_viewPos;
uniform vec3 u_lightPos;
uniform vec3 u_lightColor;
uniform float u_Shineness;

uniform bool u_open_phong;
uniform bool u_blinn_phong;
uniform float u_gamma_value;

void main()
{
	float gamma=u_gamma_value;
	vec4 result=u_color;
    if(u_open_phong)
	{
		//change the y-axis of light position
		vec3 lightPos=vec3(u_lightPos.x,-u_lightPos.y,u_lightPos.z);
 
		float ambient_strength=0.5f;
		vec3 ambient=ambient_strength*u_lightColor;

		vec3 norm = normalize(fs_in.v_normals);
		vec3 lightDir = normalize(lightPos - fs_in.v_fragPos);
		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = diff * u_lightColor;
		
		// specular
		float specular_Strength = 0.5;
		vec3 viewDir = normalize(u_viewPos - fs_in.v_fragPos);
		vec3 reflectDir = reflect(-lightDir, norm);  
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Shineness);
		vec3 specular = specular_Strength * spec * u_lightColor;  

		vec4 result=(vec4(ambient,1.0)+vec4(diffuse,1.0f)+vec4(specular,1.0f))*u_color;
		
		result.rgb=pow(result.rgb,vec3(1.0f/u_gamma_value));
		FragColor=result;
	}
	else if(u_blinn_phong)
	{
		vec3 lightPos=vec3(u_lightPos.x,-u_lightPos.y,u_lightPos.z);
 
		float ambient_strength=0.5f;
		vec3 ambient=ambient_strength*u_lightColor;

		vec3 norm = normalize(fs_in.v_normals);
		vec3 lightDir = normalize(lightPos - fs_in.v_fragPos);
		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = diff * u_lightColor;
		
		// specular
		float specular_Strength = 0.5;
		vec3 viewDir = normalize(u_viewPos - fs_in.v_fragPos);
		vec3 halfwayDir=normalize(lightDir+viewDir);
		vec3 reflectDir = reflect(-lightDir, norm);  
	
		float spec = pow(max(dot(norm, halfwayDir), 0.0), u_Shineness);
		vec3 specular = specular_Strength * spec * u_lightColor;  

		vec4 result=(vec4(ambient,1.0)+vec4(diffuse,1.0f)+vec4(specular,1.0f))*u_color;
		result=pow(result,vec4(1.0f/u_gamma_value));
		FragColor=result;
	}
}