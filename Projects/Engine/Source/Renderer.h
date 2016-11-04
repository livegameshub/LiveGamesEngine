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
		void drawAll(const Node* node) const;
		void drawNode(const Node* node) const;
		void drawSprite(const Node* sprite) const;

		void setScene(const Scene* scene);

		static void init();
		static void enable2d();
		static void disable2d();
		
	private:
		static u32 smCurrentMeshId;
		static u32 smCurrentProgramId;
		static u32 smCurrentMaterialId;
		static u32 smCurrentTextureId;

		static bool smIs2dActivated;

		const Scene* mScene;
	};
}

#endif // _RENDERER_H_
