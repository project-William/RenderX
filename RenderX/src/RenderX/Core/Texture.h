#pragma once
#include "pch.h"


namespace renderx::Core
{
	enum TextureType
	{
		TEXTURE2D,
		TEXTURE_CUBE,
	};

	enum TextureKind
	{
		ALBEDO,
		AO,
		NORMAL,
		ROUGHNESS,
		METALLIC
	};


	class TextureLoader
	{
	public:
		//static unsigned int LoadTexture(const std::string& filePath);
		static unsigned int LoadTexture(const std::string& filePath, bool gammaCorrection);
		static std::pair<unsigned int,unsigned int> LoadEnvMap(const std::string& filepath);
		static void UseTexture(int slot, unsigned int texture, TextureType type);
		static void CreateColorAttachment(int width,int height, unsigned int& ColorAttachment);
	};
}