#pragma once
#include "..//graphics/render/RenderObject.h"
#include "..//graphics/texture/CubemapTexture.h"
#include "Entity.h"

namespace renderx {
	namespace entity {

		using CubemapTexVector=std::vector<std::vector<std::string>>;

		struct REN_API CubemapFaces
		{
			std::vector<std::string> m_faces =
			{
				"texture/ame_iceflats/iceflats_ft.tga",
				"texture/ame_iceflats/iceflats_bk.tga",
				"texture/ame_iceflats/iceflats_dn.tga",
				"texture/ame_iceflats/iceflats_up.tga",
				"texture/ame_iceflats/iceflats_rt.tga",
				"texture/ame_iceflats/iceflats_lf.tga",
			};

			std::vector<std::string> m_faces1 =
			{

			};

			std::vector<std::string> m_faces2 =
			{

			};

			std::vector<std::string> m_faces3 =
			{

			};
							
		};


		class REN_API RenderSkybox:public Entity
		{
		public:
			RenderSkybox(const std::string& vsfile, const std::string& fsfile, const std::vector<std::string>& faces);
			~RenderSkybox();

			void EnableObject() override;
			void DisableObject() override;
			void Draw(const graphics::WinData& windata, FPSCamera* camera);
			void OnUpdate() override;
			
			inline graphics::Transformation& GetTransRef() { return m_Trans; }
			inline graphics::RenderData* GetRenderDataRef() { return m_RenderData; }
			inline std::shared_ptr<graphics::CubemapTexture>& GetCubemapRef() { return m_Cubemap; }
			
		private:
			
			std::shared_ptr<graphics::CubemapTexture> m_Cubemap;
			graphics::Transformation m_Trans;
			graphics::RenderData* m_RenderData;
			CubemapTexVector m_CubemapFaces;
			
			std::vector<float> m_SkyboxVertices= {
				-1.0f,  1.0f, -1.0f,
				-1.0f, -1.0f, -1.0f,
				 1.0f, -1.0f, -1.0f,
				 1.0f, -1.0f, -1.0f,
				 1.0f,  1.0f, -1.0f,
				-1.0f,  1.0f, -1.0f,

				-1.0f, -1.0f,  1.0f,
				-1.0f, -1.0f, -1.0f,
				-1.0f,  1.0f, -1.0f,
				-1.0f,  1.0f, -1.0f,
				-1.0f,  1.0f,  1.0f,
				-1.0f, -1.0f,  1.0f,

				 1.0f, -1.0f, -1.0f,
				 1.0f, -1.0f,  1.0f,
				 1.0f,  1.0f,  1.0f,
				 1.0f,  1.0f,  1.0f,
				 1.0f,  1.0f, -1.0f,
				 1.0f, -1.0f, -1.0f,

				-1.0f, -1.0f,  1.0f,
				-1.0f,  1.0f,  1.0f,
				 1.0f,  1.0f,  1.0f,
				 1.0f,  1.0f,  1.0f,
				 1.0f, -1.0f,  1.0f,
				-1.0f, -1.0f,  1.0f,

				-1.0f,  1.0f, -1.0f,
				 1.0f,  1.0f, -1.0f,
				 1.0f,  1.0f,  1.0f,
				 1.0f,  1.0f,  1.0f,
				-1.0f,  1.0f,  1.0f,
				-1.0f,  1.0f, -1.0f,

				-1.0f, -1.0f, -1.0f,
				-1.0f, -1.0f,  1.0f,
				 1.0f, -1.0f, -1.0f,
				 1.0f, -1.0f, -1.0f,
				-1.0f, -1.0f,  1.0f,
				 1.0f, -1.0f,  1.0f
			};
		};
	}
}