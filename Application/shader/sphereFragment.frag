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

//material parameters lighting PBR
uniform vec3 u_albedo;
uniform float u_metallic;
uniform float u_roughness;
uniform float u_ao;

// material parameters texture PBR
uniform sampler2D u_albedoMap;
uniform sampler2D u_normalMap;
uniform sampler2D u_metallicMap;
uniform sampler2D u_roughnessMap;
uniform sampler2D u_aoMap;


uniform bool u_light_pbr;
uniform bool u_texture_pbr;

const float PI = 3.14159265359;
vec3 getNormalFromMap()
{
    vec3 tangentNormal = texture(u_normalMap, fs_in.v_texCoords).xyz * 2.0 - 1.0;

    vec3 Q1  = dFdx(fs_in.v_fragPos);
    vec3 Q2  = dFdy(fs_in.v_fragPos);
    vec2 st1 = dFdx(fs_in.v_texCoords);
    vec2 st2 = dFdy(fs_in.v_texCoords);

    vec3 N   = normalize(fs_in.v_normals);
    vec3 T  = normalize(Q1*st2.t - Q2*st1.t);
    vec3 B  = -normalize(cross(N, T));
    mat3 TBN = mat3(T, B, N);

    return normalize(TBN * tangentNormal);
}
// ----------------------------------------------------------------------------
float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a = roughness*roughness;
    float a2 = a*a;
    float NdotH = max(dot(N, H), 0.0f);
    float NdotH2 = NdotH*NdotH;

    float nom   = a2;
    float denom = (NdotH2 * (a2 - 1.0f) + 1.0f);
    denom = PI * denom * denom;

    return nom / max(denom, 0.001); // prevent divide by zero for roughness=0.0 and NdotH=1.0
}
// ----------------------------------------------------------------------------
float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0f);
    float k = (r*r) / 8.0f;

    float nom   = NdotV;
    float denom = NdotV * (1.0f - k) + k;

    return nom / denom;
}
// ----------------------------------------------------------------------------
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2 = GeometrySchlickGGX(NdotV, roughness);
    float ggx1 = GeometrySchlickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}
// ----------------------------------------------------------------------------
vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}
// ----------------------------------------------------------------------------

