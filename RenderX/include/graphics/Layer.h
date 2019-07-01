#pragma once
#include "..//..//Core.h"

namespace renderx {
	namespace graphics {

		class REN_API Layer
		{
		public:
			Layer();
			virtual ~Layer();

			virtual void OnAttach();
			virtual void OnDetach();
			virtual void OnUpdate();
			virtual void OnImguiLayer();
			
		};

	}
}