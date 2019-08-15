#pragma once
#include "..//graphics/render/RenderObject.h"


namespace renderx {
	namespace entity {

		class REN_API Flatboard
		{
		public:
			explicit Flatboard(const std::string& vsfile,const  std::string& ffile);
			~Flatboard();

			void EnableObject();
			void DisableObject();

			void Draw(const graphics::WinData& windata, FPSCamera* camera);

			inline std::shared_ptr<graphics::RenderData>& GetRenderDataRef() { return m_RenderData; }
			inline graphics::Transformation& GetTransRef() { return m_Trans; }

		private:
			std::shared_ptr<graphics::Texture> m_AlbedoTex;
			std::shared_ptr<graphics::Texture> m_NormalTex;
			std::shared_ptr<graphics::Texture> m_AOTex;
			std::shared_ptr<graphics::Texture> m_RoughnessTex;
			std::shared_ptr<graphics::Texture> m_MetallicTex;


			std::shared_ptr<graphics::RenderData> m_RenderData;
			graphics::Transformation m_Trans;
			std::vector<float> m_VertexData =
			{
				-10.5f,  0.0f, -10.5f,  0.0f,  1.0f, 0.0f,  1.0f,  0.0f,
				 10.5f,  0.0f, -10.5f,  1.0f,  1.0f, 0.0f,  1.0f,  0.0f,
				 10.5f,  0.0f,  10.5f,  1.0f,  0.0f, 0.0f,  1.0f,  0.0f,
				 10.5f,  0.0f,  10.5f,  1.0f,  0.0f, 0.0f,  1.0f,  0.0f,
				-10.5f,  0.0f,  10.5f,  0.0f,  0.0f, 0.0f,  1.0f,  0.0f,
				-10.5f,  0.0f, -10.5f,  0.0f,  1.0f, 0.0f,  1.0f,  0.0f,
			};

		};
	}
}