#include "CubesScene.h"
#include "Shader.h"
#include "Engine.h"
#include "Window.h"
#include "Resources.h"
#include "Time.h"
#include "Input.h"
#include "Scenes.h"
#include "DiffuseMaterial.h"
#include "DirectionalLight.h"
#include "Sprite.h"
#include "Texture.h"

CubesScene::CubesScene()
	: mDirectionalLight(nullptr)
	, mCamera(nullptr)
{
}

CubesScene::CubesScene(const glm::vec3& ambientLight)
	: Scene(ambientLight)
	, mDirectionalLight(nullptr)
	, mCamera(nullptr)
{
}

CubesScene::~CubesScene()
{
}

void CubesScene::init()
{
	/* call the basic init function */
	Scene::init();

	// shaders 

	lg::Shader* vertexShader = lg::Resources::getInstance().createShader(lg::Resources::getNextAvailableId(), lg::Shader::VERTEX_SHADER, "BasicShader.vs");
	lg::Shader* fragmentShader = lg::Resources::getInstance().createShader(lg::Resources::getNextAvailableId(), lg::Shader::FRAGMENT_SHADER, "BasicShader.fs");

	lg::Shader* vertexShader2 = lg::Resources::getInstance().createShader(lg::Resources::getNextAvailableId(), lg::Shader::VERTEX_SHADER, "DiffuseShader.vs");
	lg::Shader* fragmentShader2 = lg::Resources::getInstance().createShader(lg::Resources::getNextAvailableId(), lg::Shader::FRAGMENT_SHADER, "DiffuseShader.fs");

	lg::Shader* vertexShader3 = lg::Resources::getInstance().createShader(lg::Resources::getNextAvailableId(), lg::Shader::VERTEX_SHADER, "DiffuseTextureShader.vs");
	lg::Shader* fragmentShader3 = lg::Resources::getInstance().createShader(lg::Resources::getNextAvailableId(), lg::Shader::FRAGMENT_SHADER, "DiffuseTextureShader.fs");

	// programs

	lg::Program* program = lg::Resources::getInstance().createProgram(lg::Resources::getNextAvailableId(), { vertexShader, fragmentShader });
	lg::Program* program2 = lg::Resources::getInstance().createProgram(lg::Resources::getNextAvailableId(), { vertexShader2, fragmentShader2 });
	lg::Program* program3 = lg::Resources::getInstance().createProgram(lg::Resources::getNextAvailableId(), { vertexShader3, fragmentShader3 });

	// textures

	lg::Texture* plane_texture = lg::Resources::getInstance().createTexture(lg::Resources::getNextAvailableId(), "floor.texture", false);

	// meshes

	lg::Mesh* cube_mesh = lg::Resources::getInstance().createMesh(lg::Resources::getNextAvailableId(), "Cube.mesh");
	lg::Mesh* cube_mesh2 = lg::Resources::getInstance().createMesh(lg::Resources::getNextAvailableId(), "Cube2.mesh");
	lg::Mesh* plane_mesh = lg::Resources::getInstance().createMesh(lg::Resources::getNextAvailableId(), "Plane.mesh");

	// materials

	lg::Material* red_material = lg::Resources::getInstance().createMaterial<lg::Material>(lg::Resources::getNextAvailableId(), program, nullptr, glm::vec3(1.0f, 0.0f, 0.0f));
	lg::DiffuseMaterial* yellow_material = lg::Resources::getInstance().createMaterial<lg::DiffuseMaterial>(lg::Resources::getNextAvailableId(), program2, nullptr, glm::vec3(1.0f, 1.0f, 0.0f), lg::Material::IS_LIGHTED);
	lg::DiffuseMaterial* blue_material = lg::Resources::getInstance().createMaterial<lg::DiffuseMaterial>(lg::Resources::getNextAvailableId(), program2, nullptr, glm::vec3(0.0f, 0.0f, 1.0f), lg::Material::IS_SHINY | lg::Material::IS_LIGHTED);
	lg::DiffuseMaterial* plane_material = lg::Resources::getInstance().createMaterial<lg::DiffuseMaterial>(lg::Resources::getNextAvailableId(), program3, plane_texture, glm::vec3(1.0f), lg::Material::IS_SHINY | lg::Material::IS_TEXTURED | lg::Material::IS_LIGHTED);

	// camera 

	mCamera = createCamera(1, lg::Engine::getInstance().getWindowByIndex(0)->getSize(), glm::vec3(0.0f, 0.0f, 7.0f));
	mRootNode.addChild(mCamera);

	// models

	lg::MeshRenderer* plane = createRenderable(2, plane_mesh, plane_material);

	lg::Transform& plane_transform = plane->getTransform();
	plane_transform.setScale(glm::vec3(8.0f));
	plane_transform.translate(glm::vec3(0.0f, -1.5f, 0.0f));
	plane_transform.rotateOnX(270.0f);

	mRootNode.addChild(plane);

	mCubes.push_back(createRenderable(3, cube_mesh2, blue_material));
	mCubes.push_back(createRenderable(4, cube_mesh2, yellow_material));
	mCubes.push_back(createRenderable(5, cube_mesh, red_material));

	mCubes[0]->getTransform().setPosition(glm::vec3(-3.5f, 0.0f, 0.0f));
	mCubes[2]->getTransform().setPosition(glm::vec3(3.5f, 0.0f, 0.0f));

	for (auto cube : mCubes)
	{
		mRootNode.addChild(cube);
	}

	// light

	mDirectionalLight = createDirectionalLight(7, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(1.0f), glm::vec3(0.5f));
	mRootNode.addChild(mDirectionalLight);
}

void CubesScene::update()
{
	/* call the basic update function */

	Scene::update();

	static glm::f32 cameraAngle = 0.0f;
	static glm::f32 angle = 0.0f;
	static glm::f32 speed = 10.0f;

	angle += lg::Time::getDeltaTime() * 20.0f;

	for (auto cube : mCubes)
	{
		cube->getTransform().rotateOnY(angle);
	}

	if (angle > 360.0f)
	{
		angle -= 360.0f;
	}

	if (lg::Input::isKeyDown(GLFW_KEY_UP))
	{
		mCamera->moveForward(speed * lg::Time::getDeltaTime());
	}
	else if(lg::Input::isKeyDown(GLFW_KEY_DOWN))
	{
		mCamera->moveForward(-speed * lg::Time::getDeltaTime());
	}

	if (lg::Input::isKeyDown(GLFW_KEY_RIGHT))
	{
		cameraAngle -= lg::Time::getDeltaTime() * 75.0f;

		mCamera->rotateOnY(cameraAngle);
	}
	else if (lg::Input::isKeyDown(GLFW_KEY_LEFT))
	{
		cameraAngle += lg::Time::getDeltaTime() * 75.0f;

		mCamera->rotateOnY(cameraAngle);
	}
			

	if (lg::Input::isKeyDown(GLFW_KEY_SPACE))
	{
		lg::Engine::loadScene(1);
	}
}
