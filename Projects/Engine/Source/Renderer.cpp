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
#include "MeshRenderer.h"
#include "MaterialUtil.h"
#include "Light.h"
#include "Program.h"

namespace lg
{
	u32 Renderer::smCurrentMeshId = 0;
	u32 Renderer::smCurrentProgramId = 0;
	u32 Renderer::smCurrentMaterialId = 0;
	u32 Renderer::smCurrentTextureId = 0;

	bool Renderer::smIs2dActivated = true;

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

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		disable2d();
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
			drawAll(&mScene->getRootNode());
		}
	}

	void Renderer::drawAll(const Node* node) const
	{
		for (auto it : node->getChildren())
		{
			assert(it != nullptr);

			if (it->isEnabled())
			{
				if (it->getType() == Node::SPRITE)
				{
					enable2d();

					drawSprite(it);
				}
				else
				{
					disable2d();

					drawNode(it);
				}

				drawAll(it);
			}
		}
	}

	void Renderer::drawNode(const Node* node) const
	{
		MeshRenderer* mesh_renderer = node->getRenderer();

		if (mesh_renderer && mesh_renderer->isEnabled())
		{
			Material* material = mesh_renderer->getMaterial();
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

				if (node->getTransform().hasUniformScale())
				{
					program->setUniform(UNIFORM_NORMAL, mat3(node->getTransform().getMatrix()));
				}
				else
				{
					program->setUniform(UNIFORM_NORMAL, mat3(transpose(inverse(node->getTransform().getMatrix()))));
				}
			}

			if (smCurrentMaterialId != material->getId())
			{
				smCurrentMaterialId = material->getId();

				material->uploadUniforms();

				if (material->IsLighted())
				{
					DirectionalLight* light = mScene->getRootNode().getFistChild<DirectionalLight>(Node::DIRECTIONAL_LIGHT);
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

			const Mesh* mesh = mesh_renderer->getMesh();
			assert(mesh != nullptr);

			if (smCurrentMeshId != mesh->getId())
			{
				smCurrentMeshId = mesh->getId();

				mesh->bindVbo();
				mesh->uploadAttributes(program->getAttributes(), 3);
				mesh->bindIbo();
			}

			program->setUniform(UNIFORM_MODEL, node->getTransform().getMatrix());

			mesh->draw();
		}
	}

	void Renderer::drawSprite(const Node* sprite) const
	{
		MeshRenderer* mesh_renderer = sprite->getRenderer();

		if (mesh_renderer && mesh_renderer->isEnabled())
		{
			const Material* material = mesh_renderer->getMaterial();
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

			const Mesh* mesh = mesh_renderer->getMesh();
			assert(mesh != nullptr);

			if (smCurrentMeshId != mesh->getId())
			{
				smCurrentMeshId = mesh->getId();

				mesh->bindVbo();
				mesh->uploadAttributes(program->getAttributes(), 2);
				mesh->bindIbo();
			}

			program->setUniform(UNIFORM_MODEL, sprite->getTransform().getMatrix());

			mesh->draw();
		}
	}

	void Renderer::enable2d()
	{
		if (!smIs2dActivated)
		{
			glEnable(GL_BLEND);
			glDisable(GL_DEPTH_TEST);
	
			smIs2dActivated = true;
		}
	}

	void Renderer::disable2d()
	{
		if (smIs2dActivated)
		{
			glDisable(GL_BLEND);
			glEnable(GL_DEPTH_TEST);

			smIs2dActivated = false;
		}
	}
}
