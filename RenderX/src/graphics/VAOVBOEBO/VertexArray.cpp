#include "graphics/VAOVBOEBO/VertexArray.h"

namespace renderx {
	namespace graphics {

		VertexArray::VertexArray()
			:m_Vertexbuffer(nullptr),m_VertexArray(0),m_IndexBuffer(0)
		{

		}

		VertexArray::VertexArray(unsigned int size, const void* data)
			:m_VertexArray(0),
			 m_Vertexbuffer(new VertexBuffer(size, data)),
			 m_IndexBuffer(new IndexBuffer())
		{
			glGenVertexArrays(1, &m_VertexArray);
		}

		VertexArray::~VertexArray()
		{
			glDeleteVertexArrays(1, &m_VertexArray);
			delete m_Vertexbuffer;
			delete m_IndexBuffer;
		}

		void VertexArray::AddEbo(unsigned int indices_size, const void* indices_data)
		{
			delete m_IndexBuffer;
			m_IndexBuffer = new IndexBuffer(indices_size, indices_data);
		}

		void VertexArray::AddBufferLayout(const BufferLayout& layout)
		{
			m_Vertexbuffer->Bind();
			m_IndexBuffer->Bind();
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
			m_Vertexbuffer->Unbind();
			m_IndexBuffer->Unbind();
		}

	}
}