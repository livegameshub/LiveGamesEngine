#include "GameScene.h"
#include "Shader.h"
#include "Resources.h"
#include "Engine.h"
#include "Camera.h"
#include "Sprite.h"
#include "Input.h"
#include "Time.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::init()
{
	// scale the scene a little bit
	mScaleFactor = 0.6f;
	mRootNode.getTransform().Scale(vec3(mScaleFactor));
	
	// shaders
	lg::Shader* vertexShader = lg::Resources::getInstance().createShader(lg::Resources::getNextAvailableId(), lg::Shader::VERTEX, "SpriteShader.vs");
	lg::Shader* fragmentShader = lg::Resources::getInstance().createShader(lg::Resources::getNextAvailableId(), lg::Shader::FRAGMENT, "SpriteShader.fs");
	
	// program
	lg::Program* program = lg::Resources::getInstance().createProgram(lg::Resources::getNextAvailableId(), { vertexShader, fragmentShader });
	
	// mesh
	lg::Mesh* sprite_mesh = lg::Resources::getInstance().createMesh(lg::Resources::getNextAvailableId(), vec2(), vec2(512.0f, 256.0f), vec2(512.0f, 256.0f));
	
	// texture
	//lg::Texture* plane_texture_1 = lg::Resources::getInstance().createTexture(lg::Resources::getNextAvailableId(), "grass_iso_1.texture", true);
	lg::Texture* plane_texture_2 = lg::Resources::getInstance().createTexture(lg::Resources::getNextAvailableId(), "grass_iso_3.texture", true);
	
	// material
	//lg::Material* sprite_material_1 = lg::Resources::getInstance().createMaterial<lg::Material>(lg::Resources::getNextAvailableId(), program, plane_texture_1, vec3(1.0f));
	lg::Material* sprite_material_2 = lg::Resources::getInstance().createMaterial<lg::Material>(lg::Resources::getNextAvailableId(), program, plane_texture_2, vec3(1.0f));
	
	// camera
	lg::Camera* camera = createNode<lg::Camera>(1, lg::Node::CAMERA);
	camera->setViewSize(lg::Engine::getInstance().getWindowByIndex(0)->getSize());
	camera->moveAt(vec3(0.0f, 0.0f, 7.0f));
	mRootNode.addChild(camera);
	
	// useful variables
	i32 r_max = 3;
	i32 c_max = 3;
	
	i32 sprite_id = 1;
	
	f32 width = 216.0f;
	f32 height = 96.0f;
	
	f32 x_position = (camera->getViewSize().x / 2.0f) - (static_cast<f32>(r_max) * height) / 2.0f;
	f32 y_position = (camera->getViewSize().y / 2.0f) + (static_cast<f32>(c_max) * height) / 2.0f;
	
	// create the level
	for (i32 r = r_max; r > 0; --r)
	{
		for (i32 c = 0; c < c_max; ++c)
		{
			lg::Sprite* sprite = createNode<lg::Sprite>(++sprite_id, lg::Node::SPRITE);
			sprite->setRenderer(lg::MeshRenderer::create(sprite_material_2, sprite_mesh));
			sprite->setSize(vec2(512.0f, 256.0f));

			sprite->getTransform().setPosition(vec3(static_cast<f32>(x_position) + (width * static_cast<f32>(c)) + (width * static_cast<f32>(r)),
													static_cast<f32>(y_position) + (height * static_cast<f32>(c)) - (height * static_cast<f32>(r)),
													0.0f));
	
			mRootNode.addChild(sprite);
		}
	}
}

void GameScene::update()
{
#ifdef _DEBUG

	if (lg::Input::isKeyDown(GLFW_KEY_EQUAL))
	{
		mScaleFactor += 1.5f * lg::Time::getDeltaTime();
	
		mRootNode.getTransform().Scale(vec3(mScaleFactor));
	}
	else if (lg::Input::isKeyDown(GLFW_KEY_MINUS))
	{
		mScaleFactor -= 1.5 * lg::Time::getDeltaTime();
	
		mRootNode.getTransform().Scale(vec3(mScaleFactor));
	}
	
	if (lg::Input::isKeyDown(GLFW_KEY_RIGHT))
	{
		mRootNode.getTransform().translate(vec3(-150.0f, 0.0f, 0.0f) * lg::Time::getDeltaTime());
	}
	else if (lg::Input::isKeyDown(GLFW_KEY_LEFT))
	{
		mRootNode.getTransform().translate(vec3(150.0f, 0.0f, 0.0f) * lg::Time::getDeltaTime());
	}
	else if (lg::Input::isKeyDown(GLFW_KEY_UP))
	{
		mRootNode.getTransform().translate(vec3(0.0f, 150.0f, 0.0f) * lg::Time::getDeltaTime());
	}
	else if (lg::Input::isKeyDown(GLFW_KEY_DOWN))
	{
		mRootNode.getTransform().translate(vec3(0.0f, -150.0f, 0.0f) * lg::Time::getDeltaTime());
	}

#endif

	Scene::update();
}
