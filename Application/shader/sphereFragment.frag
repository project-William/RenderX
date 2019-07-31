#version 410
in vec2 texcoords;
in vec3 normals;
in vec3 fragPos;

out vec4 FragColor;

uniform vec4 u_color;

uniform vec3 u_viewPos;
uniform vec3 u_lightPos;
uniform vec3 u_lightColor;

uniform float u_Shineness;

void main()
{
	//change the y-axis of light position
	vec3 lightPos=vec3(u_lightPos.x,-u_lightPos.y,u_lightPos.z);
 
	float ambient_strength=0.5f;
	vec3 ambient=ambient_strength*u_lightColor;

	vec3 norm = normalize(normals);
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * u_lightColor;
    
    // specular
    float specular_Strength = 0.5;
    vec3 viewDir = normalize(u_viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Shineness);
    vec3 specular = specular_Strength * spec * u_lightColor;  

	vec4 result=(vec4(ambient,1.0)+vec4(diffuse,1.0f)+vec4(specular,1.0f))*u_color;

	FragColor=result;
}