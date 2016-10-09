#include "ProgramResource.h"
#include "ShaderResource.h"

namespace ai
{
	ProgramResource::ProgramResource(glm::u32 id)
		: BasicResource(id)
		, mProgramId(0)
	{
	}

	ProgramResource::~ProgramResource()
	{
	}

	void ProgramResource::Use() const
	{
		glUseProgram(mProgramId);
	}

	void ProgramResource::Link() const
	{
		glLinkProgram(mProgramId);
	}

	void ProgramResource::AttachShader(ShaderResource* shader) const
	{
		glAttachShader(mProgramId, shader->GetShaderId());
	}

	void ProgramResource::DetachShader(ShaderResource* shader) const
	{
		glDetachShader(mProgramId, shader->GetShaderId());
	}

	void ProgramResource::AddShader(ShaderResource* shader)
	{
		assert(shader != nullptr);

		mShaders.push_back(shader);
	}

	void ProgramResource::RemoveShader(glm::u32 type)
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

	void ProgramResource::AddUniform(const std::string& uniform_name)
	{
		assert(mUniforms.find(uniform_name) == mUniforms.end());

		mUniforms.insert({ uniform_name, -1 });
	}

	void ProgramResource::AddUniforms(const std::vector<std::string>& uniforms)
	{
		for (auto uniform_name : uniforms)
		{
			AddUniform(uniform_name);
		}
	}

	void ProgramResource::SetUniform(const std::string& uniform_name, const glm::mat4& matrix) const
	{
		glUniformMatrix4fv(mUniforms.at(uniform_name), 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void ProgramResource::SetUniform(const std::string& uniform_name, const glm::vec3& vector) const
	{
		glUniform3f(mUniforms.at(uniform_name), vector.x, vector.y, vector.z);
	}

	void ProgramResource::SetUniform(const std::string& uniform_name, glm::f32 value)
	{
		glUniform1f(mUniforms.at(uniform_name), value);
	}

	void ProgramResource::SetUniform(const std::string& uniform_name, glm::i32 value)
	{
		glUniform1i(mUniforms.at(uniform_name), value);
	}

	glm::i32 ProgramResource::GetAttributeLocation(glm::u32 index) const
	{
		assert(index < COUNT);

		return mAttributes[index];
	}

	const glm::i32* ProgramResource::GetAttributes() const
	{
		return mAttributes;
	}

	glm::u32 ProgramResource::GetProgramId() const
	{
		return mProgramId;
	}

	#if (defined _DEBUG || !defined WINDOWS_BUILD)

	bool ProgramResource::LinkingStatus() const
	{
		glm::i32 result;

		glGetProgramiv(mProgramId, GL_LINK_STATUS, &result);

		if (!result)
		{
			glm::i32 info;

			glGetProgramiv(mProgramId, GL_INFO_LOG_LENGTH, &info);

			std::vector<char> error(glm::max(info, glm::i32(1)));
			glGetProgramInfoLog(mProgramId, info, nullptr, &error[0]);

			fprintf(stdout, "%s\n", &error[0]);

			return false;
		}

		return true;
	}

	#endif

	bool ProgramResource::Create()
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

		#if (defined _DEBUG || !defined WINDOWS_BUILD)

		if (!LinkingStatus())
		{
			return false;
		}

		#endif

		InitAttributes();
		InitUniforms();

		return true;
	}

	bool ProgramResource::Release()
	{
		if (!mProgramId)
		{
			return false;
		}

		for (auto shader : mShaders)
		{
			if (shader->GetReferencesCounter() > 0)
			{
				DetachShader(shader);

				shader->Unload();
			}
		}

		glDeleteProgram(mProgramId);

		mProgramId = 0;

		return true;
	}

	void ProgramResource::InitAttributes()
	{
		mAttributes[POSITION_INDEX] = glGetAttribLocation(mProgramId, "a_position");
		mAttributes[TEXTURE_INDEX] = glGetAttribLocation(mProgramId, "a_uv");
		mAttributes[NORMAL_INDEX] = glGetAttribLocation(mProgramId, "a_normal");
	}

	void ProgramResource::InitUniforms()
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