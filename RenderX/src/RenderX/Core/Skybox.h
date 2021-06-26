#pragma once
#include "pch.h"
#include "Shader.h"	




namespace renderx::Core
{
	class Skybox
	{
	public:
		static std::shared_ptr<Skybox>& Get();
		~Skybox();
		
		bool& IsUseSkyboxRef() { return m_IsUseSkybox; }
		bool& IsUseIrridianceRef() { return m_IsUseIrridiance; }
		void Draw();
		void DrawUseIrrdiance();
	private:
		Skybox();
		static std::shared_ptr<Skybox> s_Instance;

		std::shared_ptr<Shader> m_SkyboxShader;
		bool m_IsUseSkybox;
		bool m_IsUseIrridiance;
	};
}