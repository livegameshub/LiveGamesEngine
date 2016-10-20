#include "Renderer.h"
#include "Graphics.h"
#include "Model.h"
#include "Camera.h"
#include "Program.h"
#include "Material.h"
#include "Mesh.h"
#include "Scene.h"
#include "RendererState.h"
#include "DiffuseMaterial.h"
#include "DirectionalLight.h"

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

	void Renderer::setScene(Scene* scene)
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

	void Renderer::drawNode(const Node* node) const
	{
		for (auto node_instance : node->getChildren())
		{
			assert(node_instance != nullptr);

			if (node_instance->isEnabled())
			{
				if (node_instance->getNodeType() == Node::MODEL_NODE)
				{
					Model* model = static_cast<Model*>(node_instance);

					if (model->isVisible())
					{
						drawModel(model);
					}
				}

				drawNode(node_instance);
			}
		}
	}

	void Renderer::drawModel(const Model* model) const
	{
		Material* material = model->getMaterial();
		assert(material != nullptr);

		const Program* program = material->getProgram();
		assert(program != nullptr);

		if (RendererState::checkProgramId(program->getId()))
		{
			program->use();
		}

		const Camera* camera = mScene->getCameraByIndex(0);
		assert(camera != nullptr);

		program->setUniform(UNIFORM_VIEW, camera->getViewMatrix());
		program->setUniform(UNIFORM_PROJECTION, camera->getPerspecitiveMatrix());

		if (material->IsLighted())
		{
			program->setUniform(UNIFORM_CAMERA_POSITION, camera->getTransform().getPosition());

			if (model->getTransform().hasUniformScale())
			{
				program->setUniform(UNIFORM_NORMAL, glm::mat3(model->getTransform().getMatrix()));
			}
			else
			{
				program->setUniform(UNIFORM_NORMAL, glm::mat3(glm::transpose(glm::inverse(model->getTransform().getMatrix()))));
			}
		}

		if (RendererState::checkMaterialId(material->getId()))
		{
			material->uploadUniforms();

			if (material->IsLighted())
			{
				program->setUniform(UNIFORM_AMBIENT_LIGHT, mScene->getAmbientLight());

				static_cast<DiffuseMaterial*>(material)->uploadUniforms(static_cast<DirectionalLight*>(mScene->getLightByIndex(0)));
			}
		}

		const Mesh* mesh = model->getMesh();
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
