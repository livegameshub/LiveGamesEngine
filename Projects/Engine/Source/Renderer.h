#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "EngineUtil.h"

namespace lg
{
	class Scene;
	class Node;
	class Model;
	
	class ENGINE_API Renderer
	{
	public:
		Renderer();
		~Renderer();

		void draw() const;

		void drawNode(const Node* node) const;
		void drawModel(const Model* model) const;
		void setScene(const Scene* scene);

		static void init();

	private:
		const Scene* mScene;
	};
}

#endif // _RENDERER_H_
