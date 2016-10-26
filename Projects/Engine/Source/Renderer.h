#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "EngineUtil.h"

namespace lg
{
	class Sprite;
	class Scene;
	class Node;
	class Renderable;
	
	class ENGINE_API Renderer
	{
	public:
		Renderer();
		~Renderer();

		void draw() const;
		void drawNode(const Node* node) const;
		void drawSprite(const Sprite* sprite) const;
		void drawRenderable(const Renderable* model) const;

		void setScene(const Scene* scene);

		static void enable2d();
		static void disable2d();
		static void init();

	private:
		static glm::u32 smCurrentMeshId;
		static glm::u32 smCurrentProgramId;
		static glm::u32 smCurrentMaterialId;
		static glm::u32 smCurrentTextureId;
		static bool smIsUsing2d;

		const Scene* mScene;
	};
}

#endif // _RENDERER_H_
