#ifndef _PROGRAM_RESOURCE_H_
#define _PROGRAM_RESOURCE_H_

#include "BasicResource.h"

namespace ai
{
	class ShaderResource;

	class ENGINE_API ProgramResource : public BasicResource
	{
	public:
		enum AttributeIndex : glm::u32
		{
			POSITION_INDEX,
			TEXTURE_INDEX,
			NORMAL_INDEX,
			COUNT
		};

		ProgramResource(glm::u32 id);
		~ProgramResource();
	
		void Use() const;
		void Link() const;

		void AttachShader(ShaderResource* shader) const;
		void DetachShader(ShaderResource* shader) const;

		void AddShader(ShaderResource* shader);
		void RemoveShader(glm::u32 type);

		void AddUniform(const std::string& uniform_name);
		void AddUniforms(const std::vector<std::string>& uniforms);

		void SetUniform(const std::string& uniform_name, const glm::mat4& matrix) const;
		void SetUniform(const std::string& uniform_name, const glm::vec3& vector) const;
		void SetUniform(const std::string& uniform_name, glm::f32 value);
		void SetUniform(const std::string& uniform_name, glm::i32 value);

		glm::i32 GetAttributeLocation(glm::u32 index) const;

		const glm::i32* GetAttributes() const;
		glm::u32 GetProgramId() const;

	private:
		#if (defined _DEBUG || !defined WINDOWS_BUILD)

		bool LinkingStatus() const;

		#endif

		bool Create() override;
		bool Release() override;

		void InitAttributes();
		void InitUniforms();

		std::map<std::string, glm::i32> mUniforms;
		std::vector<ShaderResource*> mShaders;

		glm::i32 mAttributes[COUNT];
		glm::u32 mProgramId;
	};
}

#endif
