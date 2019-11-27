#pragma once
#include "graphics/render/Sphere.h"

namespace renderx::graphics
{
	Sphere::Sphere()
		:X_SEGMENTS(64), Y_SEGMENTS(64), m_IndexCount(0), m_PI(3.1415926535)
	{
		CreateSphere();

		m_VertexArray = std::shared_ptr<VertexArray>(new VertexArray(sizeof(float) * m_SphereData.size(), &m_SphereData[0]));
		m_VertexArray->BindVertexArray();
		m_VertexArray->CreateEBO(sizeof(unsigned int) * m_IndexCount, &m_Indices[0]);

		m_Layout =
		{
			{ ShaderDataType::FLOAT3, "a_VertexPos" },
			{ ShaderDataType::FLOAT2, "a_TexCoords" },
			{ ShaderDataType::FLOAT3, "a_Normals" }
		};
		m_VertexArray->AddBufferLayout(m_Layout);
	}

	Sphere::~Sphere()
	{

	}

	void Sphere::BindVAO()
	{
		m_VertexArray->BindVertexArray();
	}

	void Sphere::Draw()
	{
		glDrawElements(GL_TRIANGLE_STRIP, m_IndexCount, GL_UNSIGNED_INT, 0);
	}

	void Sphere::SetMVP(std::function<void()> func)
	{
		func();
	}

	void Sphere::CreateSphere()
	{
		for (size_t y = 0; y <= Y_SEGMENTS; ++y)
		{
			for (size_t x = 0; x <= X_SEGMENTS; ++x)
			{
				float xSegment = static_cast<float>(x) / static_cast<float>(X_SEGMENTS);
				float ySegment = static_cast<float>(y) / static_cast<float>(Y_SEGMENTS);
				float xPos = std::cos(xSegment * 2.0f * m_PI) * std::sin(ySegment * m_PI);
				float yPos = std::cos(ySegment * m_PI);
				float zPos = std::sin(xSegment * 2.0f * m_PI) * std::sin(ySegment * m_PI);

				m_Positions.push_back(glm::vec3(xPos, yPos, zPos));
				m_UV.push_back(glm::vec2(xSegment, ySegment));
				m_Normals.push_back(glm::vec3(xPos, yPos, zPos));
			}
		}

		bool oddRow = false;
		for (int32_t y = 0; y < Y_SEGMENTS; ++y)
		{
			if (!oddRow) // even rows: y == 0, y == 2; and so on
			{
				for (int32_t x = 0; x <= X_SEGMENTS; ++x)
				{
					m_Indices.push_back(y * (X_SEGMENTS + 1) + x);
					m_Indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
				}
			}
			else
			{
				for (int32_t x = X_SEGMENTS; x >= 0; --x)
				{
					m_Indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
					m_Indices.push_back(y * (X_SEGMENTS + 1) + x);
				}
			}
			oddRow = !oddRow;
		}
		m_IndexCount = m_Indices.size();

		for (int i = 0; i < m_Positions.size(); ++i)
		{
			m_SphereData.push_back(m_Positions[i].x);
			m_SphereData.push_back(m_Positions[i].y);
			m_SphereData.push_back(m_Positions[i].z);
			if (m_UV.size() > 0)
			{
				m_SphereData.push_back(m_UV[i].x);
				m_SphereData.push_back(m_UV[i].y);
			}
			if (m_Normals.size() > 0)
			{
				m_SphereData.push_back(m_Normals[i].x);
				m_SphereData.push_back(m_Normals[i].y);
				m_SphereData.push_back(m_Normals[i].z);
			}
		}

	}
}