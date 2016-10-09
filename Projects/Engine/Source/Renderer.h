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

		void draw() const;

		void drawNode(const BasicNode* node) const;
		void drawModel(const ModelNode* model) const;
		void setScene(BasicScene* scene);

		static void init();

	private:
		BasicScene* mScene;
	};
}

#endif
