#include "Program.h"
#include "Shader.h"
#include "Matrix4.h"
#include "Vector3.h"

#include <algorithm>

namespace ai
{
	Program::Program(u32 id)
		: BasicResource(id)
		, mProgramId(0)
	{
	}

	Program::~Program()
	{
	}

	void Program::User() const
	{
		glUseProgram(mProgramId);
	}

	void Program::Link() const
	{
		glLinkProgram(mProgramId);
	}

	void Program::AttachShader(Shader* shader) const
	{
		glAttachShader(mProgramId, shader->GetShaderId());
	}

	void Program::DetachShader(Shader* shader) const
	{
		glDetachShader(mProgramId, shader->GetShaderId());
	}

	void Program::AddShader(Shader* shader)
	{
		if (shader)
		{
			mShaders.push_back(shader);
		}
	}

	void Program::RemoveShader(u32 type)
	{
		for (auto it = mShaders.begin(); it != mShaders.end(); ++it)
		{
			if ((*it)->GetShaderType() == type)
			{
				mShaders.erase(it);

				break;
			}
		}
	}

	void Program::AddUniform(const std::string& uniform_name)
	{
		#ifdef _DEBUG

		auto it = mUniforms.find(uniform_name);

		if (it != mUniforms.end())
		{
			return;
		}

		#endif

		mUniforms.insert({ uniform_name, -1 });
	}

	void Program::AddUniforms(const std::vector<std::string>& uniforms)
	{
		for (auto uniform_name : uniforms)
		{
			AddUniform(uniform_name);
		}
	}

	void Program::SetUniform(const std::string& uniform_name, const Matrix4& matrix) const
	{
		glUniformMatrix4fv(mUniforms.at(uniform_name), 1, GL_FALSE, &matrix.data[0]);
	}

	void Program::SetUniform(const std::string& uniform_name, const Vector3& vector) const
	{
		glUniform3f(mUniforms.at(uniform_name), vector.x, vector.y, vector.z);
	}

	void Program::SetUniform(const std::string& uniform_name, f32 value)
	{
		glUniform1f(mUniforms.at(uniform_name), value);
	}

	void Program::SetUniform(const std::string& uniform_name, i32 value)
	{
		glUniform1i(mUniforms.at(uniform_name), value);
	}

	i32 Program::GetAttributeLocation(u32 index) const
	{
		#ifdef _DEBUG

		if (index >= COUNT)
		{
			return -1;
		}

		#endif

		return mAttributes[index];
	}

	const i32* Program::GetAttributes() const
	{
		return mAttributes;
	}

	u32 Program::GetProgramId() const
	{
		return mProgramId;
	}

	#ifdef _DEBUG

	bool Program::LinkingStatus() const
	{
		i32 result;

		glGetProgramiv(mProgramId, GL_LINK_STATUS, &result);

		if (!result)
		{
			i32 info;

			glGetProgramiv(mProgramId, GL_INFO_LOG_LENGTH, &info);

			std::vector<char> error(std::max(info, i32(1)));
			glGetProgramInfoLog(mProgramId, info, nullptr, &error[0]);

			fprintf(stdout, "%s\n", &error[0]);

			return false;
		}

		return true;
	}

	#endif

	bool Program::Create()
	{
		mProgramId = glCreateProgram();

		if (!mProgramId)
		{
			return false;
		}

		for (auto shader : mShaders)
		{
			if (shader->Load())
			{
				AttachShader(shader);
			}
		}

		Link();

		#ifdef _DEBUG

		if (!LinkingStatus())
		{
			return false;
		}

		#endif

		InitAttributes();
		InitUniforms();

		return true;
	}

	bool Program::Release()
	{
		if (!mProgramId)
		{
			return false;
		}

		for (auto shader : mShaders)
		{
			if (shader->GetReferencesCounter())
			{
				DetachShader(shader);

				shader->Unload();
			}
		}

		glDeleteProgram(mProgramId);

		mProgramId = 0;

		return true;
	}

	void Program::InitAttributes()
	{
		mAttributes[POSITION_INDEX] = glGetAttribLocation(mProgramId, "a_position");
		mAttributes[TEXTURE_INDEX] = glGetAttribLocation(mProgramId, "a_uv");
		mAttributes[NORMAL_INDEX] = glGetAttribLocation(mProgramId, "a_normal");
	}

	void Program::InitUniforms()
	{
		for (auto it : mUniforms)
		{
			if (it.second == -1)
			{
				std::string key = it.first;

				mUniforms.at(key) = glGetUniformLocation(mProgramId, key.c_str());
			}
		}
	}
}
