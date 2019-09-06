#pragma once
#include "..//..//..//Core.h"
#include "..//Window.h"
namespace renderx {
	namespace ui {

		class REN_API ImguiSceneWindow
		{
		public:
			~ImguiSceneWindow();

			void BeginSceneWindow();
			void EndSceneWindow();

			void SceneWindow(const graphics::WinData& windata,const GLuint& texture);

			inline int GetSceneWinWidth() const { return m_SceneWinWidth; }
			inline int GetSceneWinHeight() const { return m_SceneWinHeight; }

			

			
			static std::shared_ptr<ImguiSceneWindow> Create();
			inline static std::shared_ptr<ImguiSceneWindow>& GetSceneWindowInstance() { return m_Instance; }

		private:
			int m_SceneWinWidth;
			int m_SceneWinHeight;

			ImguiSceneWindow();
			static std::shared_ptr<ImguiSceneWindow> m_Instance;
			
		};


	}
}

