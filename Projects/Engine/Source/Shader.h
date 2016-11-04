#ifndef _SHADER_H_
#define _SHADER_H_

#include "Resource.h"
#include "Graphics.h"

namespace lg
{
	class ENGINE_API Shader : public Resource
	{
	public:
		static const u32 VERTEX = GL_VERTEX_SHADER;
		static const u32 FRAGMENT = GL_FRAGMENT_SHADER;

		Shader(u32 id);
		Shader(u32 id, u32 shaderType);
		Shader(u32 id, u32 shaderType, const string& file);

		~Shader();

		void compile() const;

		void setShaderType(u32 type);
		u32 getShaderType() const;
		u32 getShaderId() const;
		
	private:
		#if (defined _DEBUG || !defined WINDOWS_BUILD)

		bool compilationStatus() const;

		#endif // (defined _DEBUG || !defined WINDOWS_BUILD)

		bool create() override;
		bool release() override;

		u32 mShaderId;
		u32 mShaderType;
	};
}

#endif // _SHADER_H_
