#include "Scenes.h"
#include "Resources.h"
#include "Engine.h"
#include "Scene.h"
#include "Input.h"

namespace ai
{
	Scenes::Scenes()
		: mMainScene(nullptr)
	{
	}

	void Scenes::update()
	{
		if (mMainScene)
		{
			mMainScene->update();
		}
	}

	void Scenes::release()
	{
		for (Scene* scene : mScenes)
		{
			assert(scene != nullptr);

			scene->release();

			delete scene;
			scene = nullptr;
		}
	}

	void Scenes::addScene(Scene* scene)
	{
		assert(scene != nullptr);

		mScenes.push_back(scene);
	}

	void Scenes::removeScene(glm::u32 index)
	{
		/* check the bounds for the array */
		assert(index < mScenes.size());

		mScenes[index]->release();

		mScenes.erase(mScenes.begin() + index);
	}

	void Scenes::setMainScene(glm::u32 index)
	{
		Scene* new_scene = getScene(index);

		assert(new_scene != nullptr);
		
		// init the new scene
		new_scene->init();
		
		if (mMainScene)
		{
			// release the old scene
			mMainScene->release();
		}

		// swap the scenes
		mMainScene = new_scene;

		/* process the resources */
		Resources::getInstance().flushPendingItems();

		/* set the scene for the renderer */
		Engine::getInstance().getWindowByIndex(0)->getRenderer().setScene(mMainScene);

		/* reset the input */
		Input::reset();
	}

	Scene* Scenes::getScene(glm::u32 index)
	{
		/* check the bounds for the array */
		assert(index < mScenes.size());
		
		return mScenes[index];
	}

	Scene* Scenes::operator[](glm::u32 index)
	{
		return getScene(index);
	}

	const Scene* Scenes::getMainScene() const
	{
		return mMainScene;
	}

	const std::vector<Scene*>& Scenes::getScenes() const
	{
		return mScenes;
	}

	Scenes& Scenes::getInstance()
	{
		static Scenes instance;

		return instance;
	}
}