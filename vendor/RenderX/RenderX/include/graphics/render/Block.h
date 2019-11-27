#pragma once
#include "Renderer.h"

namespace renderx::graphics
{
	class REN_API Block :public Renderer
	{
	public:
		Block();
		~Block();

		std::shared_ptr<VertexArray> m_VertexArray;
		BufferLayout m_Layout;

		void BindVAO() override;
		void Draw() override;
		std::string GetName() override { return "Block"; }
		void SetMVP(std::function<void()> func);

	private:
		std::vector<float> m_BlockData =
		{
			// back face
			-1.0f, -1.0f, -1.0f,  0.0f, 0.0f, 0.0f,  0.0f, -1.0f, // bottom-left
			 1.0f,  1.0f, -1.0f,  1.0f, 1.0f, 0.0f,  0.0f, -1.0f, // top-right
			 1.0f, -1.0f, -1.0f,  1.0f, 0.0f, 0.0f,  0.0f, -1.0f, // bottom-right         
			 1.0f,  1.0f, -1.0f,  1.0f, 1.0f, 0.0f,  0.0f, -1.0f, // top-right
			-1.0f, -1.0f, -1.0f,  0.0f, 0.0f, 0.0f,  0.0f, -1.0f, // bottom-left
			-1.0f,  1.0f, -1.0f,  0.0f, 1.0f, 0.0f,  0.0f, -1.0f, // top-left
			// front face
			-1.0f, -1.0f,  1.0f,  0.0f, 0.0f, 0.0f,  0.0f,  1.0f, // bottom-left
			 1.0f, -1.0f,  1.0f,  1.0f, 0.0f, 0.0f,  0.0f,  1.0f, // bottom-right
			 1.0f,  1.0f,  1.0f,  1.0f, 1.0f, 0.0f,  0.0f,  1.0f, // top-right
			 1.0f,  1.0f,  1.0f,  1.0f, 1.0f, 0.0f,  0.0f,  1.0f, // top-right
			-1.0f,  1.0f,  1.0f,  0.0f, 1.0f, 0.0f,  0.0f,  1.0f, // top-left
			-1.0f, -1.0f,  1.0f,  0.0f, 0.0f, 0.0f,  0.0f,  1.0f, // bottom-left
			// left face
			-1.0f,  1.0f,  1.0f,  1.0f, 0.0f,-1.0f,  0.0f,  0.0f, // top-right
			-1.0f,  1.0f, -1.0f,  1.0f, 1.0f,-1.0f,  0.0f,  0.0f, // top-left
			-1.0f, -1.0f, -1.0f,  0.0f, 1.0f,-1.0f,  0.0f,  0.0f, // bottom-left
			-1.0f, -1.0f, -1.0f,  0.0f, 1.0f,-1.0f,  0.0f,  0.0f, // bottom-left
			-1.0f, -1.0f,  1.0f,  0.0f, 0.0f,-1.0f,  0.0f,  0.0f, // bottom-right
			-1.0f,  1.0f,  1.0f,  1.0f, 0.0f,-1.0f,  0.0f,  0.0f, // top-right
			// right face
			 1.0f,  1.0f,  1.0f,  1.0f, 0.0f, 1.0f,  0.0f,  0.0f, // top-left
			 1.0f, -1.0f, -1.0f,  0.0f, 1.0f, 1.0f,  0.0f,  0.0f, // bottom-right
			 1.0f,  1.0f, -1.0f,  1.0f, 1.0f, 1.0f,  0.0f,  0.0f, // top-right         
			 1.0f, -1.0f, -1.0f,  0.0f, 1.0f, 1.0f,  0.0f,  0.0f, // bottom-right
			 1.0f,  1.0f,  1.0f,  1.0f, 0.0f, 1.0f,  0.0f,  0.0f, // top-left
			 1.0f, -1.0f,  1.0f,  0.0f, 0.0f, 1.0f,  0.0f,  0.0f, // bottom-left     
			// bottom face
			-1.0f, -1.0f, -1.0f,  0.0f, 1.0f, 0.0f, -1.0f,  0.0f, // top-right
			 1.0f, -1.0f, -1.0f,  1.0f, 1.0f, 0.0f, -1.0f,  0.0f, // top-left
			 1.0f, -1.0f,  1.0f,  1.0f, 0.0f, 0.0f, -1.0f,  0.0f, // bottom-left
			 1.0f, -1.0f,  1.0f,  1.0f, 0.0f, 0.0f, -1.0f,  0.0f, // bottom-left
			-1.0f, -1.0f,  1.0f,  0.0f, 0.0f, 0.0f, -1.0f,  0.0f, // bottom-right
			-1.0f, -1.0f, -1.0f,  0.0f, 1.0f, 0.0f, -1.0f,  0.0f, // top-right
			// top face
			-1.0f,  1.0f, -1.0f,  0.0f, 1.0f, 0.0f,  1.0f,  0.0f, // top-left
			 1.0f,  1.0f , 1.0f,  1.0f, 0.0f, 0.0f,  1.0f,  0.0f, // bottom-right
			 1.0f,  1.0f, -1.0f,  1.0f, 1.0f, 0.0f,  1.0f,  0.0f, // top-right     
			 1.0f,  1.0f,  1.0f,  1.0f, 0.0f, 0.0f,  1.0f,  0.0f, // bottom-right
			-1.0f,  1.0f, -1.0f,  0.0f, 1.0f, 0.0f,  1.0f,  0.0f, // top-left
			-1.0f,  1.0f,  1.0f,  0.0f, 0.0f, 0.0f,  1.0f,  0.0f, // bottom-left       
		};
	};
}