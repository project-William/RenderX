#pragma once
#include "..//..//Core.h"

namespace renderx {
	namespace graphics {

		class REN_API RenderScene
		{
		public:
			RenderScene();
			~RenderScene();

			static void SceneBegin();
			static void SceneEnd();

		private:


		};

	}
}