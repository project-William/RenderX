#include "graphics/OpenGL/BufferLayout.h"

namespace renderx::graphics
{

	BufferLayout::~BufferLayout()
	{
	}

	BufferLayout::BufferLayout(const std::initializer_list<BufferElement> elements)
		:m_Elements(elements), m_Stride(0)
	{
		for (auto& ele : m_Elements)
		{
			m_Stride += ele.GetElementSize();
		}
	}
}