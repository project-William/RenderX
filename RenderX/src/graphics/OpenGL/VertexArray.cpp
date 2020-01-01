#include "graphics/OpenGL/VertexArray.h"

namespace renderx::graphics
{

	VertexArray::VertexArray(size_t size, const void* data)
		:m_VertexArray(0)
	{
		m_VertexBuffer = std::unique_ptr<VertexBuffer>(new VertexBuffer(size, data));
		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_VertexArray);
	}

	void VertexArray::CreateEBO(size_t indices_size, const void* indices_data)
	{
		m_IndexBuffer = std::unique_ptr<IndexBuffer>(new IndexBuffer(indices_size, indices_data));
	}

	void VertexArray::AddBufferLayout(const BufferLayout& layout)
	{
		BindVertexArray();
		m_VertexBuffer->Bind();
		if (m_IndexBuffer)
		{
			m_IndexBuffer->Bind();
		}
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
		m_VertexBuffer->Unbind();
		m_IndexBuffer->Unbind();
	}
}