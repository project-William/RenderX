#include "manager/RendererManager.h"
#include "graphics/render/Block.h"
#include "graphics/render/Sphere.h"
#include "graphics/render/Model.h"

namespace renderx
{
	namespace manager
	{
		void RendererManager::SubmitRenderer(std::shared_ptr<graphics::Renderer> renderer)
		{
			m_Renderers.push_back(renderer);
			if (renderer->GetName() == "Block")
			{
				m_BasicShape_Block = renderer;
			}
			else if (renderer->GetName() == "Sphere")
			{
				m_BasicShape_Sphere = renderer;
			}
			else if (renderer->GetName() == "Quad")
			{
				m_BasicShape_Quad = renderer;
			}
		}


		void RendererManager::AddModel(const std::string& filepath)
		{
			std::shared_ptr<graphics::Model> model(new graphics::Model(filepath));
			SubmitRenderer(model);
		}
		



	}
}
