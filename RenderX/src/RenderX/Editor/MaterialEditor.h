#pragma once
#include "../Core/RenderScene.h"

namespace renderx::ui
{
	class MaterialEditor
	{
	public:
		MaterialEditor();
		~MaterialEditor();

		static void RunMatrialEditor(const std::string& rendererName);
		static void ShowTexture(Core::Material& material, unsigned int texture, const std::string& name, bool& isBindTexture);
		
		
		static unsigned int m_DefaultTexture;


		
	};
}