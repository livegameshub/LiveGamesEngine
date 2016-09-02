#include "Graphics.h"

namespace ai
{
	i32 Graphics::smMinorApiVersion;
	i32 Graphics::smMajorApiVersion;
	
	i32 Graphics::smMajorApiShaderVersion;
	i32 Graphics::smMinorApiShaderVersion;
	
	i32 Graphics::smMaxSamples;

	bool Graphics::InitApi()
	{
		return glewInit() == GLEW_OK ? true : false;
	}

	void Graphics::CheckApiVersion()
	{
		glGetIntegerv(GL_MAJOR_VERSION, &smMajorApiVersion);
		glGetIntegerv(GL_MINOR_VERSION, &smMinorApiVersion);

		const u8* glsl = glGetString(GL_SHADING_LANGUAGE_VERSION);

		if (glsl)
		{
			smMajorApiShaderVersion = std::atoi(reinterpret_cast<const char*>(&glsl[0]));
			smMinorApiShaderVersion = std::atoi(reinterpret_cast<const char*>(&glsl[2]));
		}
	}

	void Graphics::CheckMaxSamples()
	{
		glGetIntegerv(GL_MAX_SAMPLES, &smMaxSamples);
	}

	i32 Graphics::GetMajorApiVersion()
	{
		return smMajorApiVersion;
	}

	i32 Graphics::GetMinorApiVersion()
	{
		return smMinorApiVersion;
	}

	i32 Graphics::GetMajorApiShaderVersion()
	{
		return smMajorApiShaderVersion;
	}

	i32 Graphics::GetMinorApiShaderVersion()
	{
		return smMinorApiShaderVersion;
	}
}
