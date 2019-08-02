#pragma once
#include "RenderObject.h"

namespace renderx {
	namespace graphics {

		class REN_API RenderSphere :public RenderObject
		{
		public:
			RenderSphere();
			RenderSphere(const std::string& vsfile,const std::string& fsfile);
			~RenderSphere();

			void BindObject() const override;
			void UnbindObject() const override;
			void Draw(const WinData& windata) override;
			void DrawMultiObj(const WinData& windata);

			void RenderProperties() override;
			void Color(const WinData& windata);
			void SphereSetting(const WinData& windata, entity::FPSCamera* camera);
			void PhongModel(RenderLight* light, entity::FPSCamera* camera);
			inline const unsigned int GetXSegments()const { return X_SEGMENTS; }
			inline const unsigned int GetYSegments()const { return Y_SEGMENTS; }
			inline const unsigned int GetIndexCount()const { return m_IndexCount; }
		
			inline Transformation& GetTrans() override { return m_Trans; }

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