#include "Program.h"
#include "Shader.h"

#include <algorithm>

namespace lg
{
	Program::Program(u32 id)
		: Resource(id)
		, mProgramId(0)
	{
	}

	Program::~Program()
	{
	}

	void Program::use() const
	{
		glUseProgram(mProgramId);
	}

	void Program::link() const
	{
		glLinkProgram(mProgramId);
	}

	void Program::attachShader(Shader* shader) const
	{
		glAttachShader(mProgramId, shader->getShaderId());
	}

	void Program::detachShader(Shader* shader) const
	{
		glDetachShader(mProgramId, shader->getShaderId());
	}

	void Program::addShaders(const vector<Shader*> shaders)
	{
		for (Shader* shader : shaders)
		{
			addShader(shader);
		}
	}

	void Program::addShader(Shader* shader)
	{
		assert(shader != nullptr);

		mShaders.push_back(shader);
	}

	void Program::removeShader(u32 type)
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

	void Program::addUniform(const string& uniform_name)
	{
		assert(mUniforms.find(uniform_name) == mUniforms.end());

		mUniforms.insert({ uniform_name, -1 });
	}

	void Program::addUniforms(const vector<string>& uniforms)
	{
		for (auto uniform_name : uniforms)
		{
			addUniform(uniform_name);
		}
	}

	void Program::setUniform(const string& uniform_name, const mat4& matrix) const
	{
		glUniformMatrix4fv(mUniforms.at(uniform_name), 1, GL_FALSE, value_ptr(matrix));
	}

	void Program::setUniform(const string& uniform_name, const mat3& matrix) const
	{
		glUniformMatrix3fv(mUniforms.at(uniform_name), 1, GL_FALSE, value_ptr(matrix));
	}

	void Program::setUniform(const string& uniform_name, const vec3& vector) const
	{
		glUniform3f(mUniforms.at(uniform_name), vector.x, vector.y, vector.z);
	}

	void Program::setUniform(const string& uniform_name, const vec2& vector) const
	{
		glUniform2f(mUniforms.at(uniform_name), vector.x, vector.y);
	}

	void Program::setUniform(const string& uniform_name, f32 value)
	{
		glUniform1f(mUniforms.at(uniform_name), value);
	}

	void Program::setUniform(const string& uniform_name, i32 value)
	{
		glUniform1i(mUniforms.at(uniform_name), value);
	}

	i32 Program::getAttributeLocation(u32 index) const
	{
		assert(index < COUNT);

		return mAttributes[index];
	}

	const map<string, i32>& Program::getUniforms() const
	{
		return mUniforms;
	}

	const i32* Program::getAttributes() const
	{
		return mAttributes;
	}

	u32 Program::getProgramId() const
	{
		return mProgramId;
	}

	#if (defined _DEBUG || !defined WINDOWS_BUILD)

	bool Program::linkingStatus() const
	{
		i32 result;

		glGetProgramiv(mProgramId, GL_LINK_STATUS, &result);

		if (!result)
		{
			i32 info;

			glGetProgramiv(mProgramId, GL_INFO_LOG_LENGTH, &info);

			vector<char> error(std::max(info, i32(1)));
			glGetProgramInfoLog(mProgramId, info, nullptr, &error[0]);

			fprintf(stdout, "%s\n", &error[0]);

			return false;
		}

		return true;
	}

	#endif // (defined _DEBUG || !defined WINDOWS_BUILD)

	bool Program::create()
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

		#endif // (defined _DEBUG || !defined WINDOWS_BUILD)

		initAttributes();

		return true;
	}

	bool Program::release()
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

		// remove the uniforms
		mUniforms.clear();

		glDeleteProgram(mProgramId);

		mProgramId = 0;

		return true;
	}

	void Program::initAttributes()
	{
		mAttributes[POSITION] = glGetAttribLocation(mProgramId, "a_position");
		mAttributes[TEXTURE] = glGetAttribLocation(mProgramId, "a_uv");
		mAttributes[NORMAL] = glGetAttribLocation(mProgramId, "a_normal");
	}

	void Program::initUniforms()
	{
		for (auto it : mUniforms)
		{
			if (it.second == -1)
			{
				string key = it.first;

				mUniforms.at(key) = glGetUniformLocation(mProgramId, key.c_str());
			}
		}
	}
}
