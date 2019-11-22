#pragma once
#include "Renderer.h"

namespace renderx
{
	namespace graphics
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
				// positions         // texture coords // normals           
				-1.0f, -1.0f, -1.0f, 0.0f,  0.0f, 0.0f,  0.0f, -1.0f,
				 1.0f, -1.0f, -1.0f, 1.0f,  0.0f, 0.0f,  0.0f, -1.0f,
				 1.0f,  1.0f, -1.0f, 1.0f,  1.0f, 0.0f,  0.0f, -1.0f,
				 1.0f,  1.0f, -1.0f, 1.0f,  1.0f, 0.0f,  0.0f, -1.0f,
				-1.0f,  1.0f, -1.0f, 0.0f,  1.0f, 0.0f,  0.0f, -1.0f,
				-1.0f, -1.0f, -1.0f, 0.0f,  0.0f, 0.0f,  0.0f, -1.0f,

				-1.0f, -1.0f,  1.0f, 0.0f,  0.0f, 0.0f,  0.0f,  1.0f,
				 1.0f, -1.0f,  1.0f, 1.0f,  0.0f, 0.0f,  0.0f,  1.0f,
				 1.0f,  1.0f,  1.0f, 1.0f,  1.0f, 0.0f,  0.0f,  1.0f,
				 1.0f,  1.0f,  1.0f, 1.0f,  1.0f, 0.0f,  0.0f,  1.0f,
				-1.0f,  1.0f,  1.0f, 0.0f,  1.0f, 0.0f,  0.0f,  1.0f,
				-1.0f, -1.0f,  1.0f, 0.0f,  0.0f, 0.0f,  0.0f,  1.0f,

				-1.0f,  1.0f,  1.0f, 1.0f,  0.0f, 1.0f,  0.0f,  0.0f,
				-1.0f,  1.0f, -1.0f, 1.0f,  1.0f, 1.0f,  0.0f,  0.0f,
				-1.0f, -1.0f, -1.0f, 0.0f,  1.0f, 1.0f,  0.0f,  0.0f,
				-1.0f, -1.0f, -1.0f, 0.0f,  1.0f, 1.0f,  0.0f,  0.0f,
				-1.0f, -1.0f,  1.0f, 0.0f,  0.0f, 1.0f,  0.0f,  0.0f,
				-1.0f,  1.0f,  1.0f, 1.0f,  0.0f, 1.0f,  0.0f,  0.0f,

				 1.0f,  1.0f,  1.0f, 1.0f,  0.0f, 1.0f,  0.0f,  0.0f,
				 1.0f,  1.0f, -1.0f, 1.0f,  1.0f, 1.0f,  0.0f,  0.0f,
				 1.0f, -1.0f, -1.0f, 0.0f,  1.0f, 1.0f,  0.0f,  0.0f,
				 1.0f, -1.0f, -1.0f, 0.0f,  1.0f, 1.0f,  0.0f,  0.0f,
				 1.0f, -1.0f,  1.0f, 0.0f,  0.0f, 1.0f,  0.0f,  0.0f,
				 1.0f,  1.0f,  1.0f, 1.0f,  0.0f, 1.0f,  0.0f,  0.0f,

				-1.0f, -1.0f, -1.0f, 0.0f,  1.0f, 0.0f, -1.0f,  0.0f,
				 1.0f, -1.0f, -1.0f, 1.0f,  1.0f, 0.0f, -1.0f,  0.0f,
				 1.0f, -1.0f,  1.0f, 1.0f,  0.0f, 0.0f, -1.0f,  0.0f,
				 1.0f, -1.0f,  1.0f, 1.0f,  0.0f, 0.0f, -1.0f,  0.0f,
				-1.0f, -1.0f,  1.0f, 0.0f,  0.0f, 0.0f, -1.0f,  0.0f,
				-1.0f, -1.0f, -1.0f, 0.0f,  1.0f, 0.0f, -1.0f,  0.0f,

				-1.0f,  1.0f, -1.0f, 0.0f,  1.0f, 0.0f,  1.0f,  0.0f,
				 1.0f,  1.0f, -1.0f, 1.0f,  1.0f, 0.0f,  1.0f,  0.0f,
				 1.0f,  1.0f,  1.0f, 1.0f,  0.0f, 0.0f,  1.0f,  0.0f,
				 1.0f,  1.0f,  1.0f, 1.0f,  0.0f, 0.0f,  1.0f,  0.0f,
				-1.0f,  1.0f,  1.0f, 0.0f,  0.0f, 0.0f,  1.0f,  0.0f,
				-1.0f,  1.0f, -1.0f, 0.0f,  1.0f, 0.0f,  1.0f,  0.0f,
			};
		};
	}
}