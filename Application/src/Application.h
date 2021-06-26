#pragma once
#include "RenderX.h"

using namespace renderx;


class Application:public base::BasicConfig
{
public:

	Application()
	{
		m_EnvironmentEditor = ui::EnvironmentEditor::Get();
		m_PropEditor = ui::RendererPropEditor::Get();
		m_ScenePanel = ui::SceneHierarchyPanel::Get();
		m_Skybox = Core::Skybox::Get();
		
	}

	void InitApp();

	~Application()
	{

	}
	void Run();

private:
	std::shared_ptr<ui::RendererPropEditor> m_PropEditor;
	std::shared_ptr<ui::SceneHierarchyPanel> m_ScenePanel;
	std::shared_ptr<ui::ViewportWindow> m_ViewportWin;
	ui::MaterialEditor m_MaterialEditor;
	std::shared_ptr<ui::EnvironmentEditor> m_EnvironmentEditor;
	std::shared_ptr<Core::Skybox> m_Skybox;
};