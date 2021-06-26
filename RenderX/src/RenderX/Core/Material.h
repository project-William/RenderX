#pragma once
#include "pch.h"

namespace renderx::Core
{
	enum ShaderType
	{
		PBR_COLOR,
		PBR_TEXTURE,
		DEPTH
	};

	struct Material
	{
		
		uint32_t albedoMap = 0;
		uint32_t normalMap = 0;
		uint32_t metallicMap = 0;
		uint32_t roughnessMap = 0;
		uint32_t aoMap = 0;

		float roughness = 1.0f;
		float metallic = 1.0f;

		int switchShader = ShaderType::PBR_COLOR;

		glm::vec3 color= glm::vec3(1.0f, 1.0f, 1.0f);

	};
}