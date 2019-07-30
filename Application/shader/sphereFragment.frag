#version 410
in vec2 texcoords;
in vec3 normals;
in vec3 fragPos;

out vec4 FragColor;

uniform vec4 u_color;

uniform vec3 u_viewPos;
uniform vec3 u_lightPos;
uniform vec3 u_lightColor;


void main()
{
    float ambient_strength=0.5f;
	vec3 ambient=ambient_strength*u_lightColor;

	vec3 norm = normalize(normals);
    vec3 lightDir = normalize(u_lightPos - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * u_lightColor;
    
    // specular
    //float specularStrength = 0.5;
    //vec3 viewDir = normalize(viewPos - FragPos);
    //vec3 reflectDir = reflect(-lightDir, norm);  
    //float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    //vec3 specular = specularStrength * spec * lightColor;  

	vec4 result=(vec4(ambient,1.0)+vec4(diffuse,1.0f))*u_color;

	FragColor=result;
}