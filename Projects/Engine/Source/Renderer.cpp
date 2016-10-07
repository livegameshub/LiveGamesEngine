#include "Renderer.h"
#include "Graphics.h"
#include "ModelNode.h"

namespace ai
{
	Renderer::Renderer()
		: mScene(nullptr)
	{
	}

	Renderer::~Renderer()
	{
	}

	void Renderer::init()
	{
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void Renderer::setScene(BasicScene* scene)
	{
		mScene = scene;
	}

	void Renderer::draw()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (mScene)
		{
			drawNode(&mScene->getRootNode());
		}
	}

	void Renderer::drawNode(const BasicNode* node)
	{
		for (auto node_instance : node->GetChildren())
		{
			assert(node_instance != nullptr);

			if (node_instance->IsEnabled())
			{
				if (node_instance->GetNodeType() == BasicNode::MODEL_NODE)
				{
					ModelNode* model = static_cast<ModelNode*>(node_instance);

					if (model->IsVisible())
					{
						drawModel(model);
					}
				}

				drawNode(node_instance);
			}
		}
	}

	void Renderer::drawModel(const ModelNode* model)
	{
		const MaterialResource* material = model->GetMaterial();
		assert(material != nullptr);

		const ProgramResource* program = material->GetProgram();
		assert(program != nullptr);

		program->Use();
	}
}
