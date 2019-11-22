#pragma once
#include "..//include/Sandbox.h"

#define EVENT_LOG(x,message) { std::cout<<"EVENT:"#x<<" "<<message<<std::endl; }

Sandbox::Sandbox()
{
	m_Window = Window::Create();
	m_Keyboard = utils::Keyboard::Create();
	m_Mouse = utils::Mouse::Create();

	m_Window->SetEventCallback(BIND_EVENT(Sandbox::OnEvent));

	m_Camera = std::shared_ptr<entity::Camera>(new entity::Camera(glm::vec3(0.0f, 0.0f, 10.0f)));

	m_Quad = std::shared_ptr<graphics::Quad>(new graphics::Quad());
	m_Block = std::shared_ptr<graphics::Block>(new graphics::Block());
	m_Sphere = std::shared_ptr<graphics::Sphere>(new graphics::Sphere());
	

	m_PbrShader = std::shared_ptr<graphics::Shader>(new graphics::Shader("shader/pbr.vert", "shader/pbr.frag", graphics::ShaderType::PBRSHADER));
	m_EquirectangularToCubemapShader = std::shared_ptr<graphics::Shader>(new graphics::Shader("shader/cubemap.vert", "shader/equirectangular_to_cubemap.frag",graphics::ShaderType::CUBEMAPSHADER));
	m_IrradianceShader = std::shared_ptr<graphics::Shader>(new graphics::Shader("shader/cubemap.vert", "shader/irradiance_convolution.frag", graphics::ShaderType::IRRDIANCESHADER));
	m_PrefilterShader = std::shared_ptr<graphics::Shader>(new graphics::Shader("shader/cubemap.vert", "shader/prefilter.frag", graphics::ShaderType::PREFILTERSHADER));
	m_BrdfShader = std::shared_ptr<graphics::Shader>(new graphics::Shader("shader/brdf.vert", "shader/brdf.frag", graphics::ShaderType::BRDFSHADER));
	m_BackgroundShader = std::shared_ptr<graphics::Shader>(new graphics::Shader("shader/background.vert", "shader/background.frag", graphics::ShaderType::BACKGROUNDSHADER));


	
	m_Framebuffer = std::shared_ptr<graphics::Framebuffer>(new graphics::Framebuffer());

	// lights
	// ------
	glm::vec3 lightPositions[] = {
		glm::vec3(-10.0f,  10.0f, 10.0f),
		glm::vec3(10.0f,  10.0f, 10.0f),
		glm::vec3(-10.0f, -10.0f, 10.0f),
		glm::vec3(10.0f, -10.0f, 10.0f),
	};
	glm::vec3 lightColors[] = {
		glm::vec3(300.0f, 300.0f, 300.0f),
		glm::vec3(300.0f, 300.0f, 300.0f),
		glm::vec3(300.0f, 300.0f, 300.0f),
		glm::vec3(300.0f, 300.0f, 300.0f)
	};
	int nrRows = 7;
	int nrColumns = 7;
	float spacing = 2.5;
	
	


	hdrtexture.LoadTexture(graphics::TexType::HDR_TEXTURE, "");
	cubemap.LoadTexture(graphics::TexType::ENVCUBEMAP, "");
	irradianceMap.LoadTexture(graphics::TexType::IRRADIANCEMAP, "");
	prefilter.LoadTexture(graphics::TexType::PREFILTERMAP, "");
	brdftexture.LoadTexture(graphics::TexType::BRDFLUT_TEXTURE, "");

	m_PbrShader->BindShaderProgram();
	m_PbrShader->SetInt("irradianceMap", 0);
	m_PbrShader->SetInt("prefilterMap", 1);
	m_PbrShader->SetInt("brdfLUT", 2);


	albedoColor = ImVec4(0.5f, 0.0f, 0.0f, 1.0f);
	m_PbrShader->SetVec4("albedo", albedoColor.x, albedoColor.y, albedoColor.z, albedoColor.w);
	m_PbrShader->SetFloat("ao", 1.0f);

	m_BackgroundShader->BindShaderProgram();
	m_BackgroundShader->SetInt("environmentMap", 0);


	
	
}

