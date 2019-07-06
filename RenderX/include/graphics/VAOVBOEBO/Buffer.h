#pragma once
#include "..//..//..//Core.h"


namespace renderx {
	namespace graphics {

		class REN_API Buffer 
		{
		public:
			Buffer();
			virtual ~Buffer();

			virtual inline GLuint GetBuffer()const = 0;

			virtual void Bind()const = 0;
			virtual void Unbind()const = 0;

			virtual void AddData(unsigned int size, const void* data) = 0;
			

		};
	}
}