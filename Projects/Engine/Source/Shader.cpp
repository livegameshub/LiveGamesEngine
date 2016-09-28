#include "Shader.h"
#include "Engine.h"

namespace ai
{
	Shader::Shader(glm::u32 id)
		: BasicResource(id)
		, mShaderId(0)
		, mShaderType(0)
	{
	}

	Shader::Shader(glm::u32 id, glm::u32 shaderType)
		: BasicResource(id)
		, mShaderId(0)
		, mShaderType(shaderType)
	{
	}

	Shader::Shader(glm::u32 id, glm::u32 shaderType, const std::string& file)
		: BasicResource(id, file)
		, mShaderId(0)
		, mShaderType(shaderType)
	{
	}

	Shader::~Shader()
	{
	}

	void Shader::Compile() const
	{
		glCompileShader(mShaderId);
	}

	void Shader::SetShaderType(glm::u32 type)
	{
		mShaderType = type;
	}

	glm::u32 Shader::GetShaderType() const
	{
		return mShaderType;
	}

	glm::u32 Shader::GetShaderId() const
	{
		return mShaderId;
	}

	#if (defined _DEBUG || !defined WINDOWS_BUILD)

	bool Shader::CompilationStatus() const
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

	#endif

	bool Shader::Create()
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

		Compile();

		#if (defined _DEBUG || !defined WINDOWS_BUILD)

		return CompilationStatus();
		#else
		return true;
		#endif
	}

	bool Shader::Release()
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
