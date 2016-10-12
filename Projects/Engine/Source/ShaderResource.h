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

		void compile() const;

		void setShaderType(glm::u32 type);
		glm::u32 getShaderType() const;
		glm::u32 getShaderId() const;
		
	private:
		#if (defined _DEBUG || !defined WINDOWS_BUILD)

		bool compilationStatus() const;

		#endif // (defined _DEBUG || !defined WINDOWS_BUILD)

		bool create() override;
		bool release() override;

		glm::u32 mShaderId;
		glm::u32 mShaderType;
	};
}

#endif // _SHADER_RESOURCE_H_
