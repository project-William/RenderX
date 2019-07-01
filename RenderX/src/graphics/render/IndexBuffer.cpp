#include "graphics/render/IndexBuffer.h"


namespace renderx {
	namespace graphics {

		IndexBuffer::IndexBuffer()
			:m_IndexBufferID(0)
		{
			glGenBuffers(1, &m_IndexBufferID);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferID);
		}

		IndexBuffer::~IndexBuffer()
		{
			glDeleteBuffers(1, &m_IndexBufferID);
		}


		void IndexBuffer::Bind()const
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferID);
		}

		void IndexBuffer::Unbind()const
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		void IndexBuffer::AddData(unsigned int size, const void* data)
		{
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
		}
	}
}