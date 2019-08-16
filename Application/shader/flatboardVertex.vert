#version 410
layout (location = 0) in vec3 a_VertexPos;
layout (location = 1) in vec3 a_Normal;
layout (location = 2) in vec2 a_TexCoords;
layout (location = 3) in vec3 a_Tangent;
layout (location = 4) in vec3 a_Bitangent;

out VS_OUT {
    vec3 v_fragPos;
    vec2 v_texCoords;
	vec3 v_normals;
    vec3 v_tangentLightPos;
    vec3 v_tangentViewPos;
    vec3 v_tangentFragPos;
} vs_out;

uniform mat4 u_projection;
uniform mat4 u_view;
uniform mat4 u_model;

uniform vec3 u_lightPos;
uniform vec3 u_viewPos;




void main()
{
	vec3 lightPos=vec3(u_lightPos.x,-u_lightPos.y,u_lightPos.z);
	vs_out.v_normals=a_Normal;

    vs_out.v_fragPos = vec3(u_model * vec4(a_VertexPos, 1.0));   
    vs_out.v_texCoords = a_TexCoords;
    
    mat3 normalMatrix = transpose(inverse(mat3(u_model)));
    vec3 T = normalize(normalMatrix * a_Tangent);
    vec3 N = normalize(normalMatrix * a_Normal);
    T = normalize(T - dot(T, N) * N);
    vec3 B = cross(N, T);
    
    mat3 TBN = transpose(mat3(T, B, N));    
    vs_out.v_tangentLightPos = TBN * lightPos;
    vs_out.v_tangentViewPos  = TBN * u_viewPos;
    vs_out.v_tangentFragPos  = TBN * vs_out.v_fragPos;
        
    gl_Position = u_projection * u_view * u_model * vec4(a_VertexPos, 1.0);
}