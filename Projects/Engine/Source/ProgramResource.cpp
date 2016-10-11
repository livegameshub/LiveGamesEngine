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

	void ProgramResource::use() const
	{
		glUseProgram(mProgramId);
	}

	void ProgramResource::link() const
	{
		glLinkProgram(mProgramId);
	}

	void ProgramResource::attachShader(ShaderResource* shader) const
	{
		glAttachShader(mProgramId, shader->getShaderId());
	}

	void ProgramResource::detachShader(ShaderResource* shader) const
	{
		glDetachShader(mProgramId, shader->getShaderId());
	}

	void ProgramResource::addShader(ShaderResource* shader)
	{
		assert(shader != nullptr);

		mShaders.push_back(shader);
	}

	void ProgramResource::removeShader(glm::u32 type)
	{
		for (auto it = mShaders.begin(); it != mShaders.end(); ++it)
		{
			if ((*it)->getShaderType() == type)
			{
				mShaders.erase(it);

				break;
			}
		}
	}

	void ProgramResource::addUniform(const std::string& uniform_name)
	{
		assert(mUniforms.find(uniform_name) == mUniforms.end());

		mUniforms.insert({ uniform_name, -1 });
	}

	void ProgramResource::addUniforms(const std::vector<std::string>& uniforms)
	{
		for (auto uniform_name : uniforms)
		{
			addUniform(uniform_name);
		}
	}

	void ProgramResource::setUniform(const std::string& uniform_name, const glm::mat4& matrix) const
	{
		glUniformMatrix4fv(mUniforms.at(uniform_name), 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void ProgramResource::setUniform(const std::string& uniform_name, const glm::vec3& vector) const
	{
		glUniform3f(mUniforms.at(uniform_name), vector.x, vector.y, vector.z);
	}

	void ProgramResource::setUniform(const std::string& uniform_name, glm::f32 value)
	{
		glUniform1f(mUniforms.at(uniform_name), value);
	}

	void ProgramResource::setUniform(const std::string& uniform_name, glm::i32 value)
	{
		glUniform1i(mUniforms.at(uniform_name), value);
	}

	glm::i32 ProgramResource::getAttributeLocation(glm::u32 index) const
	{
		assert(index < COUNT);

		return mAttributes[index];
	}

	const glm::i32* ProgramResource::getAttributes() const
	{
		return mAttributes;
	}

	glm::u32 ProgramResource::getProgramId() const
	{
		return mProgramId;
	}

	#if (defined _DEBUG || !defined WINDOWS_BUILD)

	bool ProgramResource::linkingStatus() const
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

	bool ProgramResource::create()
	{
		mProgramId = glCreateProgram();

		if (!mProgramId)
		{
			return false;
		}

		for (auto shader : mShaders)
		{
			if (shader->load())
			{
				attachShader(shader);
			}
		}

		link();

		#if (defined _DEBUG || !defined WINDOWS_BUILD)

		if (!linkingStatus())
		{
			return false;
		}

		#endif

		initAttributes();
		initUniforms();

		return true;
	}

	bool ProgramResource::release()
	{
		if (!mProgramId)
		{
			return false;
		}

		for (auto shader : mShaders)
		{
			if (shader->getReferencesCounter() > 0)
			{
				detachShader(shader);

				shader->unload();
			}
		}

		glDeleteProgram(mProgramId);

		mProgramId = 0;

		return true;
	}

	void ProgramResource::initAttributes()
	{
		mAttributes[POSITION_INDEX] = glGetAttribLocation(mProgramId, "a_position");
		mAttributes[TEXTURE_INDEX] = glGetAttribLocation(mProgramId, "a_uv");
		mAttributes[NORMAL_INDEX] = glGetAttribLocation(mProgramId, "a_normal");
	}

	void ProgramResource::initUniforms()
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
