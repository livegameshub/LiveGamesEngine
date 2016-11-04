#include "Graphics.h"

namespace lg
{
	i32 Graphics::smMinorApiVersion;
	i32 Graphics::smMajorApiVersion;

	i32 Graphics::smMajorApiShaderVersion;
	i32 Graphics::smMinorApiShaderVersion;

	i32 Graphics::smMaxSamples;

	bool Graphics::initApi()
	{
		return glewInit() == GLEW_OK ? true : false;
	}

	void Graphics::checkApiVersion()
	{
		glGetIntegerv(GL_MAJOR_VERSION, &smMajorApiVersion);
		glGetIntegerv(GL_MINOR_VERSION, &smMinorApiVersion);

		const u8* glsl = glGetString(GL_SHADING_LANGUAGE_VERSION);

		if (glsl)
		{
			smMajorApiShaderVersion = atoi(reinterpret_cast<const char*>(&glsl[0]));
			smMinorApiShaderVersion = atoi(reinterpret_cast<const char*>(&glsl[2]));
		}
	}

	void Graphics::checkMaxSamples()
	{
		glGetIntegerv(GL_MAX_SAMPLES, &smMaxSamples);
	}

	i32 Graphics::getMajorApiVersion()
	{
		return smMajorApiVersion;
	}

	i32 Graphics::getMinorApiVersion()
	{
		return smMinorApiVersion;
	}

	i32 Graphics::getMajorApiShaderVersion()
	{
		return smMajorApiShaderVersion;
	}

	i32 Graphics::getMinorApiShaderVersion()
	{
		return smMinorApiShaderVersion;
	}
}
