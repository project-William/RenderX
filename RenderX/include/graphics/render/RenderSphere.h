#pragma once
#include "RenderObject.h"

namespace renderx {
	namespace graphics {

		class REN_API RenderSphere :public RenderObject
		{
		public:
			RenderSphere(const std::string& vsfile,const std::string& fsfile);
			~RenderSphere();

			void BindObject() const override;
			void UnbindObject() const override;
			void Draw(const WinData& windata) override;

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


			unsigned int& GetAlbedoTexture() override { return m_AlbedoTex->GetTexRef(); }
			unsigned int& GetAOTexture() override { return m_AOTex->GetTexRef(); }
			unsigned int& GetMetallicTexture() override { return m_MetallicTex->GetTexRef(); }
			unsigned int& GetNormalTexture() override { return m_NormalTex->GetTexRef(); }
			unsigned int& GetRoughnessTexture() override { return m_RoughnessTex->GetTexRef(); }



			void EnableAlbedoTexture() override { m_RenderData->m_AlbedoTex = m_AlbedoTex->GetTexture(); }
			void EnableAOTexture()  override { m_RenderData->m_AOTex= m_AOTex->GetTexture(); }
			void EnableMetallicTexture() override { m_RenderData->m_MetallicTex = m_MetallicTex->GetTexture(); }
			void EnableNormalTexture()  override { m_RenderData->m_NormalTex = m_NormalTex->GetTexture(); }
			void EnableRoughnessTexture()  override { m_RenderData->m_RoughnessTex = m_RoughnessTex->GetTexture(); }


			void DisableAlbedoTexture() override {  m_RenderData->m_AlbedoTex = 0; }
			void DisableAOTexture()  override { m_RenderData->m_AOTex= 0; }
			void DisableMetallicTexture() override { m_RenderData->m_MetallicTex = 0; }
			void DisableNormalTexture()  override { m_RenderData->m_NormalTex = 0; }
			void DisableRoughnessTexture()  override { m_RenderData->m_RoughnessTex = 0; }


			inline const unsigned int GetXSegments()const { return X_SEGMENTS; }
			inline const unsigned int GetYSegments()const { return Y_SEGMENTS; }
			inline const unsigned int GetIndexCount()const { return m_IndexCount; }
		
			inline Transformation& GetTransRef() override { return m_Trans; }
			inline RenderData* GetRenderDataRef() override { return m_RenderData; }
		
		private:
			
			Transformation m_Trans;
			unsigned int m_IndexCount;
			const unsigned int X_SEGMENTS;
			const unsigned int Y_SEGMENTS;
			const float m_PI;
			std::vector<float> m_SphereData;
			RenderData* m_RenderData;
			
			bool m_Open_Camera = false;
			bool m_Phong_model = true;
		private:
			void CreateSphere();
		};

	}
}