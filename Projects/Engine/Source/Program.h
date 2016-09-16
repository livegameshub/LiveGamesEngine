#ifndef _PROGRAM_H_
#define _PROGRAM_H_

#include "BasicResource.h"

namespace ai
{
	class Shader;
	struct Matrix4;

	class ENGINE_API Program : public BasicResource
	{
	public:
		enum AttributeIndex : u32
		{
			POSITION_INDEX,
			TEXTURE_INDEX,
			NORMAL_INDEX,
			COUNT
		};

		Program(u32 id);
		~Program();
	
		void User() const;
		void Link() const;

		void AttachShader(Shader* shader) const;
		void DetachShader(Shader* shader) const;

		void AddShader(Shader* shader);
		void RemoveShader(u32 type);

		void AddUniform(const std::string& uniform_name);
		void AddUniforms(const std::vector<std::string>& uniforms);

		void SetUniform(const char* uniform_name, const Matrix4& matrix) const;

		inline i32 GetAttributeLocation(u32 index) const;

		inline const i32* GetAttributes() const;
		inline u32 GetProgramId() const;

	private:
		#ifdef _DEBUG

		bool LinkingStatus() const;

		#endif

		bool Create() override;
		bool Release() override;

		void InitAttributes();
		void InitUniforms();

		std::map<std::string, i32> mUniforms;
		std::vector<Shader*> mShaders;

		i32 mAttributes[COUNT];
		u32 mProgramId;
	};
}

#endif
