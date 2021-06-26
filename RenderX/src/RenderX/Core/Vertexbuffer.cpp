#include "pch.h"
#include "Vertexbuffer.h"

namespace renderx::Core
{

	VertexBuffer::VertexBuffer()
	{
		glGenBuffers(1, &m_BufferID);
	}

	VertexBuffer::VertexBuffer(GLsizeiptr size, const void* data)
	{
		glGenBuffers(1, &m_BufferID);
		glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}

	void VertexBuffer::SetVertexBuffer(GLsizeiptr size, const void* data, bool addIndices)
	{
		if (addIndices)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
		}
		else
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
			glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
		}
	}


	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_BufferID);
	}

	void VertexBuffer::BindVertexBuffer()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
	}

	void VertexBuffer::UnbindVertexBuffer()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}




}