void main()
{
	vec4 result=u_color;
	vec3 lightPos=vec3(u_lightPos.x,-u_lightPos.y,u_lightPos.z);
    
	//if(u_open_phong)
	//{
	//	//change the y-axis of light position
 	//
	//	float ambient_strength=0.5f;
	//	vec3 ambient=ambient_strength*u_lightColor;
	//
	//	vec3 norm = normalize(fs_in.v_normals);
	//	vec3 lightDir = normalize(lightPos - fs_in.v_fragPos);
	//	float diff = max(dot(norm, lightDir), 0.0);
	//	vec3 diffuse = diff * u_lightColor;
	//	
	//	// specular
	//	float specular_Strength = 0.5;
	//	vec3 viewDir = normalize(u_viewPos - fs_in.v_fragPos);
	//	vec3 reflectDir = reflect(-lightDir, norm);  
	//	float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Shineness);
	//	vec3 specular = specular_Strength * spec * u_lightColor;  
	//
	//	result=(vec4(ambient,1.0)+vec4(diffuse,1.0f)+vec4(specular,1.0f))*u_color;
	//	result.rgb=pow(result.rgb,vec3(1.0f/u_gamma_value));
	//}
	//
	//if(u_blinn_phong)
	//{
	//	float ambient_strength=0.5f;
	//	vec3 ambient=ambient_strength*u_lightColor;
	//
	//	vec3 norm = normalize(fs_in.v_normals);
	//	vec3 lightDir = normalize(lightPos - fs_in.v_fragPos);
	//	float diff = max(dot(norm, lightDir), 0.0);
	//	vec3 diffuse = diff * u_lightColor;
	//	
	//	// specular
	//	float specular_Strength = 0.5;
	//	vec3 viewDir = normalize(u_viewPos - fs_in.v_fragPos);
	//	vec3 halfwayDir=normalize(lightDir+viewDir);
	//	vec3 reflectDir = reflect(-lightDir, norm);  
	//
	//	float spec = pow(max(dot(norm, halfwayDir), 0.0), u_Shineness);
	//	vec3 specular = specular_Strength * spec * u_lightColor;  
	//
	//	result=(vec4(ambient,1.0)+vec4(diffuse,1.0f)+vec4(specular,1.0f))*u_color;
	//	result.rgb=pow(result.rgb,vec3(1.0f/u_gamma_value));
	//}
	//
	//if(u_light_pbr)
	//{
	//	vec3 N = normalize(fs_in.v_normals);
	//	vec3 V = normalize(u_viewPos - fs_in.v_fragPos);
	//
	//	vec3 F0 = vec3(0.04); 
	//	F0 = mix(F0, u_albedo, u_metallic);
	//	// calculate reflectance at normal incidence; if dia-electric (like plastic) use F0 
	//	// of 0.04 and if it's a metal, use the albedo color as F0 (metallic workflow)    
	//	// calculate per-light radiance
    //    vec3 Lo = vec3(0.0);
	//	vec3 L = normalize(lightPos - fs_in.v_fragPos);
    //    vec3 H = normalize(V + L);
    //    float distance = length(lightPos  - fs_in.v_fragPos);
    //    float attenuation = 1.0 / (distance * distance);
    //    vec3 radiance = lightPos   * attenuation;
    //    // Cook-Torrance BRDF
    //    float NDF = DistributionGGX(N, H, u_roughness);   
    //    float G   = GeometrySmith(N, V, L, u_roughness);      
    //    vec3 F    = fresnelSchlick(clamp(dot(H, V), 0.0, 1.0), F0);
    //       
    //    vec3 nominator    = NDF * G * F; 
    //    float denominator = 4 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0);
    //    vec3 specular = nominator / max(denominator, 0.001); // prevent divide by zero for NdotV=0.0 or NdotL=0.0
    //    
    //    // kS is equal to Fresnel
    //    vec3 kS = F;
    //    // for energy conservation, the diffuse and specular light can't
    //    // be above 1.0 (unless the surface emits light); to preserve this
    //    // relationship the diffuse component (kD) should equal 1.0 - kS.
    //    vec3 kD = vec3(1.0) - kS;
    //    // multiply kD by the inverse metalness such that only non-metals 
    //    // have diffuse lighting, or a linear blend if partly metal (pure metals
    //    // have no diffuse light).
    //    kD *= 1.0 - u_metallic;	  
	//
    //    // scale light by NdotL
    //    float NdotL = max(dot(N, L), 0.0);        
	//
    //    // add to outgoing radiance Lo
    //    Lo += (kD * u_albedo / PI + specular) * radiance * NdotL;
	//
	//
	//	vec3 ambient = vec3(0.03) * u_albedo * u_ao;
	//
	//	vec3 color = ambient + Lo;
	//
	//	// HDR tonemapping
	//	color = color / (color + vec3(1.0));
	//	// gamma correct
	//	color = pow(color, vec3(1.0/u_gamma_value)); 
	//	result=vec4(color,1.0f);
	//}
	//
	//if(u_texture_pbr)
	//{
		vec3 albedo     = pow(texture(u_albedoMap, fs_in.v_texCoords).rgb, vec3(2.2));
		float metallic  = texture(u_metallicMap, fs_in.v_texCoords).r;
		float roughness = texture(u_roughnessMap, fs_in.v_texCoords).r;
		float ao        = texture(u_aoMap, fs_in.v_texCoords).r;

		vec3 N = getNormalFromMap();
		vec3 V = normalize(u_viewPos - fs_in.v_fragPos);

		// calculate reflectance at normal incidence; if dia-electric (like plastic) use F0 
		// of 0.04 and if it's a metal, use the albedo color as F0 (metallic workflow)    
		vec3 F0 = vec3(0.04); 
		F0 = mix(F0, albedo, metallic);

		// reflectance equation
		vec3 Lo = vec3(0.0);
		// calculate per-light radiance
		vec3 L = normalize(lightPos - fs_in.v_fragPos);
		vec3 H = normalize(V + L);
		float dist = length(lightPos - fs_in.v_fragPos);
		float attenuation = 1.0 / (dist * dist);
		vec3 radiance = u_lightColor * attenuation;

		// Cook-Torrance BRDF
		float NDF = DistributionGGX(N, H, roughness);   
		float G   = GeometrySmith(N, V, L, roughness);      
		vec3 F    = fresnelSchlick(max(dot(H, V), 0.0), F0);
		   
		vec3 nominator    = NDF * G * F; 
		float denominator = 4 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.001; // 0.001 to prevent divide by zero.
		vec3 specular = nominator / denominator;
		
		// kS is equal to Fresnel
		vec3 kS = F;
		// for energy conservation, the diffuse and specular light can't
		// be above 1.0 (unless the surface emits light); to preserve this
		// relationship the diffuse component (kD) should equal 1.0 - kS.
		vec3 kD = vec3(1.0) - kS;
		// multiply kD by the inverse metalness such that only non-metals 
		// have diffuse lighting, or a linear blend if partly metal (pure metals
		// have no diffuse light).
		kD *= 1.0 - metallic;	  

		// scale light by NdotL
		float NdotL = max(dot(N, L), 0.0);        

		// add to outgoing radiance Lo
		Lo += (kD * albedo / PI + specular) * radiance * NdotL;  // note that we already multiplied the BRDF by the Fresnel (kS) so we won't multiply by kS again
		
		// ambient lighting (note that the next IBL tutorial will replace 
		// this ambient lighting with environment lighting).
		vec3 ambient = vec3(0.03) * albedo * ao;
		
		vec3 color = ambient + Lo ;

		// HDR tonemapping
		color = color / (color + vec3(1.0));
		// gamma correct
		color = pow(color, vec3(1.0/u_gamma_value)); 

		result = vec4(color, 1.0);
	//}
	FragColor=result;
}
