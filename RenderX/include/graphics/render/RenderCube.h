#pragma once
#include "RenderObject.h"

namespace renderx {
	namespace graphics {

		class REN_API RenderCube :public RenderObject
		{
		public:
			RenderCube();
			~RenderCube();
			RenderCube(const std::string& vspath, const std::string& fspath);

			void BindObject() const override;
			void UnbindObject() const override;
			void Draw(const WinData& windata) override;
		
			void Color(const WinData& windata);
			void Draw();
			inline RenderData* GetRenderDataRef() override { return m_RenderData; }
			
			inline Transformation& GetTransRef() override { return m_Trans; }


			std::shared_ptr<graphics::Texture> m_AlbedoTex;
			std::shared_ptr<graphics::Texture> m_NormalTex;
			std::shared_ptr<graphics::Texture> m_AOTex;
			std::shared_ptr<graphics::Texture> m_RoughnessTex;
			std::shared_ptr<graphics::Texture> m_MetallicTex;


			void SetAlbedoTex(const std::string& file) override;
			void SetNormalTex(const std::string& file) override;
			void SetAOTex(const std::string& file) override;
			void SetRoughnessTex(const std::string& file) override;
			void SetMetallicTex(const std::string& file) override;


			void EnableAlbedoTexture() override { m_RenderData->m_AlbedoTex = m_AlbedoTex->GetTexture(); }
			void EnableAOTexture()  override { m_RenderData->m_AOTex = m_AOTex->GetTexture(); }
			void EnableMetallicTexture() override { m_RenderData->m_MetallicTex = m_MetallicTex->GetTexture(); }
			void EnableNormalTexture()  override { m_RenderData->m_NormalTex = m_NormalTex->GetTexture(); }
			void EnableRoughnessTexture()  override { m_RenderData->m_RoughnessTex = m_RoughnessTex->GetTexture(); }


			void DisableAlbedoTexture() override { m_RenderData->m_AlbedoTex = 0; }
			void DisableAOTexture()  override { m_RenderData->m_AOTex = 0; }
			void DisableMetallicTexture() override { m_RenderData->m_MetallicTex = 0; }
			void DisableNormalTexture()  override { m_RenderData->m_NormalTex = 0; }
			void DisableRoughnessTexture()  override { m_RenderData->m_RoughnessTex = 0; }


			unsigned int& GetAlbedoTexture() override { return m_AlbedoTex->GetTexRef(); }
			unsigned int& GetAOTexture() override { return m_AOTex->GetTexRef(); }
			unsigned int& GetMetallicTexture() override { return m_MetallicTex->GetTexRef(); }
			unsigned int& GetNormalTexture() override { return m_NormalTex->GetTexRef(); }
			unsigned int& GetRoughnessTexture() override { return m_RoughnessTex->GetTexRef(); }


		private:
			RenderData *m_RenderData;
			Transformation m_Trans;
		
			std::vector<float> m_CubeData =
			{
				// back face
				-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
				1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
				1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f, // bottom-right         
				1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
			   -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
			   -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, // top-left
				// front face
				-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
				1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, // bottom-right
				1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
				1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
				-1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f, // top-left
				-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
				// left face
				-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
				-1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-left
				-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
				-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
				-1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-right
				-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
				// right face
				1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
				1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
				1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-right         
				1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
				1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
				1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-left     
				// bottom face
				-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
				1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f, // top-left
				1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
				1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
				-1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f, // bottom-right
				-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
				// top face
				-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
				1.0f,  1.0f , 1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
				1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f, // top-right     
				1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
				-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
				-1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f  // bottom-left       
			};

		};
	}
}