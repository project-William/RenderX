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
// IBL
uniform samplerCube u_irradianceMap;
uniform samplerCube u_prefilterMap;
uniform sampler2D u_brdfLUT;

uniform bool u_IsBlinnTexture;


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

//skybox
uniform samplerCube u_skybox;

uniform bool u_light_pbr;
uniform bool u_texture_pbr;
uniform bool u_environment_mapping;


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
vec3 fresnelSchlickRoughness(float cosTheta, vec3 F0, float roughness)
{
    return F0 + (max(vec3(1.0 - roughness), F0) - F0) * pow(1.0 - cosTheta, 5.0);
} 
// ----------------------------------------------------------------------------

vec3 BlinnPhong(vec3 lightpos)
{
	vec3 result;
	//ambient
	vec3 ambient;
	vec3 texture_color;
	if(u_IsBlinnTexture)
	{
		vec3 texture_color=texture(u_albedoMap,fs_in.v_texCoords).rgb;
		ambient=0.5f* texture_color;
	}
	else
	{
		ambient=0.5f* vec3(u_lightColor);
	}
	//diffuse
	vec3 normals=normalize(fs_in.v_normals);
	vec3 lightDir=normalize(vec3(3.0f,-3.0f,3.0f)- fs_in.v_fragPos);
	float diff=max(dot(normals,lightDir),0.0f);
	vec3 diffuse;
    if(u_IsBlinnTexture)
	{
		diffuse=diff* texture_color;
	}
	else
	{
		diffuse= diff* vec3(u_lightColor);
	}
	//specular
	vec3 viewDir = normalize(u_viewPos - fs_in.v_fragPos);
    vec3 reflectDir = reflect(-lightDir, normals);
    float spec = 0.0;
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    spec = pow(max(dot(normals, halfwayDir), 0.0), 32.0);
    vec3 specular = vec3(u_lightColor) * spec *0.5f;

	result=ambient+diffuse+specular;
	return result;
}


