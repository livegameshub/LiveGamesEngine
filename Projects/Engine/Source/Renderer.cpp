#include "Renderer.h"
#include "Graphics.h"
#include "ModelNode.h"
#include "CameraNode.h"
#include "ProgramResource.h"
#include "BasicMaterialResource.h"
#include "MeshResource.h"
#include "BasicScene.h"
#include "RendererState.h"
#include "DiffuseMaterialResource.h"
#include "DirectionalLightNode.h"

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
		BasicMaterialResource* material = model->getMaterial();
		assert(material != nullptr);

		const ProgramResource* program = material->getProgram();
		assert(program != nullptr);

		if (RendererState::checkProgramId(program->getId()))
		{
			program->use();
		}

		const CameraNode* camera = mScene->getCameraByIndex(0);
		assert(camera != nullptr);

		program->setUniform(UNIFORM_VIEW, camera->getViewMatrix());
		program->setUniform(UNIFORM_PROJECTION, camera->getPerspecitiveMatrix());

		if (material->IsLighted())
		{
			program->setUniform(UNIFORM_CAMERA_POSITION, camera->getTransform().getPosition());
		}

		if (RendererState::checkMaterialId(material->getId()))
		{
			material->uploadUniforms();

			if (material->IsLighted())
			{
				program->setUniform(UNIFORM_AMBIENT_LIGHT, mScene->getAmbientLight());

				static_cast<DiffuseMaterialResource*>(material)->uploadUniforms(static_cast<DirectionalLightNode*>(mScene->getLightByIndex(0)));
			}
		}

		const MeshResource* mesh = model->getMesh();
		assert(mesh != nullptr);

		if (RendererState::checkMeshId(mesh->getId()))
		{
			mesh->bindVbo();
			mesh->uploadAttributes(program->getAttributes());
			mesh->bindIbo();

			if (material->IsLighted())
			{
				if (model->getTransform().hasUniformScale())
				{
					program->setUniform(UNIFORM_NORMAL, glm::mat3(model->getTransform().getMatrix()));
				}
				else
				{
					program->setUniform(UNIFORM_NORMAL, glm::mat3(glm::transpose(glm::inverse(model->getTransform().getMatrix()))));
				}
			}
		}

		program->setUniform(UNIFORM_MODEL, model->getTransform().getMatrix());

		mesh->draw();
	}
}
