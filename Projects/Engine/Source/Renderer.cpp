#include "Renderer.h"
#include "Graphics.h"
#include "MeshRenderer.h"
#include "Camera.h"
#include "Program.h"
#include "Material.h"
#include "Mesh.h"
#include "Scene.h"
#include "DiffuseMaterial.h"
#include "DirectionalLight.h"
#include "Texture.h"
#include "Sprite.h"

namespace lg
{
	glm::u32 Renderer::smCurrentMeshId = 0;
	glm::u32 Renderer::smCurrentProgramId = 0;
	glm::u32 Renderer::smCurrentMaterialId = 0;
	glm::u32 Renderer::smCurrentTextureId = 0;

	bool Renderer::smIsDrawing2d = false;

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

	void Renderer::setScene(const Scene* scene)
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
				if (node_instance->isVisible())
				{
					if (node_instance->getType() == Node::MESH_RENDERER)
					{
						MeshRenderer* model = static_cast<MeshRenderer*>(node_instance);

						disable2dDrawing();
						drawRenderable(model);
					}
					else if (node_instance->getType() == Node::SPRITE)
					{
						Sprite* sprite = static_cast<Sprite*>(node_instance);

						enable2dDrawing();
						drawSprite(sprite);
					}
				}
				else
				{
					drawNode(node_instance);
				}
			}
		}
	}

	void Renderer::drawSprite(const Sprite* sprite) const
	{
		const Material* material = sprite->getMaterial();
		assert(material != nullptr);

		const Program* program = material->getProgram();
		assert(program != nullptr);

		if (smCurrentProgramId != program->getId())
		{
			smCurrentProgramId = program->getId();

			program->use();
		}

		const Camera* camera = mScene->getRootNode().getFistChild<Camera>(Node::CAMERA);
		assert(camera != nullptr);

		program->setUniform(UNIFORM_PROJECTION, camera->getOrthoMatrix());

		if (smCurrentMaterialId != material->getId())
		{
			smCurrentMaterialId = material->getId();

			material->uploadUniforms();
		}

		const Texture* texture = material->getDiffuseTexture();
		assert(texture != nullptr);

		if (smCurrentTextureId != texture->getId())
		{
			smCurrentTextureId = texture->getId();

			texture->bind();
		}

		const Mesh* mesh = sprite->getMesh();
		assert(mesh != nullptr);

		if (smCurrentMeshId != mesh->getId())
		{
			smCurrentMeshId = mesh->getId();

			mesh->bindVbo();
			mesh->uploadAttributes(program->getAttributes());
			mesh->bindIbo();
		}

		program->setUniform(UNIFORM_MODEL, sprite->getTransform().getMatrix());

		mesh->draw();
	}

	void Renderer::drawRenderable(const MeshRenderer* model) const
	{
		Material* material = model->getMaterial();
		assert(material != nullptr);

		const Program* program = material->getProgram();
		assert(program != nullptr);

		if (smCurrentProgramId != program->getId())
		{
			smCurrentProgramId = program->getId();

			program->use();
		}

		const Camera* camera = mScene->getRootNode().getFistChild<Camera>(Node::CAMERA);
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

		if (smCurrentMaterialId != material->getId())
		{
			smCurrentMaterialId = material->getId();

			material->uploadUniforms();

			if (material->IsLighted())
			{
				DirectionalLight* light = mScene->getRootNode().getFistChild<DirectionalLight>(Node::LIGHT);
				assert(light != nullptr);

				static_cast<DiffuseMaterial*>(material)->uploadUniforms(light);

				program->setUniform(UNIFORM_AMBIENT_LIGHT, mScene->getAmbientLight());
			}
		}

		if (material->IsTextured())
		{
			const Texture* texture = static_cast<DiffuseMaterial*>(material)->getDiffuseTexture();
			assert(texture != nullptr);

			if (smCurrentTextureId != texture->getId())
			{
				smCurrentTextureId = texture->getId();

				texture->bind();
			}
		}

		const Mesh* mesh = model->getMesh();
		assert(mesh != nullptr);

		if (smCurrentMeshId != mesh->getId())
		{
			smCurrentMeshId = mesh->getId();

			mesh->bindVbo();
			mesh->uploadAttributes(program->getAttributes());
			mesh->bindIbo();
		}

		program->setUniform(UNIFORM_MODEL, model->getTransform().getMatrix());

		mesh->draw();
	}

	void Renderer::enable2dDrawing()
	{
		if (!smIsDrawing2d)
		{
			glEnable(GL_BLEND);

			glDisable(GL_DEPTH_TEST);
			//glDisable(GL_MULTISAMPLE);

			smIsDrawing2d = true;
		}
	}

	void Renderer::disable2dDrawing()
	{
		if (smIsDrawing2d)
		{
			glDisable(GL_BLEND);

			glEnable(GL_DEPTH_TEST);
			//glEnable(GL_MULTISAMPLE);

			smIsDrawing2d = false;
		}
	}
}

