#pragma once
#include "..//..//..//Common.h"
#include "Renderer.h"

namespace renderx
{
	namespace graphics
	{
		class REN_API Model:public Renderer
		{
		public:
			Model(const std::string& filepath) {}
			~Model() {}
		};
	}
}