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