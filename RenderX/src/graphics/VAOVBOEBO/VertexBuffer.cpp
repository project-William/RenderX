#include "graphics/VAOVBOEBO/VertexBuffer.h"

namespace renderx {
	namespace graphics {
		VertexBuffer::VertexBuffer()
			:m_VertexBuffer(0)
		{

		}


		VertexBuffer::VertexBuffer(unsigned int size, const void* data)
			:m_VertexBuffer(0)
		{
			glGenBuffers(1, &m_VertexBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
			glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
		}

		VertexBuffer::~VertexBuffer()
		{
			glDeleteBuffers(1, &m_VertexBuffer);
		}

		void VertexBuffer::Bind()const
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
		}

		void VertexBuffer::Unbind()const
		{
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
	}
}