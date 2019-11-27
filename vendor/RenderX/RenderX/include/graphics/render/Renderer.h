#pragma once
#include "..//..//..//Common.h"
#include "..//VAOVBOEBO/VertexArray.h"

namespace renderx::graphics
{

	enum class REN_API RendererType
	{
		BLOCK, SPHERE, MODEL
	};


	struct REN_API Renderer
	{
		Renderer() {};
		virtual ~Renderer() {};

		virtual std::string GetName() { return ""; }
		virtual void Draw() {}
		virtual void BindVAO() {}
	};
}