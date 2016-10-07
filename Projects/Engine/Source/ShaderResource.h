#ifndef _SHADER_RESOURCE_H_
#define _SHADER_RESOURCE_H_

#include "BasicResource.h"
#include "Graphics.h"

namespace ai
{
	class ENGINE_API ShaderResource : public BasicResource
	{
	public:
		static const glm::u32 VERTEX_SHADER = GL_VERTEX_SHADER;
		static const glm::u32 FRAGMENT_SHADER = GL_FRAGMENT_SHADER;

		ShaderResource(glm::u32 id);
		ShaderResource(glm::u32 id, glm::u32 shaderType);
		ShaderResource(glm::u32 id, glm::u32 shaderType, const std::string& file);

		~ShaderResource();

		void Compile() const;

		void SetShaderType(glm::u32 type);
		glm::u32 GetShaderType() const;
		glm::u32 GetShaderId() const;
		
	private:
		#if (defined _DEBUG || !defined WINDOWS_BUILD)

		bool CompilationStatus() const;

		#endif

		bool Create() override;
		bool Release() override;

		glm::u32 mShaderId;
		glm::u32 mShaderType;
	};
}

#endif
