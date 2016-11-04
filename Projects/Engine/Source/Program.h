#ifndef _PROGRAM_H_
#define _PROGRAM_H_

#include "Resource.h"

namespace lg
{
	class Shader;

	class ENGINE_API Program : public Resource
	{
	public:
		enum UniformsType : u32
		{
			BASIC_MATERIAL = 1,
			DIFFUSE_MATERIAL = 2
		};

		enum AttributeIndex : u32
		{
			POSITION,
			TEXTURE,
			NORMAL,
			COUNT
		};

		Program(u32 id);
		~Program();
	
		void use() const;
		void link() const;

		void initUniforms();

		void attachShader(Shader* shader) const;
		void detachShader(Shader* shader) const;

		void addShader(Shader* shader);
		void removeShader(u32 type);

		void addUniform(const string& name);
		void addUniforms(const vector<string>& uniforms);

		void setUniform(const string& name, const mat4& matrix) const;
		void setUniform(const string& name, const mat3& matrix) const;
		void setUniform(const string& name, const vec3& vector) const;
		void setUniform(const string& name, const vec2& vector) const;
		void setUniform(const string& name, f32 value);
		void setUniform(const string& name, i32 value);

		i32 getAttributeLocation(u32 index) const;

		const map<string, i32>& getUniforms() const;
		const i32* getAttributes() const;
		u32 getProgramId() const;

	private:
		#if (defined _DEBUG || !defined WINDOWS_BUILD)

		bool linkingStatus() const;

		#endif // (defined _DEBUG || !defined WINDOWS_BUILD)

		bool create() override;
		bool release() override;

		void initAttributes();

		map<string, i32> mUniforms;
		vector<Shader*> mShaders;

		i32 mAttributes[COUNT];
		u32 mProgramId;
	};
}

#endif // _PROGRAM_H_
