#ifndef _MATERIAL_RESOURCE_H_
#define _MATERIAL_RESOURCE_H_

#include "ProgramResource.h"

namespace ai
{
	class ENGINE_API MaterialResource : public BasicResource
	{
	public:
		enum MaterialProperties : glm::u32
		{
			IS_LIGTHED = 1,
			IS_TEXTURED = 2,
			IS_SHINY = 4
		};

		MaterialResource(glm::u32 id);
		MaterialResource(glm::u32 id, const Flag& flag);

		virtual ~MaterialResource();

		void SetProgram(ProgramResource* program);
		void setDiffuseColor(const glm::vec3& color);

		ProgramResource* GetProgram() const;
		const glm::vec3& GetDiffuseColor() const;

	private:
		bool Create() override;
		bool Release() override;

		ProgramResource* mProgram;

		glm::vec3 mDiffuseColor;
	};
}

#endif
