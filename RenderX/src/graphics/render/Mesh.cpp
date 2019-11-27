#include "graphics/render/Mesh.h"
#include "graphics/Shader.h"

namespace renderx::graphics
{
	Mesh::Mesh(const std::vector<Vertex>& vertices,
		const std::vector<uint32_t>& indices,
		const std::vector<TextureInfo>& textures)
		:m_Vertices(vertices), m_Indices(indices), m_Textures(textures)
	{
		SetupMesh();
	}

	void Mesh::SetupMesh()
	{
		m_VAO = std::shared_ptr<graphics::VertexArray>(new graphics::VertexArray(sizeof(float) * m_Vertices.size(), &m_Vertices[0]));
		m_VAO->CreateEBO(sizeof(uint32_t) * m_Indices.size(), &m_Indices[0]);

		m_Layout =
		{
			{ ShaderDataType::FLOAT3, "a_VertexPos" },
			{ ShaderDataType::FLOAT2, "a_TexCoords" },
			{ ShaderDataType::FLOAT3, "a_Normals" },
			{ ShaderDataType::FLOAT3, "a_Tangent" },
			{ ShaderDataType::FLOAT3, "a_Bitangent" },
		};

		m_VAO->AddBufferLayout(m_Layout);
		m_VAO->UnbindVertexArray();
	}

	void Mesh::Draw(std::shared_ptr<Shader> shader)
	{
		size_t diffuseNr = 1;
		size_t specularNr = 1;
		size_t normalNr = 1;
		size_t heightNr = 1;

		for (size_t i = 0; i < m_Textures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE3 + i);
			std::string number;
			std::string name = m_Textures[i].type;
			if (name == "texture_diffuse")
				number = std::to_string(diffuseNr++);
			else if (name == "texture_specular")
				number = std::to_string(specularNr++);
			else if (name == "texture_normal")
				number = std::to_string(normalNr++);
			else if (name == "texture_height")
				number = std::to_string(heightNr++);


			shader->SetInt((name + number), i);
			glBindTexture(GL_TEXTURE_2D, m_Textures[i].id);
		}
		//draw mesh
		m_VAO->BindVertexArray();
		glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, 0);
		m_VAO->UnbindVertexArray();
	}
}