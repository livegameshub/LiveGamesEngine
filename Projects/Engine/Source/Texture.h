#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "Resource.h"

namespace lg
{
	class ENGINE_API Texture : public Resource
	{
	public:
		Texture(u32 id);
		Texture(u32 id, const string& file, bool generateMipmaps);

		~Texture();

		void bind() const;

		const ivec2& getSize() const;
		u32 getTextureFormat() const;
		u32 getTextureId() const;
		
		static void Activate(u32 index);

	private:
		bool create() override;
		bool release() override;

		bool mGenerateMipmaps;

		ivec2 mSize;
		u32 mTextureId;
		u32 mFormat;
		u32 mBits;
	};
}

#endif // _TEXTURE_H_
