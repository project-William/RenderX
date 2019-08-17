#pragma once
#include "..//graphics/render/RenderObject.h"


namespace renderx {
	namespace entity {

		class REN_API Flatboard
		{
		public:
			explicit Flatboard(const std::string& vsfile,const  std::string& ffile);
			~Flatboard();

			void EnableObject();
			void DisableObject();

			void Draw(const graphics::WinData& windata, FPSCamera* camera);

			inline std::shared_ptr<graphics::RenderData>& GetRenderDataRef() { return m_RenderData; }
			inline graphics::Transformation& GetTransRef() { return m_Trans; }

		private:
			std::shared_ptr<graphics::Texture> m_AlbedoTex;
			std::shared_ptr<graphics::Texture> m_NormalTex;


			std::shared_ptr<graphics::RenderData> m_RenderData;
			graphics::Transformation m_Trans;
			std::vector<float> m_VertexData;
			
			//Position
			glm::vec3 m_Pos1;
			glm::vec3 m_Pos2;
			glm::vec3 m_Pos3;
			glm::vec3 m_Pos4;
			//texcoord
			glm::vec2 m_Uv1;
			glm::vec2 m_Uv2;
			glm::vec2 m_Uv3;
			glm::vec2 m_Uv4;
			//normal
			glm::vec3 m_Nm;
		private:
			void PositionTexCoordNormal()
			{
				m_Pos1 = glm::vec3(-1.0f, 0.0f, -1.0f);
				m_Pos2 = glm::vec3(-1.0f, 0.0f,  1.0f);
				m_Pos3 = glm::vec3( 1.0f, 0.0f,  1.0f);
				m_Pos4 = glm::vec3( 1.0f, 0.0f, -1.0f);
				m_Uv1 = glm::vec2(0.0, 1.0);
				m_Uv2 = glm::vec2(0.0, 0.0);
				m_Uv3 = glm::vec2(1.0, 0.0);
				m_Uv4 = glm::vec2(1.0, 1.0);
				m_Nm = glm::vec3(0.0, 1.0, 0.0);
				// calculate tangent/bitangent vectors of both triangles
				glm::vec3 tangent1, bitangent1;
				glm::vec3 tangent2, bitangent2;
				// triangle 1
				// ----------
				glm::vec3 edge1 = m_Pos2 - m_Pos1;
				glm::vec3 edge2 = m_Pos3 - m_Pos1;
				glm::vec2 deltaUV1 = m_Uv2 - m_Uv1;
				glm::vec2 deltaUV2 = m_Uv3 - m_Uv1;

				GLfloat f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

				tangent1.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
				tangent1.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
				tangent1.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
				tangent1 = glm::normalize(tangent1);

				bitangent1.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
				bitangent1.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
				bitangent1.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
				bitangent1 = glm::normalize(bitangent1);

				// triangle 2
				// ----------
				edge1 = m_Pos3 - m_Pos1;
				edge2 = m_Pos4 - m_Pos1;
				deltaUV1 = m_Uv3 - m_Uv1;
				deltaUV2 = m_Uv4 - m_Uv1;

				f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

				tangent2.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
				tangent2.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
				tangent2.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
				tangent2 = glm::normalize(tangent2);


				bitangent2.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
				bitangent2.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
				bitangent2.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
				bitangent2 = glm::normalize(bitangent2);


				m_VertexData = {
					// positions							// normal				// texcoords	// tangent							// bitangent
					10*m_Pos1.x, 10*m_Pos1.y, 10*m_Pos1.z, m_Nm.x, m_Nm.y, m_Nm.z, m_Uv1.x, m_Uv1.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,
					10*m_Pos2.x, 10*m_Pos2.y, 10*m_Pos2.z, m_Nm.x, m_Nm.y, m_Nm.z, m_Uv2.x, m_Uv2.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,
					10*m_Pos3.x, 10*m_Pos3.y, 10*m_Pos3.z, m_Nm.x, m_Nm.y, m_Nm.z, m_Uv3.x, m_Uv3.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,
					10*m_Pos1.x, 10*m_Pos1.y, 10*m_Pos1.z, m_Nm.x, m_Nm.y, m_Nm.z, m_Uv1.x, m_Uv1.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z,
					10*m_Pos3.x, 10*m_Pos3.y, 10*m_Pos3.z, m_Nm.x, m_Nm.y, m_Nm.z, m_Uv3.x, m_Uv3.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z,
					10*m_Pos4.x, 10*m_Pos4.y, 10*m_Pos4.z, m_Nm.x, m_Nm.y, m_Nm.z, m_Uv4.x, m_Uv4.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z
				};
				
			}

		};
	}
}