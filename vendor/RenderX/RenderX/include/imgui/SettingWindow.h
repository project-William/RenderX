#pragma once
#include "ImguiWindow.h"
#include "..//Scene.h"
#include "..//entity/Camera.h"

namespace renderx::ui
{
	class REN_API SettingWindow
	{
	public:
		SettingWindow();
		~SettingWindow();
		void Begin();
		void DockSpace();
		void FPSWindow(double duration);
		void End();
		void Demo();


		void RendererWindow();
		void AttribWindow(std::shared_ptr<entity::Camera> cam);
		void EnvirWindow();
		void TexturePart();
		void EnvirPart();

		void OnUpdate();

		void Test();


	private:
		bool m_DockOpen;

		struct Boolean
		{
			bool isChoose = false;
		};

		std::list<Boolean> m_RendererChoose;

		std::list<RenderList>::reverse_iterator m_Riterator;
		std::list<RenderList>::iterator m_Iterator;

		bool m_QuadChoose = false;
		bool m_BlockChoose = false;
		bool m_SphereChoose = false;
		bool m_ModelChoose = false;

		std::shared_ptr<Scene> m_TempScene;

		glm::vec4 temp_Albedo;

		bool m_UseColor = true;
	};
}