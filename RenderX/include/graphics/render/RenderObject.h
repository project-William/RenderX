#pragma once
#include "Render.h"


namespace renderx {
	namespace graphics {

		struct REN_API ShapeData
		{
			const std::vector<float> triangle = {
				-0.5f,-0.5f,0.0f,
				 0.5f,-0.5f,0.0f,
				 0.0f, 0.5f,0.0f
			};

			const std::vector<float> rectangle = {
				-0.5f,-0.5f,0.0f,
				 0.5f,-0.5f,0.0f,
				-0.5f, 0.5f,0.0f,
				-0.5f, 0.5f,0.0f,
				 0.5f,-0.5f,0.0f,
				 0.5f, 0.5f,0.0f
			};
		};




		class REN_API RenderObject
		{
		public:
			RenderObject();
			virtual ~RenderObject();

			virtual void BindObject() const = 0;
			virtual void UnbindObject() const = 0;
			virtual void Draw() = 0;

		};


	}
}