#pragma once
#include "..//shader/Shader.h"
#include "..//VAOVBOEBO/VertexArray.h"
#include "..//Window.h"
#include "..//..//entity/FPSCamera.h"
#include "..//..//entity/MayaCamera.h"
#include "..//texture/Texture.h"
#include "BasicLight.h"


namespace renderx {
	namespace graphics {

		struct REN_API RenderData
		{
			std::shared_ptr<Shader> m_Shader;
			std::shared_ptr<VertexArray> m_VAO;
			BufferLayout m_Layout;

			std::vector<glm::vec3> m_Positions;
			std::vector<glm::vec2> m_UV;
			std::vector<glm::vec3> m_Normals;
			std::vector<glm::vec3> m_Tangent;
			std::vector<glm::vec3> m_Bitangent;
			std::vector<unsigned int> m_Indices;

			unsigned int m_AlbedoTex = 0;
			unsigned int m_AOTex = 0;
			unsigned int m_MetallicTex = 0;
			unsigned int m_NormalTex = 0;
			unsigned int m_RoughnessTex = 0;
			

			RenderData()
				:m_Shader(nullptr), m_VAO(nullptr)
			{

			}
		};

		struct REN_API Transformation
		{
			float perspective_radians;
			float s_scale = 1.0f;
			glm::vec3 scale;
			glm::mat4 model;
			glm::mat4 view;
			glm::mat4 projection;
			glm::vec4 color;
			Transformation()
				:perspective_radians(45.0f),
				 scale(glm::vec3(1.0f, 1.0f, 1.0f)),
				 model(glm::mat4(1.0f)),
				 view(glm::mat4(1.0f)),
				 projection(glm::mat4(1.0f)),
				 color(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f))
			{

			}

		};


		class REN_API RenderObject
		{
		public:
			RenderObject() {}
			virtual ~RenderObject() {}

			virtual void BindObject() const = 0;
			virtual void UnbindObject() const = 0;
			virtual void Draw(const WinData& windata) = 0;
			virtual inline Transformation& GetTransRef() = 0;
			virtual inline RenderData* GetRenderDataRef() = 0;

			virtual void SetAlbedoTex(const std::string& file) = 0;
			virtual void SetNormalTex(const std::string& file) = 0;
			virtual void SetAOTex(const std::string& file) = 0;
			virtual void SetRoughnessTex(const std::string& file) = 0;
			virtual void SetMetallicTex(const std::string& file) = 0;

			virtual unsigned int& GetAlbedoTexture() = 0;
			virtual unsigned int& GetAOTexture() = 0;
			virtual unsigned int& GetMetallicTexture() = 0;
			virtual unsigned int& GetNormalTexture() = 0;
			virtual unsigned int& GetRoughnessTexture() = 0;

			virtual void EnableAlbedoTexture() = 0;
			virtual void EnableAOTexture() = 0;
			virtual void EnableMetallicTexture() = 0;
			virtual void EnableNormalTexture() = 0;
			virtual void EnableRoughnessTexture() = 0;
			
			virtual void DisableAlbedoTexture() = 0;
			virtual void DisableAOTexture() = 0;
			virtual void DisableMetallicTexture() = 0;
			virtual void DisableNormalTexture() = 0;
			virtual void DisableRoughnessTexture() = 0;


		
		};


	}
}