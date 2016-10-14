#include "Renderer.h"
#include "Graphics.h"
#include "ModelNode.h"
#include "CameraNode.h"
#include "ProgramResource.h"
#include "BasicMaterialResource.h"
#include "MeshResource.h"
#include "BasicScene.h"
#include "RendererState.h"

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
		const BasicMaterialResource* material = model->getMaterial();
		assert(material != nullptr);

		const ProgramResource* program = material->getProgram();
		assert(program != nullptr);

		if (RendererState::checkProgramId(program->getId()))
		{
			program->use();
		}

		program->setUniform(UNIFORM_VIEW, mScene->getCameraByIndex(0)->getViewMatrix());
		program->setUniform(UNIFORM_PROJECTION, mScene->getCameraByIndex(0)->getPerspecitiveMatrix());

		if (RendererState::checkMaterialId(material->getId()))
		{
			material->UploadUniforms();
		}

		const MeshResource* mesh = model->getMesh();
		assert(mesh != nullptr);

		if (RendererState::checkMeshId(mesh->getId()))
		{
			mesh->bindVbo();
			mesh->uploadAttributes(program->getAttributes());
			mesh->bindIbo();
		}

		program->setUniform(UNIFORM_MODEL, model->getTransform().getMatrix());

		mesh->draw();
	}
}
