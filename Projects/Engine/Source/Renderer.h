#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "EngineUtil.h"

namespace lg
{
	class Sprite;
	class Scene;
	class Node;
	class MeshRenderer;
	
	class ENGINE_API Renderer
	{
	public:
		Renderer();
		~Renderer();

		void draw() const;
		void drawNode(const Node* node) const;
		void drawSprite(const Sprite* sprite) const;

		void setScene(const Scene* scene);

		static void enable2dDrawing();
		static void disable2dDrawing();
		static void init();

	private:
		static u32 smCurrentMeshId;
		static u32 smCurrentProgramId;
		static u32 smCurrentMaterialId;
		static u32 smCurrentTextureId;
		static bool smIsDrawing2d;

		const Scene* mScene;
	};
}

#endif // _RENDERER_H_
