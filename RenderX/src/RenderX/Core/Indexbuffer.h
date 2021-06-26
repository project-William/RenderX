#pragma once

namespace renderx::Core
{
	class IndexBuffer
	{
	public:
		IndexBuffer(GLsizeiptr size, const void* data);
		~IndexBuffer();


	private:
		uint32_t m_IndexBufferID;
	};
}