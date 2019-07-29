#pragma once
#include "..//..//..//Core.h"
#include "..//Window.h"
namespace renderx {
	namespace ui {

		class REN_API ImguiSceneWindow
		{
		public:
			ImguiSceneWindow();
			~ImguiSceneWindow();

			void BeginSceneWindow();
			void EndSceneWindow();

			void SceneWindow(const graphics::WinData& windata,const GLuint& texture);


		};


	}
}