Sandbox::~Sandbox()
{

}

void Sandbox::OnEvent(events::Event& e)
{
	bool handled = false;
	events::EventDispatcher dispatcher(e);

	if (e.IsInCategory(events::RX_EVENT_CATEGORY_WINDOW))
	{
		if (!handled)
		{
			handled = dispatcher.Dispatch<events::WindowResizedEvent>(BIND_EVENT(Sandbox::OnWindowResizedEvent));
		}

		if (!handled)
		{
			handled = dispatcher.Dispatch<events::WindowClosedEvent>(BIND_EVENT(Sandbox::OnWindowClosedEvent));
		}

		if (!handled)
		{
			handled = dispatcher.Dispatch<events::WindowMovedEvent>(BIND_EVENT(Sandbox::OnWindowMovedEvent));
		}
	}

	else if (e.IsInCategory(events::RX_EVENT_CATEGORY_KEYBOARD))
	{
		if (!handled)
		{
			handled = dispatcher.Dispatch<events::KeyPressedEvent>(BIND_EVENT(Sandbox::OnKeyPressedEvent));
		}

		if (!handled)
		{
			handled = dispatcher.Dispatch<events::KeyReleasedEvent>(BIND_EVENT(Sandbox::OnKeyReleasedEvent));
		}

	}

	else if (e.IsInCategory(events::RX_EVENT_CATEGORY_MOUSE))
	{
		if (!handled)
		{
			handled = dispatcher.Dispatch<events::MouseMovedEvent>(BIND_EVENT(Sandbox::OnMouseMovedEvent));
		}

		if (!handled)
		{
			handled = dispatcher.Dispatch<events::MousePressedEvent>(BIND_EVENT(Sandbox::OnMouseButtonPressed));
		}

		if (!handled)
		{
			handled = dispatcher.Dispatch<events::MouseRelasedEvent>(BIND_EVENT(Sandbox::OnMouseButtonReleased));
		}

		if (!handled)
		{
			handled = dispatcher.Dispatch<events::MouseScrollEvent>(BIND_EVENT(Sandbox::OnMouseScrollEvent));
		}
	}
}

bool Sandbox::OnWindowResizedEvent(events::WindowResizedEvent& e)
{
	m_Window->OnWindowResized();
	m_WindowResized_flag = true;
	return true;
}

bool Sandbox::OnWindowClosedEvent(events::WindowClosedEvent& e)
{
	m_Running = false;
	return true;
}

bool Sandbox::OnWindowMovedEvent(events::WindowMovedEvent& e)
{
	return true;
}

bool Sandbox::OnMouseButtonPressed(events::MousePressedEvent& e)
{
	utils::Mouse::GetMouseInstance()->OnEvent(e);
	return true;
}

bool Sandbox::OnMouseButtonReleased(events::MouseRelasedEvent& e)
{
	utils::Mouse::GetMouseInstance()->OnEvent(e);
	return true;
}

bool Sandbox::OnMouseMovedEvent(events::MouseMovedEvent& e)
{
	utils::Mouse::GetMouseInstance()->OnEvent(e);
	return true;
}

bool Sandbox::OnMouseScrollEvent(events::MouseScrollEvent& e)
{
	utils::Mouse::GetMouseInstance()->OnEvent(e);
	return true;
}

bool Sandbox::OnKeyPressedEvent(events::KeyPressedEvent& e)
{
	utils::Keyboard::GetKeyboardInstance()->OnEvent(e);
	return true;
}

bool Sandbox::OnKeyReleasedEvent(events::KeyReleasedEvent& e)
{
	utils::Keyboard::GetKeyboardInstance()->OnEvent(e);
	return true;
}
