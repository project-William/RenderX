#pragma once
#include "..//..//..//Core.h"

namespace renderx {
	namespace graphics {

		struct REN_API Buffer
		{
			Buffer()
			{

			}
			virtual ~Buffer()
			{

			}

			virtual void Bind()const {}
			virtual void Unbind()const {}
		};

		
	}
}