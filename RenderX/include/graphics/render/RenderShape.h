#pragma once
#include "RenderObject.h"


namespace renderx {
	namespace graphics {
		
		class REN_API RenderShape :public RenderObject
		{
		private:
			struct Shape
			{
				std::unique_ptr<Shader> m_Shader = nullptr;
				std::unique_ptr<VertexArray> m_VAO = nullptr;
				BufferLayout m_Layout;

			};
			
			std::pair<Shape*, Shape*> m_Shape;
			
			ShapeData m_ShapeData;
		public:
			RenderShape();
			~RenderShape();

			void BindObject()const;
			void UnbindObject()const;

			void Draw();
		private:
			void DrawTriangle();
			void DrawRectangle();
			void MakeShape();
		};

	}
}