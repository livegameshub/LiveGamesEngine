#include "Shader.h"
#include "Engine.h"

namespace lg
{
	Shader::Shader(u32 id, const string& file)
		: Resource(id, file)
		, mShaderId(0)
		, mShaderType(-1)
	{
	}

	Shader::~Shader()
	{
	}

	void Shader::compile() const
	{
		glCompileShader(mShaderId);
	}

	u32 Shader::getShaderType() const
	{
		return mShaderType;
	}

	u32 Shader::getShaderId() const
	{
		return mShaderId;
	}

	#if (defined _DEBUG || !defined WINDOWS_BUILD)

	bool Shader::compilationStatus() const
	{
		i32 result;

		glGetShaderiv(mShaderId, GL_COMPILE_STATUS, &result);

		if (!result)
		{
			i32 info;

			glGetShaderiv(mShaderId, GL_INFO_LOG_LENGTH, &info);

			vector<char> error(info);
			glGetShaderInfoLog(mShaderId, info, nullptr, &error[0]);

			fprintf(stdout, "%s\n", &error[0]);

			return false;
		}

		return true;
	}

	#endif // (defined _DEBUG || !defined WINDOWS_BUILD)

	bool Shader::create()
	{
		ifstream read(ASSETS_PATH + mResourceFile, ios::in);

		if (!read.is_open())
		{
			return false;
		}

		/* check the shader type by file extension - begin */

		string output_file = mResourceFile.substr(mResourceFile.find('.'));
		
		if (output_file == ".vs")
		{
			mShaderType = VERTEX;
		}
		else if (output_file == ".fs")
		{
			mShaderType = FRAGMENT;
		}

		/* check the shader type by file extension - end */

		mShaderId = glCreateShader(mShaderType);

		if (!mShaderId)
		{
			return false;
		}

		stringstream stream;
		stream << read.rdbuf();
		read.close();

		string source = stream.str();
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
