#pragma once

namespace renderx::Core
{
	
	class VertexBuffer
	{
	private:
		uint32_t m_BufferID;
	public:
		VertexBuffer();
		VertexBuffer(GLsizeiptr size,const void* data);
		~VertexBuffer();

		void SetVertexBuffer(GLsizeiptr size, const void* data, bool addIndices);
		void BindVertexBuffer();
		void UnbindVertexBuffer();
		uint32_t GetVertexBufferID()const { return m_BufferID; }
	};
}