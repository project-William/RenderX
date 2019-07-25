#pragma once
#include "VertexBuffer.h"
#include "BufferLayout.h"
#include "IndexBuffer.h"

namespace renderx {
	namespace graphics {

		class REN_API VertexArray
		{
		private:
			GLuint m_VertexArray;
			VertexBuffer* m_Vertexbuffer;
			BufferLayout m_Layout;
			IndexBuffer* m_IndexBuffer;
		public:
			VertexArray();
			VertexArray(unsigned int size, const void* data);
			~VertexArray();
			void AddEbo(unsigned int indices_size, const void* indices_data);

			void AddBufferLayout(const BufferLayout& layout);

			void BindVertexArray()const;
			void UnbindVertexArray()const;

		};
		
	}
}