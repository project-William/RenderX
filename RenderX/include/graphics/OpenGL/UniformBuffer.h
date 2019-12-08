#pragma once
#include "..//..//..//Common.h"

namespace renderx::graphics
{
	class UniformBuffer
	{
	public:
		UniformBuffer() {}
		~UniformBuffer() {}

		void AddBufferData(size_t size);

		void Bind();
		void Unbind();

	private:
		GLuint m_UniformVBO;
	};
}