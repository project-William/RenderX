#include "pch.h"
#include "SceneHierarchyPanel.h"
#include "../Utils/FileDialogs.h"
#include "../Core/RenderScene.h"

namespace renderx::ui
{
    std::shared_ptr<SceneHierarchyPanel> SceneHierarchyPanel::s_Instance;

    std::shared_ptr<SceneHierarchyPanel>& SceneHierarchyPanel::Get()
    {
        if (!s_Instance)
        {
            s_Instance = std::shared_ptr<SceneHierarchyPanel>(new SceneHierarchyPanel());
        }
        return s_Instance;
    }


    SceneHierarchyPanel::SceneHierarchyPanel()
        :m_RendererMapRef(Core::RenderScene::Get()->GetRenderersMapRef())
	{
        m_RendererName = "";
	}

	SceneHierarchyPanel::~SceneHierarchyPanel()
	{

	}

	void SceneHierarchyPanel::RunSceneHierarchyPanel()
	{
		if (ImGui::Begin("Scene Panel"))
		{

			if (ImGui::Button("Add Model"))
			{
                
				std::string path = utils::FileDialogs::OpenFile("");
                Core::RenderScene::Get()->SubmitRenderer(path);
			}

            int index = 0;
            static int selected = -1;
            for (auto iter = Core::RenderScene::Get()->GetRenderersNameInSceneRef().begin(); iter != Core::RenderScene::Get()->GetRenderersNameInSceneRef().end(); iter++)
            {
                ImGui::Bullet(); 
                if (ImGui::Selectable(iter->first.c_str(), selected == index))
                {
                    selected = index;
                    m_RendererName = iter->first;
                }
                
                index++;
            }

            ImGui::Separator();
			ImGui::End();

		}
	}
}