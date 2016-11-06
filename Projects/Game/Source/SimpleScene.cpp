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

SimpleScene::SimpleScene(const vec3& ambientLight)
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
	// shaders 
	lg::Program* program = lg::Resources::instance().getResource<lg::Program>(7);
	
	// meshes
	lg::Mesh* point_mesh = new lg::Mesh(lg::Resources::getNextId(), lg::Mesh::POINTS, lg::Mesh::STATIC_DRAW, sizeof(vec3), lg::Mesh::REMOVE_DATA);
	lg::Mesh* line_mesh = new lg::Mesh(lg::Resources::getNextId(), lg::Mesh::LINES, lg::Mesh::STATIC_DRAW, sizeof(vec3), lg::Mesh::REMOVE_DATA);
	lg::Mesh* triangle_mesh = new lg::Mesh(lg::Resources::getNextId(), lg::Mesh::TRIANGLES, lg::Mesh::STATIC_DRAW, sizeof(vec3), lg::Mesh::REMOVE_DATA);
	
	lg::MeshData& point_data = point_mesh->getData();
	lg::MeshData& line_data = line_mesh->getData(); 
	lg::MeshData& triangle_data = triangle_mesh->getData();
	
	point_data.addVertex(vec3());
	point_data.addPoint(0);
	
	line_data.addVertex(vec3(-1.0f, 0.0f, 0.0f));
	line_data.addVertex(vec3(1.0f, 0.0f, 0.0f));
	line_data.addLine(0, 1);
	
	
	triangle_data.addVertex(vec3(-1.0f, 0.0f, 0.0f));
	triangle_data.addVertex(vec3(1.0f, 0.0f, 0.0f));
	triangle_data.addVertex(vec3(0.0f, 1.0f, 0.0f));
	triangle_data.addTriangle(0, 1, 2);

	lg::Resources::instance().add(point_mesh);
	lg::Resources::instance().add(line_mesh);
	lg::Resources::instance().add(triangle_mesh);
	
	// materials
	lg::Material* red_material =  lg::Resources::instance().createMaterial<lg::Material>(lg::Resources::getNextId(), program, nullptr, vec3(1.0f, 0.0f, 0.0f));
	lg::Material* yellow_material = lg::Resources::instance().createMaterial<lg::Material>(lg::Resources::getNextId(), program, nullptr, vec3(1.0f, 1.0f, 0.0f));
	lg::Material* blue_material = lg::Resources::instance().createMaterial<lg::Material>(lg::Resources::getNextId(), program, nullptr, vec3(0.0f, 0.0f, 1.0f));
	
	// camera 
	mCamera = create<lg::Camera>(1, lg::Node::CAMERA, &mRootNode);
	mCamera->setSize(lg::Engine::instance().getWindowByIndex(0)->getSize());
	mCamera->moveAt(vec3(0.0f, 0.0f, 7.0f));
	
	// models
	mPrimitives.push_back(create<lg::Node>(2, lg::Node::MODEL, &mRootNode, vec3(-3.5f, 0.0f, 0.0f)));
	mPrimitives.push_back(create<lg::Node>(3, lg::Node::MODEL, &mRootNode));
	mPrimitives.push_back(create<lg::Node>(4, lg::Node::MODEL, &mRootNode, vec3(3.5f, 0.0f, 0.0f)));

	mPrimitives[0]->setRenderer(new lg::MeshRenderer(blue_material, point_mesh));
	mPrimitives[1]->setRenderer(new lg::MeshRenderer(yellow_material, line_mesh));
	mPrimitives[2]->setRenderer(new lg::MeshRenderer(red_material, triangle_mesh));

	/* call the basic init function */
	//Scene::init();
}

void SimpleScene::update()
{
	static f32 cameraAngle = 0.0f;
	static f32 speed = 10.0f;
	
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

	/* call the basic update function */
	Scene::update();

	if (lg::Input::isKeyDown(GLFW_KEY_SPACE))
	{
		lg::Engine::loadScene(3);
	}
}
