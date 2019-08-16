#pragma once
#include "..//..//..//Core.h"

namespace renderx {
	namespace graphics {
	
		
		class REN_API RenderLight
		{
		public:
			RenderLight() {}
			virtual ~RenderLight() {}

			virtual inline glm::vec3 GetLightPosition()const = 0;
			virtual inline glm::vec3 GetLightColor() const = 0;
			virtual inline float GetShineness()const = 0;
			virtual inline float& GetShinenessRef() = 0;
			virtual inline glm::vec3& GetLightPositionRef() = 0;
			virtual inline glm::vec3& GetLightColorRef() = 0;
			virtual inline glm::vec3& GetLightDirectionRef() = 0;
		};


	}
}