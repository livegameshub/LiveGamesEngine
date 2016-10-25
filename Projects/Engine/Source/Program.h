#ifndef _PROGRAM_H_
#define _PROGRAM_H_

#include "Resource.h"

namespace lg
{
	class Shader;

	class ENGINE_API Program : public Resource
	{
	public:
		enum UniformsType : glm::u32
		{
			BASIC_MATERIAL_UNIFORMS = 1,
			DIFFUSE_MATERIAL_UNIFORMS = 2
		};

		enum AttributeIndex : glm::u32
		{
			POSITION_INDEX,
			TEXTURE_INDEX,
			NORMAL_INDEX,
			COUNT
		};

		Program(glm::u32 id);
		~Program();
	
		void use() const;
		void link() const;

		void initUniforms();

		void attachShader(Shader* shader) const;
		void detachShader(Shader* shader) const;

		void addShader(Shader* shader);
		void removeShader(glm::u32 type);

		void addUniform(const std::string& name);
		void addUniforms(const std::vector<std::string>& uniforms);

		void setUniform(const std::string& name, const glm::mat4& matrix) const;
		void setUniform(const std::string& name, const glm::mat3& matrix) const;
		void setUniform(const std::string& name, const glm::vec3& vector) const;
		void setUniform(const std::string& name, const glm::vec2& vector) const;
		void setUniform(const std::string& name, glm::f32 value);
		void setUniform(const std::string& name, glm::i32 value);

		glm::i32 getAttributeLocation(glm::u32 index) const;

		const std::map<std::string, glm::i32>& getUniforms() const;
		const glm::i32* getAttributes() const;
		glm::u32 getProgramId() const;

	private:
		#if (defined _DEBUG || !defined WINDOWS_BUILD)

		bool linkingStatus() const;

		#endif // (defined _DEBUG || !defined WINDOWS_BUILD)

		bool create() override;
		bool release() override;

		void initAttributes();

		std::map<std::string, glm::i32> mUniforms;
		std::vector<Shader*> mShaders;

		glm::i32 mAttributes[COUNT];
		glm::u32 mProgramId;
	};
}

#endif // _PROGRAM_H_
