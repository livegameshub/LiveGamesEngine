#include "RendererState.h"

namespace ai
{
	glm::u32 RendererState::smCurrentMeshId = 0;
	glm::u32 RendererState::smCurrentProgramId = 0;
	glm::u32 RendererState::smCurrentMaterialId = 0;

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
		if (smCurrentProgramId != id)
		{
			smCurrentProgramId = id;

			return true;
		}

		return false;
	}

	bool RendererState::CheckMaterialId(glm::u32 id)
	{
		if (smCurrentMaterialId != id)
		{
			smCurrentMaterialId = id;

			return true;
		}

		return false;
	}
}
