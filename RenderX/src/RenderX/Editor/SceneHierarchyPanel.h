#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "../Core/RenderScene.h"

namespace renderx::ui
{
	class SceneHierarchyPanel
	{		 
	public:
		static std::shared_ptr<SceneHierarchyPanel>& Get();
		~SceneHierarchyPanel();

		void RunSceneHierarchyPanel();

		std::string GetRendererName() { return m_RendererName; }
		void SetRendererName(const std::string& name) { m_RendererName = name; }
	
	private:
		SceneHierarchyPanel();

		std::unordered_map<std::string, std::shared_ptr<Core::Model>>& m_RendererMapRef;

		std::string m_RendererName;

		static std::shared_ptr<SceneHierarchyPanel> s_Instance;

		
	};
}