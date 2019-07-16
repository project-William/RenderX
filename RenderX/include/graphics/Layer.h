#pragma once
#include "..//..//Core.h"
#include "Window.h"

namespace renderx {
	namespace graphics {

		class REN_API Layer
		{
		public:
			Layer();
			virtual ~Layer();

			virtual void OnAttach();
			virtual void OnDetach();
			virtual void OnImguiLayer();
			
		};

	}
}