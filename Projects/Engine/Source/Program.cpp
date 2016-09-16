#include "Program.h"
#include "Shader.h"

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

}
