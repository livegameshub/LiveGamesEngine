#include "Shader.h"
#include "Engine.h"

namespace lg
{
	Shader::Shader(glm::u32 id)
		: Resource(id)
		, mShaderId(0)
		, mShaderType(0)
	{
	}

	Shader::Shader(glm::u32 id, glm::u32 shaderType)
		: Resource(id)
		, mShaderId(0)
		, mShaderType(shaderType)
	{
	}

	Shader::Shader(glm::u32 id, glm::u32 shaderType, const std::string& file)
		: Resource(id, file)
		, mShaderId(0)
		, mShaderType(shaderType)
	{
	}

	Shader::~Shader()
	{
	}

	void Shader::compile() const
	{
		glCompileShader(mShaderId);
	}

	void Shader::setShaderType(glm::u32 type)
	{
		mShaderType = type;
	}

	glm::u32 Shader::getShaderType() const
	{
		return mShaderType;
	}

	glm::u32 Shader::getShaderId() const
	{
		return mShaderId;
	}

	#if (defined _DEBUG || !defined WINDOWS_BUILD)

	bool Shader::compilationStatus() const
	{
		glm::i32 result;

		glGetShaderiv(mShaderId, GL_COMPILE_STATUS, &result);

		if (!result)
		{
			glm::i32 info;

			glGetShaderiv(mShaderId, GL_INFO_LOG_LENGTH, &info);

			std::vector<char> error(info);
			glGetShaderInfoLog(mShaderId, info, nullptr, &error[0]);

			fprintf(stdout, "%s\n", &error[0]);

			return false;
		}

		return true;
	}

	#endif // (defined _DEBUG || !defined WINDOWS_BUILD)

	bool Shader::create()
	{
		std::ifstream read(ASSETS_PATH + mResourceFile, std::ios::in);

		if (!read.is_open())
		{
			return false;
		}

		mShaderId = glCreateShader(mShaderType);

		if (!mShaderId)
		{
			return false;
		}

		std::stringstream stream;
		stream << read.rdbuf();
		read.close();

		std::string source = stream.str();
		const char* code_pointer = source.c_str();
		glShaderSource(mShaderId, 1, &code_pointer, nullptr);

		compile();

		#if (defined _DEBUG || !defined WINDOWS_BUILD)

		return compilationStatus();
		#else
		return true;
		#endif // (defined _DEBUG || !defined WINDOWS_BUILD)
	}

	bool Shader::release()
	{
		if (!mShaderId)
		{
			return false;
		}

		glDeleteShader(mShaderId);

		mShaderId = 0;

		return true;
	}
}
