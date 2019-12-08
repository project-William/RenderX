#pragma once
#include "..//..//..//Common.h"

namespace renderx::graphics
{

	class REN_API IndexBuffer
	{
	private:
		GLuint m_IndexBuffer;
	public:
		IndexBuffer(size_t size, const void* data);
		~IndexBuffer();

		void Bind()const;
		void Unbind()const;
	};
}