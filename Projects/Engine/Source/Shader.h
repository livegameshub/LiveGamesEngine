#ifndef _SHADER_H_
#define _SHADER_H_

#include "BasicResource.h"
#include "Graphics.h"

namespace ai
{
	class ENGINE_API Shader : public BasicResource
	{
	public:
		static const glm::u32 VERTEX_SHADER = GL_VERTEX_SHADER;
		static const glm::u32 FRAGMENT_SHADER = GL_FRAGMENT_SHADER;

		Shader(glm::u32 id);
		Shader(glm::u32 id, glm::u32 shaderType);
		Shader(glm::u32 id, glm::u32 shaderType, const std::string& file);

		~Shader();

		void Compile() const;

		inline void SetShaderType(glm::u32 type);
		inline glm::u32 GetShaderType() const;
		inline glm::u32 GetShaderId() const;
		
	private:
		#ifdef _DEBUG

		bool CompilationStatus() const;

		#endif

		bool Create() override;
		bool Release() override;

		glm::u32 mShaderId;
		glm::u32 mShaderType;
	};
}

#endif