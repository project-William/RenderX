#pragma once
#include "..//Core.h"


namespace renderx {
	namespace graphics {
		class REN_API Buffer 
		{
		public:
			Buffer();
			virtual ~Buffer();

			virtual void Bind()const = 0;
			virtual void Unbind()const = 0;

		};
	}
}