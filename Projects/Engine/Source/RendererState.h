#ifndef _RENDERER_STATE_H_
#define _RENDERER_STATE_H_

#include "EngineUtil.h"

namespace ai
{
	class ENGINE_API RendererState
	{
	public:
		static bool CheckMeshId(glm::u32 id);
		static bool CheckProgramId(glm::u32 id);
		static bool CheckMaterialId(glm::u32 id);

	private:
		static glm::u32 smCurrentMeshId;
		static glm::u32 smCurrentProgramId;
		static glm::u32 smCurrentMaterialId;
	};
}

#endif // _RENDERER_STATE_H_
