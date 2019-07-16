#pragma once
#include "..//Buffer.h"

#include "BufferLayout.h"

namespace renderx {
	namespace graphics {

		class REN_API VertexBuffer :public Buffer
		{
		private:
			GLuint m_VertexBuffer;
		public:
			VertexBuffer();
			VertexBuffer(unsigned int size, const void* data);
			~VertexBuffer();

			void Bind()const override;
			void Unbind()const override;
		};
	}
}