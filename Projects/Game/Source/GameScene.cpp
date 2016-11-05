#include "GameScene.h"
#include "Shader.h"
#include "Resources.h"
#include "Engine.h"
#include "Camera.h"
#include "Sprite.h"
#include "Input.h"
#include "Time.h"
#include "Program.h"
#include "Mesh.h"

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
	lg::Shader* vertexShader = lg::Resources::instance().create<lg::Shader>(lg::Resources::getNextId(), "SpriteShader.vs");
	lg::Shader* fragmentShader = lg::Resources::instance().create<lg::Shader>(lg::Resources::getNextId(), "SpriteShader.fs");
	
	// program
	lg::Program* program = lg::Resources::instance().create<lg::Program>(lg::Resources::getNextId());
	program->addShader(vertexShader);
	program->addShader(fragmentShader);
	
	// mesh
	lg::Mesh* sprite_mesh = lg::Resources::instance().createMesh(lg::Resources::getNextId(), vec2(), vec2(512.0f, 256.0f), vec2(512.0f, 256.0f));
	
	// texture
	//lg::Texture* plane_texture_1 = lg::Resources::instance().createTexture(lg::Resources::getNextId(), "grass_iso_1.texture", true);
	lg::Texture* plane_texture_2 = lg::Resources::instance().create<lg::Texture>(lg::Resources::getNextId(), "grass_iso_3.texture");
	plane_texture_2->GenerateMipMaps(true);
	
	// material
	//lg::Material* sprite_material_1 = lg::Resources::instance().createMaterial<lg::Material>(lg::Resources::getNextId(), program, plane_texture_1, vec3(1.0f));
	lg::Material* sprite_material_2 = lg::Resources::instance().createMaterial<lg::Material>(lg::Resources::getNextId(), program, plane_texture_2, vec3(1.0f));
	
	// camera
	lg::Camera* camera = create<lg::Camera>(1, lg::Node::CAMERA, &mRootNode);
	camera->setViewSize(lg::Engine::instance().getWindowByIndex(0)->getSize());
	camera->moveAt(vec3(0.0f, 0.0f, 7.0f));
	
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
			f32 x = static_cast<f32>(x_position) + (width * static_cast<f32>(c)) + (width * static_cast<f32>(r));
			f32 y = static_cast<f32>(y_position) + (height * static_cast<f32>(c)) - (height * static_cast<f32>(r));

			lg::Sprite* sprite = create<lg::Sprite>(++sprite_id, lg::Node::SPRITE, &mRootNode, vec3(x, y, 0.0f));
			sprite->setRenderer(lg::MeshRenderer::create(sprite_material_2, sprite_mesh));
			sprite->setSize(vec2(512.0f, 256.0f));
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
