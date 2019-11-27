#pragma once

#include "..//..//..//Common.h"

namespace renderx::graphics
{

	class REN_API VertexBuffer
	{
	private:
		GLuint m_VertexBuffer;
	public:
		VertexBuffer(size_t size, const void* data);
		~VertexBuffer();

		void Bind()const;
		void Unbind()const;
	};
}