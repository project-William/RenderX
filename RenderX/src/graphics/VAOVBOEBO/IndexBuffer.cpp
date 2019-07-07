#include "graphics/VAOVBOEBO/IndexBuffer.h"


namespace renderx {
	namespace graphics {

		IndexBuffer::IndexBuffer()
			:m_IndexBuffer(0)
		{

		}

		IndexBuffer::~IndexBuffer()
		{
			glDeleteBuffers(1, &m_IndexBuffer);
		}

		IndexBuffer::IndexBuffer(unsigned int size, const void* data)
			: m_IndexBuffer(0)
		{
			glGenBuffers(1, &m_IndexBuffer);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
		}


		void IndexBuffer::Bind()const
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
		}
		
		void IndexBuffer::Unbind()const
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

	}
}