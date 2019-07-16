#pragma once
#include "..//Buffer.h"


namespace renderx {
	namespace graphics {

		class REN_API IndexBuffer:public Buffer
		{
		private:
			GLuint m_IndexBuffer;
		public:
			IndexBuffer();
			IndexBuffer(unsigned int size ,const void* data);
			~IndexBuffer();

			void Bind()const;
			void Unbind()const;

		};

	}
}