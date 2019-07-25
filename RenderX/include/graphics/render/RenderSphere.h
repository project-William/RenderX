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
			void RenderProperties() override;
			void Color(const WinData& windata);


			inline const unsigned int GetXSegments()const { return X_SEGMENTS; }
			inline const unsigned int GetYSegments()const { return Y_SEGMENTS; }
			inline const unsigned int GetIndexCount()const { return m_IndexCount; }
		
			void Position(const glm::vec3& position) override;
			void Rotation(const float radians, const glm::vec3& axis) override;
			void Scale(const float scale) override;
		private:
			Transformation m_Trans;
			unsigned int m_IndexCount;
			const unsigned int X_SEGMENTS;
			const unsigned int Y_SEGMENTS;
			const float m_PI;
			std::vector<float> m_SphereData;
			RenderData* m_RenderData;
		private:
			void CreateSphere();
		};

	}
}