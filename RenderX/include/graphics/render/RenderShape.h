#pragma once
#include "RenderObject.h"

namespace renderx {
	namespace graphics {
		
		class REN_API RenderShape :public RenderObject
		{
		private:
		public:
			RenderShape();
			~RenderShape();

			void BindObject()const override;
			void UnbindObject()const override;

			void Draw();


		};

	}
}