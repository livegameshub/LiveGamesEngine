#ifndef _SHADER_H_
#define _SHADER_H_

#include "BasicResource.h"
#include "Graphics.h"

namespace ai
{
	class ENGINE_API Shader : public BasicResource
	{
	public:
		const u32 VERTEX_SHADER = GL_VERTEX_SHADER;
		const u32 FRAGMENT_SHADER = GL_FRAGMENT_SHADER;

		Shader(u32 id);
		Shader(u32 id, u32 shaderType);
		~Shader();

		void Compile() const;

		inline void SetShaderType(u32 type);
		inline u32 GetShaderType() const;
		inline u32 GetShaderId() const;
		
	private:
		#ifdef _DEBUG

		bool CompilationStatus() const;

		#endif

		bool Create() override;
		bool Release() override;

		u32 mShaderId;
		u32 mShaderType;
	};
}

#endif
