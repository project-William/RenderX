#pragma once
#include "RenderObject.h"

namespace renderx {
	namespace graphics {

		class REN_API RenderModel:public RenderObject
		{
		private:

		public:
			RenderModel();
			~RenderModel();

			void BindObject()const override;
			void UnbindObject()const override;
			void Draw();

		};

	}
}