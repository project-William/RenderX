#include "graphics/VAOVBOEBO/BufferLayout.h"

namespace renderx {
	namespace graphics {

		BufferLayout::BufferLayout()
			:m_Stride(0)
		{

		}

		BufferLayout::~BufferLayout()
		{

		}

		BufferLayout::BufferLayout(const std::initializer_list<BufferElement> elements)
			:m_Elements(elements) ,m_Stride(0)
		{
			GetStride();
		}

		void BufferLayout::GetStride()
		{
			for (auto& ele : m_Elements)
			{
				m_Stride += ele.GetElementSize();
			}
		}



	}
}