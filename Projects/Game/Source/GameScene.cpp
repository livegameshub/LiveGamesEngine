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
	Scene::init();

	// scale the scene a little bit
	mScaleFactor = 0.6f;
	mRootNode.getTransform().Scale(glm::vec3(mScaleFactor));
	
	// shaders
	lg::Shader* vertexShader = lg::Resources::getInstance().createShader(lg::Resources::getNextAvailableId(), lg::Shader::VERTEX, "SpriteShader.vs");
	lg::Shader* fragmentShader = lg::Resources::getInstance().createShader(lg::Resources::getNextAvailableId(), lg::Shader::FRAGMENT, "SpriteShader.fs");

	// program
	lg::Program* program = lg::Resources::getInstance().createProgram(lg::Resources::getNextAvailableId(), { vertexShader, fragmentShader });

	// mesh
	lg::Mesh* sprite_mesh = lg::Resources::getInstance().createMesh(lg::Resources::getNextAvailableId(), glm::vec2(), glm::vec2(512.0f, 256.0f), glm::vec2(512.0f, 256.0f));

	// texture
	//lg::Texture* plane_texture_1 = lg::Resources::getInstance().createTexture(lg::Resources::getNextAvailableId(), "grass_iso_1.texture", true);
	lg::Texture* plane_texture_2 = lg::Resources::getInstance().createTexture(lg::Resources::getNextAvailableId(), "grass_iso_3.texture", true);

	// material
	//lg::Material* sprite_material_1 = lg::Resources::getInstance().createMaterial<lg::Material>(lg::Resources::getNextAvailableId(), program, plane_texture_1, glm::vec3(1.0f));
	lg::Material* sprite_material_2 = lg::Resources::getInstance().createMaterial<lg::Material>(lg::Resources::getNextAvailableId(), program, plane_texture_2, glm::vec3(1.0f));

	// camera
	lg::Camera* camera = createCamera(1, lg::Engine::getInstance().getWindowByIndex(0)->getSize(), glm::vec3(0.0f, 0.0f, 7.0f));
	mRootNode.addChild(camera);

	// useful variables
	glm::i32 r_max = 3;
	glm::i32 c_max = 3;

	glm::i32 sprite_id = 1;

	glm::f32 width = 216.0f;
	glm::f32 height = 96.0f;

	glm::f32 x_position = (camera->getViewSize().x / 2.0f) - (static_cast<glm::f32>(r_max) * height) / 2.0f;
	glm::f32 y_position = (camera->getViewSize().y / 2.0f) + (static_cast<glm::f32>(c_max) * height) / 2.0f;

	// create the level
	for (glm::i32 r = r_max; r > 0; --r)
	{
		for (glm::i32 c = 0; c < c_max; ++c)
		{
			lg::Sprite* sprite = createSprite(++sprite_id, sprite_mesh, sprite_material_2, glm::vec2(512.0f, 256.0f));

			sprite->getTransform().setPosition(glm::vec3(static_cast<glm::f32>(x_position) + (width * static_cast<glm::f32>(c)) + (width * static_cast<glm::f32>(r)),
														 static_cast<glm::f32>(y_position) + (height * static_cast<glm::f32>(c)) - (height * static_cast<glm::f32>(r)),
														 0.0f));

			mRootNode.addChild(sprite);
		}
	}
}

void GameScene::update()
{
	Scene::update();

#ifdef _DEBUG

	if (lg::Input::isKeyDown(GLFW_KEY_EQUAL))
	{
		mScaleFactor += 1.5f * lg::Time::getDeltaTime();

		mRootNode.getTransform().Scale(glm::vec3(mScaleFactor));
	}
	else if (lg::Input::isKeyDown(GLFW_KEY_MINUS))
	{
		mScaleFactor -= 1.5 * lg::Time::getDeltaTime();

		mRootNode.getTransform().Scale(glm::vec3(mScaleFactor));
	}

	if (lg::Input::isKeyDown(GLFW_KEY_RIGHT))
	{
		mRootNode.getTransform().translate(glm::vec3(-150.0f, 0.0f, 0.0f) * lg::Time::getDeltaTime());
	}
	else if (lg::Input::isKeyDown(GLFW_KEY_LEFT))
	{
		mRootNode.getTransform().translate(glm::vec3(150.0f, 0.0f, 0.0f) * lg::Time::getDeltaTime());
	}
	else if (lg::Input::isKeyDown(GLFW_KEY_UP))
	{
		mRootNode.getTransform().translate(glm::vec3(0.0f, 150.0f, 0.0f) * lg::Time::getDeltaTime());
	}
	else if (lg::Input::isKeyDown(GLFW_KEY_DOWN))
	{
		mRootNode.getTransform().translate(glm::vec3(0.0f, -150.0f, 0.0f) * lg::Time::getDeltaTime());
	}

#endif
}
