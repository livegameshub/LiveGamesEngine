#include "Renderer.h"
#include "Graphics.h"
#include "ModelNode.h"
#include "CameraNode.h"

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

	void Renderer::draw() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (mScene)
		{
			drawNode(&mScene->getRootNode());
		}
	}

	void Renderer::drawNode(const BasicNode* node) const
	{
		for (auto node_instance : node->getChildren())
		{
			assert(node_instance != nullptr);

			if (node_instance->isEnabled())
			{
				if (node_instance->getNodeType() == BasicNode::MODEL_NODE)
				{
					ModelNode* model = static_cast<ModelNode*>(node_instance);

					if (model->isVisible())
					{
						drawModel(model);
					}
				}

				drawNode(node_instance);
			}
		}
	}

	void Renderer::drawModel(const ModelNode* model) const
	{
		const MaterialResource* material = model->getMaterial();
		assert(material != nullptr);

		const ProgramResource* program = material->GetProgram();
		assert(program != nullptr);

		program->Use();

		program->SetUniform("u_view", mScene->getCameraByIndex(0)->getViewMatrix());
		program->SetUniform("u_projection", mScene->getCameraByIndex(0)->getPerspecitiveMatrix());

		program->SetUniform("u_material.diffuse", material->GetDiffuseColor());

		const MeshResource* mesh = model->getMesh();
		assert(mesh != nullptr);

		mesh->BindVbo();
		mesh->UploadAttributes(program->GetAttributes());
		mesh->BindIbo();

		program->SetUniform("u_model", model->getTransform().GetMatrix());

		mesh->Draw();
	}
}
