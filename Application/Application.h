#pragma once
#include "RenderX.h"

using namespace renderx;

class Application :Configuration
{
public:
	Application();
	~Application();

	void Run();

private:
	std::shared_ptr<entity::Camera> m_Camera;

	std::shared_ptr<graphics::Sphere> m_Sphere;
	std::shared_ptr<graphics::Quad> m_Quad;

	std::shared_ptr<graphics::Shader> shader;
	std::shared_ptr<graphics::Shader> m_PbrShader;
	std::shared_ptr<graphics::Shader> m_EquirectangularToCubemapShader;
	std::shared_ptr<graphics::Shader> m_IrradianceShader;
	std::shared_ptr<graphics::Shader> m_PrefilterShader;
	std::shared_ptr<graphics::Shader> m_BrdfShader;
	std::shared_ptr<graphics::Shader> m_BackgroundShader;


	std::shared_ptr<graphics::Block> m_Block;

	std::shared_ptr<graphics::Framebuffer> m_Framebuffer;

	//texture
	graphics::Texture hdrtexture;
	graphics::Texture cubemap;
	graphics::Texture prefilter;
	graphics::Texture brdftexture;
	graphics::Texture irradianceMap;

	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);
	glm::mat4 model = glm::mat4(1.0f);
	//managers
	manager::ShaderManager m_ShaderManager;
	manager::TextureManager m_TextureManager;
	manager::RendererManager m_RendererManager;

	//scene
	std::shared_ptr<Scene> m_Scene;


	//ui
	std::shared_ptr<ui::ImguiWindow> m_Imgui;
	std::shared_ptr<ui::SettingWindow> m_SetWin;

	ImVec4 albedoColor;

private:
	std::shared_ptr<Test> m_Test;
	

	float deltaTime = 0, lastFrame = 0;


	glm::vec3 lightPositions[4] = {
			glm::vec3(-10.0f,  10.0f, 10.0f),
			glm::vec3(10.0f,  10.0f, 10.0f),
			glm::vec3(-10.0f, -10.0f, 10.0f),
			glm::vec3(10.0f, -10.0f, 10.0f),
	};
	glm::vec3 lightColors[4] = {
		glm::vec3(300.0f, 300.0f, 300.0f),
		glm::vec3(300.0f, 300.0f, 300.0f),
		glm::vec3(300.0f, 300.0f, 300.0f),
		glm::vec3(300.0f, 300.0f, 300.0f)
	};

};