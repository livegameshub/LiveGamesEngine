#include "RendererState.h"

namespace ai
{
	glm::u32 RendererState::smCurrentMeshId = 0;

	bool RendererState::CheckMeshId(glm::u32 id)
	{
		if (smCurrentMeshId != id)
		{
			smCurrentMeshId = id;

			return true;
		}

		return false;
	}

	bool RendererState::CheckProgramId(glm::u32 id)
	{
	}
}
