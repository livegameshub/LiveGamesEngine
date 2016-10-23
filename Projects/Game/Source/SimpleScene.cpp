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
	ai::Program* program = static_cast<ai::Program*>(ai::Resources::getInstance().getResource(7));

	// meshes

	ai::Mesh* point_mesh = ai::Resources::getInstance().createMesh(ai::Resources::getNextAvailableId(), ai::Mesh::POINTS_MESH, ai::Mesh::STATIC_MESH_DRAW, ai::Mesh::MESH_REMOVE_DATA_FLAG);
	ai::Mesh* line_mesh = ai::Resources::getInstance().createMesh(ai::Resources::getNextAvailableId(), ai::Mesh::LINES_MESH, ai::Mesh::STATIC_MESH_DRAW, ai::Mesh::MESH_REMOVE_DATA_FLAG);
	ai::Mesh* triangle_mesh = ai::Resources::getInstance().createMesh(ai::Resources::getNextAvailableId(), ai::Mesh::TRIANGLES_MESH, ai::Mesh::STATIC_MESH_DRAW, ai::Mesh::MESH_REMOVE_DATA_FLAG);

	ai::MeshData& point_data = point_mesh->getData();
	ai::MeshData& line_data = line_mesh->getData(); 
	ai::MeshData& triangle_data = triangle_mesh->getData();

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

	ai::Material* red_material =  ai::Resources::getInstance().createMaterial(ai::Resources::getNextAvailableId(), program, glm::vec3(1.0f, 0.0f, 0.0f));
	ai::Material* yellow_material = ai::Resources::getInstance().createMaterial(ai::Resources::getNextAvailableId(), program, glm::vec3(1.0f, 1.0f, 0.0f));
	ai::Material* blue_material = ai::Resources::getInstance().createMaterial(ai::Resources::getNextAvailableId(), program, glm::vec3(0.0f, 0.0f, 1.0f));

	// camera 

	mCamera = createCamera(1, ai::Engine::getInstance().getWindowByIndex(0)->getSize(), glm::vec3(0.0f, 0.0f, 7.0f));
	mRootNode.addChild(mCamera);

	// models

	mPrimitives.push_back(createModel(2, point_mesh, blue_material));
	mPrimitives.push_back(createModel(3, line_mesh, yellow_material));
	mPrimitives.push_back(createModel(4, triangle_mesh, red_material));
	
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

	if (ai::Input::isKeyDown(GLFW_KEY_UP))
	{
		mCamera->moveForward(speed * ai::Time::getDeltaTime());
	}
	else if (ai::Input::isKeyDown(GLFW_KEY_DOWN))
	{
		mCamera->moveForward(-speed * ai::Time::getDeltaTime());
	}

	if (ai::Input::isKeyDown(GLFW_KEY_RIGHT))
	{
		cameraAngle -= ai::Time::getDeltaTime() * 75.0f;

		mCamera->rotateOnY(cameraAngle);
	}
	else if (ai::Input::isKeyDown(GLFW_KEY_LEFT))
	{
		cameraAngle += ai::Time::getDeltaTime() * 75.0f;

		mCamera->rotateOnY(cameraAngle);
	}
}
