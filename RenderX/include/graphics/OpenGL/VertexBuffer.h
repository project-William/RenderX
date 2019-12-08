#pragma once

#include "..//..//..//Common.h"

namespace renderx::graphics
{

	class REN_API VertexBuffer
	{
	private:
		GLuint m_VertexBuffer;
	public:
		VertexBuffer():m_VertexBuffer(0) {}
		VertexBuffer(size_t size, const void* data);
		~VertexBuffer();

		void AddBufferData(size_t size, void* data);
		void AddSubBufferData(size_t size, size_t offset, void* data);


		void Bind()const;
		void Unbind()const;
	};
}