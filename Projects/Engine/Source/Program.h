#ifndef _PROGRAM_H_
#define _PROGRAM_H_

#include "BasicResource.h"

namespace ai
{
	class Shader;

	class ENGINE_API Program : public BasicResource
	{
	public:
		enum AttributeIndex : glm::u32
		{
			POSITION_INDEX,
			TEXTURE_INDEX,
			NORMAL_INDEX,
			COUNT
		};

		Program(glm::u32 id);
		~Program();
	
		void Use() const;
		void Link() const;

		void AttachShader(Shader* shader) const;
		void DetachShader(Shader* shader) const;

		void AddShader(Shader* shader);
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
		std::vector<Shader*> mShaders;

		glm::i32 mAttributes[COUNT];
		glm::u32 mProgramId;
	};
}

#endif
