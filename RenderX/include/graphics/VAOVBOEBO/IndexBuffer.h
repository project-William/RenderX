#pragma once
#include "Buffer.h"


namespace renderx {
	namespace graphics {

		class REN_API IndexBuffer :public Buffer
		{
		private:
			GLuint m_IndexBufferID;
		public:
			IndexBuffer();
			~IndexBuffer();

			inline GLuint GetBuffer()const override { return m_IndexBufferID; }

			void Bind()const override;
			void Unbind()const override;


			void AddData(unsigned int size, const void* data)override;
		};



	}
}