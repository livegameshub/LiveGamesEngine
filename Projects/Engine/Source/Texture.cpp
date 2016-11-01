#include "Texture.h"
#include "Graphics.h"

namespace lg
{
	Texture::Texture(glm::u32 id)
		: Resource(id)
		, mGenerateMipmaps(false)
		, mTextureId(0)
		, mFormat(0)
		, mBits(0)
	{		
	}

	Texture::Texture(glm::u32 id, const std::string& file, bool generateMipmaps)
		: Resource(id, file)
		, mGenerateMipmaps(generateMipmaps)
		, mTextureId(0)
		, mFormat(0)
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

		#ifdef WINDOWS_BUILD

		fopen_s(&pFile, std::string(ASSETS_PATH + mResourceFile).c_str(), "rb");
		#else

		pFile = fopen(std::string(ASSETS_PATH + mResourceFile).c_str(), "rb");
		#endif

		if (!pFile)
		{
			return false;
		}

		fread(&mSize.x, sizeof(glm::i32), 1, pFile);
		fread(&mSize.y, sizeof(glm::i32), 1, pFile);
		fread(&mBits, sizeof(glm::u32), 1, pFile);
		fread(&mFormat, sizeof(glm::i32), 1, pFile);

		glm::i32 image_size = mSize.x * mSize.y * (mBits / 8);

		unsigned char* texture_data = new unsigned char[image_size];

		if (!texture_data)
		{
			return false;
		}

		// read the pixels
		fread(texture_data, image_size, 1, pFile);

		fclose(pFile);

		// generate the texture
		glGenTextures(1, &mTextureId);

		if (!mTextureId)
		{
			return false;
		}

		bind();

		glTexImage2D(GL_TEXTURE_2D, 0, mFormat, mSize.x, mSize.y, 0, mFormat, GL_UNSIGNED_BYTE, texture_data);

		if (mGenerateMipmaps)
		{
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		}
		else
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}

		SAFE_ARRAY_DELETE(texture_data);

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

	glm::u32 Texture::getTextureFormat() const
	{
		return mFormat;
	}
}
