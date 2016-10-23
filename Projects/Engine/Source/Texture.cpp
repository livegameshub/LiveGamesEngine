#include "Texture.h"
#include "Graphics.h"

namespace ai
{
	Texture::Texture(glm::u32 id)
		: Resource(id)
		, mTextureId(0)
		, mWidth(0)
		, mHeight(0)
	{		
	}

	Texture::Texture(glm::u32 id, const std::string& file)
		: Resource(id, file)
		, mTextureId(0)
		, mWidth(0)
		, mHeight(0)
	{
	}

	Texture::~Texture()
	{
	}

	void Texture::bind() const
	{
		glBindTexture(GL_TEXTURE_2D, mTextureId);
	}

	void Texture::Activate(glm::u32 index)
	{
		glActiveTexture(GL_TEXTURE0 + index);
	}

	bool Texture::create()
	{
		glGenTextures(1, &mTextureId);

		return true;
	}

	bool Texture::release()
	{
		if (!mTextureId)
		{
			return false;
		}

		glDeleteTextures(1, &mTextureId);

		mTextureId = 0;

		return true;
	}

	glm::u32 Texture::getTextureId() const
	{
		return mTextureId;
	}

	glm::u32 Texture::getHeight() const
	{
		return mHeight;
	}

	glm::u32 Texture::getWidth() const
	{
		return mWidth;
	}
}
