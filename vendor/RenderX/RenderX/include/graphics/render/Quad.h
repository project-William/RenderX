#pragma once
#include "Renderer.h"

namespace renderx::graphics
{
	class REN_API Quad :public Renderer
	{
	public:
		Quad();
		~Quad();

		std::shared_ptr<VertexArray> m_VertexArray;
		BufferLayout m_Layout;

		void BindVAO() override;
		void Draw() override;
		std::string GetName() override { return "Quad"; }
		void SetMVP(std::function<void()> func);

	private:
		std::vector<float> m_QuadData = {
			// positions        // texture Coords
			-1.0f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
			 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
			 1.0f,  1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-1.0f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
			 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		};
	};
}