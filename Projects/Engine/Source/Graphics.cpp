#include "Graphics.h"

namespace ai
{
	glm::i32 Graphics::smMinorApiVersion;
	glm::i32 Graphics::smMajorApiVersion;

	glm::i32 Graphics::smMajorApiShaderVersion;
	glm::i32 Graphics::smMinorApiShaderVersion;

	glm::i32 Graphics::smMaxSamples;

	bool Graphics::initApi()
	{
		return glewInit() == GLEW_OK ? true : false;
	}

	void Graphics::checkApiVersion()
	{
		glGetIntegerv(GL_MAJOR_VERSION, &smMajorApiVersion);
		glGetIntegerv(GL_MINOR_VERSION, &smMinorApiVersion);

		const glm::u8* glsl = glGetString(GL_SHADING_LANGUAGE_VERSION);

		if (glsl)
		{
			smMajorApiShaderVersion = std::atoi(reinterpret_cast<const char*>(&glsl[0]));
			smMinorApiShaderVersion = std::atoi(reinterpret_cast<const char*>(&glsl[2]));
		}
	}

	void Graphics::checkMaxSamples()
	{
		glGetIntegerv(GL_MAX_SAMPLES, &smMaxSamples);
	}

	glm::i32 Graphics::getMajorApiVersion()
	{
		return smMajorApiVersion;
	}

	glm::i32 Graphics::getMinorApiVersion()
	{
		return smMinorApiVersion;
	}

	glm::i32 Graphics::getMajorApiShaderVersion()
	{
		return smMajorApiShaderVersion;
	}

	glm::i32 Graphics::getMinorApiShaderVersion()
	{
		return smMinorApiShaderVersion;
	}
}
