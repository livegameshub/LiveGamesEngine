#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "BasicScene.h"

namespace ai
{
	class ModelNode;

	class ENGINE_API Renderer
	{
	public:
		Renderer();
		~Renderer();

		void draw();
		void setScene(BasicScene* scene);

		static void drawNode(const BasicNode* node);
		static void drawModel(const ModelNode* model);

		static void init();

	private:
		BasicScene* mScene;
	};
}

#endif
