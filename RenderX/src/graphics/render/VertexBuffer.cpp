#include "graphics/render/VertexBuffer.h"


namespace renderx {
	namespace graphics {

		VertexBuffer::VertexBuffer()
			:m_VertexBufferID(0)
		{
			glGenBuffers(1, &m_VertexBufferID);
			glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
		}

		VertexBuffer::~VertexBuffer()
		{
			glDeleteBuffers(1, &m_VertexBufferID);
		}

		void VertexBuffer::Bind()const 
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
		}

		void VertexBuffer::Unbind()const 
		{
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		void VertexBuffer::AddData(unsigned int size, const void* data)
		{
			glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
		}

	}
}