#include "Texture.h"
#include "Graphics.h"

namespace ai
{
	Texture::Texture(glm::u32 id)
		: Resource(id)
		, mTextureId(0)
		, mBitsPerPixel(0)
	{		
	}

	Texture::Texture(glm::u32 id, const std::string& file)
		: Resource(id, file)
		, mTextureId(0)
		, mBitsPerPixel(0)
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
		fread(&mBitsPerPixel, sizeof(glm::u32), 1, pFile);

		glm::i32 image_size = mSize.x * mSize.y * (mBitsPerPixel / 8);

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

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mSize.x, mSize.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_data);

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

	const glm::ivec2& Texture::getSize() const
	{
		return mSize;
	}
}
