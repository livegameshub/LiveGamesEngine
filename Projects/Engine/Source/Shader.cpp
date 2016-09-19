#include "Shader.h"
#include "Engine.h"

namespace ai
{
	Shader::Shader(u32 id)
		: BasicResource(id)
		, mShaderId(0)
		, mShaderType(0)
	{
	}

	Shader::Shader(u32 id, u32 shaderType)
		: BasicResource(id)
		, mShaderId(0)
		, mShaderType(shaderType)
	{
	}

	Shader::Shader(u32 id, u32 shaderType, const std::string& file)
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

	void Shader::SetShaderType(u32 type)
	{
		mShaderType = type;
	}

	u32 Shader::GetShaderType() const
	{
		return mShaderType;
	}

	u32 Shader::GetShaderId() const
	{
		return mShaderId;
	}

	#ifdef _DEBUG

	bool Shader::CompilationStatus() const
	{
		i32 result;

		glGetShaderiv(mShaderId, GL_COMPILE_STATUS, &result);

		if (!result)
		{
			i32 info;

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
		std::ifstream read(Engine::GetAssetsPath() + mResourceFile, std::ios::in);

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

		#ifdef _DEBUG
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
