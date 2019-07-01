#pragma once
#include "..//Core.h"

#include "IndexBuffer.h"
#include "VertexBuffer.h"

namespace renderx {
	namespace graphics {
		class REN_API VertexArray
		{
		private:
			//raw pointer
			Buffer* m_VBuffer;
			Buffer* m_Ebuffer;

			GLuint m_VertexArray;

		public:

			VertexArray();
			~VertexArray();

			void SetVbuffer();
			void SetEbuffer();


			void Bind()const;
			void Unbind()const;

			void SetupVertexArray(unsigned int stride, const void* offset);


		};
	}
}
