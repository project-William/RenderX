#pragma once
#include "Buffer.h"

namespace renderx {
	namespace graphics {

		class REN_API VertexBuffer :public Buffer
		{
		private:
			GLuint m_VertexBufferID;
		public:
			VertexBuffer();
			~VertexBuffer();

			inline GLuint GetBuffer()const override { return m_VertexBufferID; }

			void Bind()const override;
			void Unbind()const override;

			void AddData(unsigned int size, const void* data)override;
		};

	}
}