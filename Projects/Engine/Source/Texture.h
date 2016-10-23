#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "Resource.h"

namespace ai
{
	class ENGINE_API Texture : public Resource
	{
	public:
		Texture(glm::u32 id);
		Texture(glm::u32 id, const std::string& file);

		~Texture();

		void bind() const;

		glm::u32 getTextureId() const;
		glm::u32 getWidth() const;
		glm::u32 getHeight() const;

		static void Activate(glm::u32 index);

	private:
		bool create() override;
		bool release() override;

		glm::u32 mTextureId;
		glm::u32 mBitsPerPixel;
		glm::u32 mWidth;
		glm::u32 mHeight;
	};
}

#endif // _TEXTURE_H_
