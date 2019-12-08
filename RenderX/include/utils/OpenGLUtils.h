#pragma once
#include "..//Common.h"

namespace renderx::utils
{
	struct OpenGLUtils
	{
		static void OpenGLEnableDepth();

		static void OpenGLDepthFunc();

		static void OpenGLEnableSeamlessCubemap();

	};
}