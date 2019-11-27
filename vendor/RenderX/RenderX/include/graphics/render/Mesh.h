#pragma once
#include "..//..//..//Common.h"
#include "..//VAOVBOEBO/VertexArray.h"

namespace renderx::graphics
{
	class Shader;
	struct Vertex {
		// position
		glm::vec3 Position;
		// normal
		glm::vec3 Normal;
		// texCoords
		glm::vec2 TexCoords;
		// tangent
		glm::vec3 Tangent;
		// bitangent
		glm::vec3 Bitangent;
	};

	struct TextureInfo
	{
		uint32_t id;
		std::string type;
		std::string path;
	};

	class REN_API Mesh
	{
	public:
		Mesh() {}

		Mesh(const std::vector<Vertex>& vertices,
			const std::vector<uint32_t>& indices,
			const std::vector<TextureInfo>& textures);
		~Mesh() {}

		void Draw(std::shared_ptr<Shader> shader);

	private:
		std::vector<Vertex> m_Vertices;
		std::vector<uint32_t> m_Indices;
		std::vector<TextureInfo> m_Textures;

		std::shared_ptr<VertexArray> m_VAO;
		BufferLayout m_Layout;

		void SetupMesh();


	};
}