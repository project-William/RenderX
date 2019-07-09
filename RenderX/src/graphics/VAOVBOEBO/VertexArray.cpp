#include "graphics/VAOVBOEBO/VertexArray.h"

namespace renderx {
	namespace graphics {

		VertexArray::VertexArray()
			:m_Vbuffer(nullptr),m_VertexArray(0)
		{

		}

		VertexArray::VertexArray(unsigned int size, const void* data)
			:m_VertexArray(0),m_Vbuffer(new VertexBuffer(size, data))
		{
			glGenVertexArrays(1, &m_VertexArray);
		}

		VertexArray::~VertexArray()
		{
			glDeleteVertexArrays(1, &m_VertexArray);
			delete m_Vbuffer;
		}

		void VertexArray::AddBuffer(unsigned int stride, const void* offset)
		{
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, offset);
		}

		void VertexArray::AddBufferLayout(const BufferLayout& layout)
		{
			m_Vbuffer->Bind();
			BindVertexArray();

			GLuint index = 0;
			GLuint offset = 0;
			auto& elements = layout.GetBufferElements();

			for (auto& element : elements)
			{
				glEnableVertexAttribArray(index);
				glVertexAttribPointer(index, element.GetElementCount(), 
					GL_FLOAT, GL_FALSE, 
					layout.GetStride(),
					(const void*)offset);
				offset += element.GetElementSize();
				index++;
			}

		}

		void VertexArray::BindVertexArray()const
		{
			glBindVertexArray(m_VertexArray);
		}

		void VertexArray::UnbindVertexArray()const
		{
			glBindVertexArray(0);
		}

	}
}