#pragma once
#include "..//..//..//Core.h"
#include "..//Window.h"
namespace renderx {
	namespace graphics {

		class REN_API ImguiSceneWindow
		{
		public:
			ImguiSceneWindow();
			~ImguiSceneWindow();

			void BeginSceneWindow();
			void EndSceneWindow();

			void SceneWindow(const WinData& windata,const GLuint& texture);


		};


	}
}

