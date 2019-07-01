#pragma once
#include "graphics/VAOVBOEBO/VertexArray.h"


namespace renderx {
	namespace graphics {
		VertexArray::VertexArray()
			:m_Ebuffer(nullptr), m_VBuffer(nullptr)
		{
			glGenVertexArrays(1, &m_VertexArray);
		}


		VertexArray::~VertexArray()
		{
			delete m_Ebuffer;
			delete m_VBuffer;
			glDeleteVertexArrays(1, &m_VertexArray);
		}

		void VertexArray::SetVbuffer()
		{
			m_VBuffer = new VertexBuffer();
		}

		void VertexArray::SetEbuffer()
		{
			m_Ebuffer = new IndexBuffer();
		}

		void VertexArray::Bind()const
		{
			glBindVertexArray(m_VertexArray);
		}


		void VertexArray::Unbind()const
		{
			glBindVertexArray(0);
		}

		void VertexArray::SetupVertexArray()
		{
		}


	}
}