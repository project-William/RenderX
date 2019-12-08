#pragma once
#include "VertexBuffer.h"
#include "BufferLayout.h"
#include "IndexBuffer.h"

namespace renderx::graphics
{

	class REN_API VertexArray
	{
	private:
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		GLuint m_VertexArray;
	public:
		VertexArray(size_t size, const void* data);
		~VertexArray();
		void CreateEBO(size_t indices_size, const void* indices_data);

		void AddBufferLayout(const BufferLayout& layout);

		void BindVertexArray()const;
		void UnbindVertexArray()const;

	};
}