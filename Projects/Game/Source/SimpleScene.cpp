#include "SimpleScene.h"
#include "Shader.h"
#include "Engine.h"
#include "Window.h"
#include "Resources.h"
#include "Time.h"
#include "Input.h"
#include "Scenes.h"
#include "DiffuseMaterial.h"
#include "DirectionalLight.h"
#include "Mesh.h"
#include "MeshData.h"
#include "Program.h"

SimpleScene::SimpleScene()
	: mDirectionalLight(nullptr)
	, mCamera(nullptr)
{
}

SimpleScene::SimpleScene(const glm::vec3& ambientLight)
	: Scene(ambientLight)
	, mDirectionalLight(nullptr)
	, mCamera(nullptr)
{
}

SimpleScene::~SimpleScene()
{
}

void SimpleScene::init()
{
	/* call the basic init function */
	Scene::init();

	// shaders 
	lg::Program* program = static_cast<lg::Program*>(lg::Resources::getInstance().getResource(7));

	// meshes

	lg::Mesh* point_mesh = lg::Resources::getInstance().createMesh(lg::Resources::getNextAvailableId(), lg::Mesh::POINTS_MESH, lg::Mesh::STATIC_MESH_DRAW, lg::Mesh::MESH_REMOVE_DATA_FLAG);
	lg::Mesh* line_mesh = lg::Resources::getInstance().createMesh(lg::Resources::getNextAvailableId(), lg::Mesh::LINES_MESH, lg::Mesh::STATIC_MESH_DRAW, lg::Mesh::MESH_REMOVE_DATA_FLAG);
	lg::Mesh* triangle_mesh = lg::Resources::getInstance().createMesh(lg::Resources::getNextAvailableId(), lg::Mesh::TRIANGLES_MESH, lg::Mesh::STATIC_MESH_DRAW, lg::Mesh::MESH_REMOVE_DATA_FLAG);

	lg::MeshData& point_data = point_mesh->getData();
	lg::MeshData& line_data = line_mesh->getData(); 
	lg::MeshData& triangle_data = triangle_mesh->getData();

	point_data.addVertex(glm::vec3());
	point_data.addPoint(0);

	line_data.addVertex(glm::vec3(-1.0f, 0.0f, 0.0f));
	line_data.addVertex(glm::vec3(1.0f, 0.0f, 0.0f));
	line_data.addLine(0, 1);

	
	triangle_data.addVertex(glm::vec3(-1.0f, 0.0f, 0.0f));
	triangle_data.addVertex(glm::vec3(1.0f, 0.0f, 0.0f));
	triangle_data.addVertex(glm::vec3(0.0f, 1.0f, 0.0f));
	triangle_data.addTriangle(0, 1, 2);

	// materials

	lg::Material* red_material =  lg::Resources::getInstance().createMaterial(lg::Resources::getNextAvailableId(), program, glm::vec3(1.0f, 0.0f, 0.0f));
	lg::Material* yellow_material = lg::Resources::getInstance().createMaterial(lg::Resources::getNextAvailableId(), program, glm::vec3(1.0f, 1.0f, 0.0f));
	lg::Material* blue_material = lg::Resources::getInstance().createMaterial(lg::Resources::getNextAvailableId(), program, glm::vec3(0.0f, 0.0f, 1.0f));

	// camera 

	mCamera = createCamera(1, lg::Engine::getInstance().getWindowByIndex(0)->getSize(), glm::vec3(0.0f, 0.0f, 7.0f));
	mRootNode.addChild(mCamera);

	// models

	mPrimitives.push_back(createRenderable(2, point_mesh, blue_material));
	mPrimitives.push_back(createRenderable(3, line_mesh, yellow_material));
	mPrimitives.push_back(createRenderable(4, triangle_mesh, red_material));
	
	mPrimitives[0]->getTransform().setPosition(glm::vec3(-3.5f, 0.0f, 0.0f));
	mPrimitives[2]->getTransform().setPosition(glm::vec3(3.5f, 0.0f, 0.0f));

	for (auto primitive : mPrimitives)
	{
		mRootNode.addChild(primitive);
	}

	// light

	mDirectionalLight = createDirectionalLight(5, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(1.0f), glm::vec3(0.5f));
	mRootNode.addChild(mDirectionalLight);
}

void SimpleScene::update()
{
	/* call the basic update function */

	Scene::update();

	static glm::f32 cameraAngle = 0.0f;
	static glm::f32 speed = 10.0f;

	if (lg::Input::isKeyDown(GLFW_KEY_UP))
	{
		mCamera->moveForward(speed * lg::Time::getDeltaTime());
	}
	else if (lg::Input::isKeyDown(GLFW_KEY_DOWN))
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
}
