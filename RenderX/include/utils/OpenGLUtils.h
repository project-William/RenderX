#pragma once
#include "..//..//Common.h"

namespace renderx::utils
{
	struct REN_API OpenGLUtils
	{
		static void OpenGLEnableDepth();

		static void OpenGLDepthFunc();

		static void OpenGLEnableSeamlessCubemap();

	};
}