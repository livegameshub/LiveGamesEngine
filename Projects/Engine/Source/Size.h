#ifndef _SIZE_H_
#define _SIZE_H_

#include "EngineUtil.h"

namespace ai
{
	template <typename T> struct ENGINE_API Size
	{
		T width;
		T height;

		Size()
		{
		}

		Size(T width, T height) : width(width), height(height)
		{
		}
		
		bool operator!=(const Size<T>& size) const
		{
			return width != size.width || height != size.height;
		}

		bool operator==(const Size<T>& size) const
		{
			return width == size.width && height = size.height;
		}
	};

	/* in case you use this outside this projects */

	//EXP_TEMPLATE template struct ENGINE_API Size<u32>;
	//EXP_TEMPLATE template struct ENGINE_API Size<f32>;
}

#endif
