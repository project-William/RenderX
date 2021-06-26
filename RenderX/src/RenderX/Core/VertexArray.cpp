#include "pch.h"
#include "VertexArray.h"


namespace renderx::Core
{
	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &m_ArrayID);
		glBindVertexArray(m_ArrayID);
	}


	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_ArrayID);
	}

	void VertexArray::BindVertexArray()
	{
		glBindVertexArray(m_ArrayID);
	}

	void VertexArray::UnbindVertexArray()
	{
		glBindVertexArray(0);
	}

	void VertexArray::SubmitBufferLayout(std::initializer_list<Element> eleList)
	{
		m_Element = eleList;
	}


}