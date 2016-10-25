#include "Texture.h"
#include "Graphics.h"

namespace lg
{
	Texture::Texture(glm::u32 id)
		: Resource(id)
		, mTextureId(0)
		, mBits(0)
	{		
	}

	Texture::Texture(glm::u32 id, const std::string& file)
		: Resource(id, file)
		, mTextureId(0)
		, mBits(0)
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
		FILE * pFile;

		// read the pixels
		fopen_s(&pFile, std::string(ASSETS_PATH + mResourceFile).c_str(), "rb");

		fread(&mSize.x, sizeof(glm::i32), 1, pFile);
		fread(&mSize.y, sizeof(glm::i32), 1, pFile);
		fread(&mBits, sizeof(glm::u32), 1, pFile);

		glm::u32 format = getTextureFormat();
		
		if (!format)
		{
			return false;
		}

		glm::i32 image_size = mSize.x * mSize.y * (mBits / 8);

		unsigned char* texture_data = new unsigned char[image_size];

		if (!texture_data)
		{
			return false;
		}

		fread(texture_data, image_size, 1, pFile);

		fclose(pFile);

		// generate the texture
		glGenTextures(1, &mTextureId);

		if (!mTextureId)
		{
			return false;
		}

		bind();

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, format, mSize.x, mSize.y, 0, format, GL_UNSIGNED_BYTE, texture_data);

		delete[] texture_data;
		texture_data = nullptr;

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

	glm::u32 Texture::getTextureFormat() const
	{
		if (mBits == 32)
		{
			return GL_RGBA;
		}

		if (mBits == GL_RGB)
		{
			return GL_RGB;
		}

		return 0;
	}

	const glm::ivec2& Texture::getSize() const
	{
		return mSize;
	}
}
