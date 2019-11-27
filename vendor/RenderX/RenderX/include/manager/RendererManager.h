#pragma once
#include "..//..//Common.h"
#include "..//graphics/render/Renderer.h"

namespace renderx::manager
{
	class REN_API RendererManager
	{
	public:
		~RendererManager() {}
		RendererManager() {}

		RendererManager(const RendererManager&) = delete;
		RendererManager& operator=(const RendererManager&) = delete;

		void SubmitRenderer(std::shared_ptr<graphics::Renderer> renderer);
		void AddModel(const std::string& filepath);

		std::vector<std::shared_ptr<graphics::Renderer>>& GetRendererVecRef() { return m_Renderers; }

		std::shared_ptr<graphics::Renderer> GetBasicShapeBlockPtr() { return m_BasicShape_Block; }
		std::shared_ptr<graphics::Renderer> GetBasicShapeQuadPtr() { return m_BasicShape_Quad; }
		std::shared_ptr<graphics::Renderer> GetBasicShapeSpherePtr() { return m_BasicShape_Sphere; }


	private:
		std::vector<std::shared_ptr<graphics::Renderer>> m_Renderers;
		std::shared_ptr<graphics::Renderer> m_BasicShape_Block;
		std::shared_ptr<graphics::Renderer> m_BasicShape_Quad;
		std::shared_ptr<graphics::Renderer> m_BasicShape_Sphere;
	};
}