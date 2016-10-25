#include "RendererState.h"

namespace lg
{
	glm::u32 RendererState::smCurrentMeshId = 0;
	glm::u32 RendererState::smCurrentProgramId = 0;
	glm::u32 RendererState::smCurrentMaterialId = 0;
	glm::u32 RendererState::smCurrentTextureId = 0;

	bool RendererState::checkMeshId(glm::u32 id)
	{
		if (smCurrentMeshId != id)
		{
			smCurrentMeshId = id;

			return true;
		}

		return false;
	}

	bool RendererState::checkProgramId(glm::u32 id)
	{
		if (smCurrentProgramId != id)
		{
			smCurrentProgramId = id;

			return true;
		}

		return false;
	}

	bool RendererState::checkMaterialId(glm::u32 id)
	{
		if (smCurrentMaterialId != id)
		{
			smCurrentMaterialId = id;

			return true;
		}

		return false;
	}

	bool RendererState::checkTextureId(glm::u32 id)
	{
		if (smCurrentTextureId != id)
		{
			smCurrentTextureId = id;

			return true;
		}

		return false;
	}
}
