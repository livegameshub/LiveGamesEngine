#ifndef _PROGRAM_RESOURCE_H_
#define _PROGRAM_RESOURCE_H_

#include "BasicResource.h"

namespace ai
{
	class ShaderResource;

	class ENGINE_API ProgramResource : public BasicResource
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

		ProgramResource(glm::u32 id);
		~ProgramResource();
	
		void use() const;
		void link() const;

		void initUniforms();

		void attachShader(ShaderResource* shader) const;
		void detachShader(ShaderResource* shader) const;

		void addShader(ShaderResource* shader);
		void removeShader(glm::u32 type);

		void addUniform(const std::string& uniform_name);
		void addUniforms(const std::vector<std::string>& uniforms);

		void setUniform(const std::string& uniform_name, const glm::mat4& matrix) const;
		void setUniform(const std::string& uniform_name, const glm::mat3& matrix) const;
		void setUniform(const std::string& uniform_name, const glm::vec3& vector) const;
		void setUniform(const std::string& uniform_name, const glm::vec2& vector) const;
		void setUniform(const std::string& uniform_name, glm::f32 value);
		void setUniform(const std::string& uniform_name, glm::i32 value);

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
		std::vector<ShaderResource*> mShaders;

		glm::i32 mAttributes[COUNT];
		glm::u32 mProgramId;
	};
}

#endif // _PROGRAM_RESOURCE_H_
