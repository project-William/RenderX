#pragma once
#include "RenderObject.h"
#include "..//texture/CubemapTexture.h"

namespace renderx {
	namespace graphics {

		struct REN_API CubemapFaces
		{
			std::vector<std::string> m_faces =
			{
				"texture/ame_iceflats/iceflats_ft.tga",
				"texture/ame_iceflats/iceflats_bk.tga",
				"texture/ame_iceflats/iceflats_up.tga",
				"texture/ame_iceflats/iceflats_dn.tga",
				"texture/ame_iceflats/iceflats_lf.tga",
				"texture/ame_iceflats/iceflats_rt.tga"
			};
			
		};


		class REN_API RenderSkybox
		{
		public:
			RenderSkybox(const std::string& vsfile, const std::string& fsfile);
			~RenderSkybox();

			void EnableObject() const override;
			void DisableObject() const override;
			void Draw(const WinData& windata);
			void OnUpdate() override;
		private:
			CubemapFaces m_Faces;
			std::unique_ptr<CubemapTexture> m_Cubemap;
			Transformation m_Trans;
			RenderData* m_RenderData;
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