#pragma once
#include "Renderer.h"

namespace renderx::graphics
{
	class REN_API Sphere :public Renderer
	{
	public:
		Sphere();
		~Sphere();

		void BindVAO()override;
		void Draw()override;
		std::string GetName() override { return "Sphere"; }

		void SetMVP(std::function<void()> func);
	private:
		std::shared_ptr<VertexArray> m_VertexArray;
		BufferLayout m_Layout;

		size_t m_IndexCount;
		const int32_t X_SEGMENTS;
		const int32_t Y_SEGMENTS;
		const float m_PI;
		std::vector<float> m_SphereData;
		void CreateSphere();

		std::vector<glm::vec3> m_Positions;
		std::vector<glm::vec2> m_UV;
		std::vector<glm::vec3> m_Normals;
		std::vector<uint32_t> m_Indices;
	};
}