#include "utils/OpenGLUtils.h"

namespace renderx::utils
{
	void OpenGLUtils::OpenGLEnableDepth()
	{
		glEnable(GL_DEPTH_TEST);
	}

	void OpenGLUtils::OpenGLDepthFunc()
	{
		glDepthFunc(GL_LEQUAL);
	}

	void OpenGLUtils::OpenGLEnableSeamlessCubemap()
	{
		glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	}

	void OpenGLUtils::OpenGLLinePolygonMode()
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	void OpenGLUtils::OpenGLFillPolygonMode()
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}