vec3 LightAndTexturePBR(vec3 lightpos,bool texture_pbr)
{
	vec3 albedo     = pow(texture(u_albedoMap, fs_in.v_texCoords).rgb, vec3(2.2));
	float metallic  = texture(u_metallicMap, fs_in.v_texCoords).r;
	float roughness = texture(u_roughnessMap, fs_in.v_texCoords).r;
	float ao        = texture(u_aoMap, fs_in.v_texCoords).r;

	vec3 N;
	vec3 V;
	vec3 R;
	if(texture_pbr)
	{
		N = getNormalFromMap();
		V = normalize(u_viewPos - fs_in.v_fragPos);
	}
	else 
	{
		N = normalize(fs_in.v_normals);
		V = normalize(u_viewPos - fs_in.v_fragPos);
		vec3 R = reflect(-V, N);
	}
	
	vec3 F0 = vec3(0.04); 
	if(texture_pbr)
	{
		F0=mix(F0,albedo,metallic);
	}
	else
	{
		F0 = mix(F0, u_albedo, u_metallic);
	}
	// calculate reflectance at normal incidence; if dia-electric (like plastic) use F0 
	// of 0.04 and if it's a metal, use the albedo color as F0 (metallic workflow)    
	// calculate per-light radiance
    vec3 Lo = vec3(0.0);
	for(int i=0;i<4;i++)
	{
		vec3 L = normalize(lightpos - fs_in.v_fragPos);
		vec3 H = normalize(V + L);
		float distance = length(lightpos  - fs_in.v_fragPos);
		float attenuation = 1.0 / (distance * distance);
		vec3 radiance = (u_lightColor * 300)   * attenuation;
		// Cook-Torrance BRDF
		float NDF;
		float G;

		if(texture_pbr)
		{
			NDF=DistributionGGX(N,H,roughness);
			G=GeometrySmith(N,V,L,roughness);
		}
		else
		{
			NDF = DistributionGGX(N, H, u_roughness);   
			G   = GeometrySmith(N, V, L, u_roughness);      
		}
		
		vec3 F  = fresnelSchlick(clamp(dot(H, V), 0.0, 1.0), F0);
		//   
		vec3 nominator    = NDF * G * F; 
		float denominator = 4 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0);
		vec3 specular = nominator / max(denominator, 0.001); // prevent divide by zero for NdotV=0.0 or NdotL=0.0
		
		// kS is equal to Fresnel
		vec3 kS = F;
		// for energy conservation, the diffuse and specular light can't
		// be above 1.0 (unless the surface emits light); to preserve this
		// relationship the diffuse component (kD) should equal 1.0 - kS.
		vec3 kD = vec3(1.0) - kS;
		// multiply kD by the inverse metalness such that only non-metals 
		// have diffuse lighting, or a linear blend if partly metal (pure metals
		// have no diffuse light).
		if(texture_pbr)
		{
		    kD *= 1.0 - metallic;	  
		}
		else
		{
		    kD *= 1.0 - u_metallic;	  
		}

		//
		// scale light by NdotL
		float NdotL = max(dot(N, L), 0.0);        
		
		// add to outgoing radiance Lo
		if(texture_pbr)
		{
		    Lo += (kD * albedo/ PI + specular) * radiance * NdotL;
		}
		else
		{
		    Lo += (kD * u_albedo / PI + specular) * radiance * NdotL;
		}

	}
	//
	//
	vec3 ambient;
	if(texture_pbr)
	{
		ambient = vec3(0.03) * albedo * ao;
	}
	else 
	{
		ambient = vec3(0.03) * u_albedo * u_ao;
		 // ambient lighting (we now use IBL as the ambient term)
	    //vec3 F = fresnelSchlickRoughness(max(dot(N, V), 0.0), F0, roughness);
	    //
	    //vec3 kS = F;
	    //vec3 kD = 1.0 - kS;
	    //kD *= 1.0 - metallic;	  
	    //
	    //vec3 irradiance = texture(u_irradianceMap, N).rgb;
	    //vec3 diffuse      = irradiance * albedo;
	    //
	    //// sample both the pre-filter map and the BRDF lut and combine them together as per the Split-Sum approximation to get the IBL specular part.
	    //const float MAX_REFLECTION_LOD = 4.0;
	    //vec3 prefilteredColor = textureLod(u_prefilterMap, R,  roughness * MAX_REFLECTION_LOD).rgb;    
	    //vec2 brdf  = texture(u_brdfLUT, vec2(max(dot(N, V), 0.0), roughness)).rg;
	    //vec3 specular = prefilteredColor * (F * brdf.x + brdf.y);
	    //
	    //vec3 ambient = (kD * diffuse + specular) * u_ao;
    
	}
	//
	vec3 color = (ambient + Lo );
	//
	// HDR tonemapping
	color = color / (color + vec3(1.0));
	// gamma correct
	color = pow(color, vec3(1.0/u_gamma_value)); 
	return color;

	
}

void main()
{
	vec3 result;
	vec3 lightPos=vec3(u_lightPos.x,-u_lightPos.y,u_lightPos.z);
    
	if(u_blinn_phong)
	{
		result =BlinnPhong(lightPos);
	}
	
	if(u_light_pbr)
	{
		result=LightAndTexturePBR(lightPos, u_texture_pbr);
	}

	if(u_environment_mapping)
	{
		float ratio = 1.00 / 1.52;
		vec3 I = normalize(fs_in.v_fragPos - u_viewPos);
		vec3 R = refract(I, normalize(fs_in.v_normals), ratio);
		FragColor = vec4(texture(u_skybox, R).rgb, 1.0);
	}

	if(u_texture_pbr)
	{
		result=LightAndTexturePBR(lightPos, u_texture_pbr);
		FragColor=vec4(result,1.0f);
	}
	else
	{
		FragColor=vec4(result,1.0f) * u_color;
	}
}
