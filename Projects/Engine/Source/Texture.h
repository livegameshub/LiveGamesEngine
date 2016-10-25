#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "Resource.h"

namespace lg
{
	class ENGINE_API Texture : public Resource
	{
	public:
		Texture(glm::u32 id);
		Texture(glm::u32 id, const std::string& file);

		~Texture();

		void bind() const;

		const glm::ivec2& getSize() const;
		glm::u32 getTextureFormat() const;
		glm::u32 getTextureId() const;
		
		
		static void Activate(glm::u32 index);

	private:
		bool create() override;
		bool release() override;

		glm::ivec2 mSize;
		glm::u32 mTextureId;
		glm::u32 mBits;
	};
}

#endif // _TEXTURE_H_
