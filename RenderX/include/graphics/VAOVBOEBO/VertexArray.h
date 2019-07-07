#pragma once
#include "VertexBuffer.h"

namespace renderx {
	namespace graphics {

		class REN_API VertexArray
		{
		private:
			GLuint m_VertexArray;
			VertexBuffer* m_Vbuffer;

		public:
			VertexArray();
			VertexArray(unsigned int size, const void* data);
			~VertexArray();

			void AddBuffer(unsigned int stride, const void* offset);
			
			void BindVertexArray()const;
			void UnbindVertexArray()const;


		};
		
	}
}