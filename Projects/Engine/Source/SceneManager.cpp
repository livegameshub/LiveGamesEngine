#include "SceneManager.h"
#include "ResourceManager.h"
#include "Engine.h"

namespace ai
{
	SceneManager::SceneManager()
		: mMainScene(nullptr)
	{
	}

	void SceneManager::update()
	{
		if (mMainScene)
		{
			mMainScene->update();
		}
	}

	void SceneManager::release()
	{
		for (BasicScene* scene : mScenes)
		{
			assert(scene != nullptr);

			scene->release();

			delete scene;
			scene = nullptr;
			
		}
	}

	void SceneManager::addScene(BasicScene* scene)
	{
		assert(scene != nullptr);

		mScenes.push_back(scene);
	}

	void SceneManager::removeScene(glm::u32 index)
	{
		/* check the bounds for the array */
		assert(index < mScenes.size());

		mScenes[index]->release();

		mScenes.erase(mScenes.begin() + index);
	}

	void SceneManager::setMainScene(glm::u32 index)
	{
		BasicScene* new_scene = getScene(index);

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
		ResourceManager::getInstance().flushPendingItems();

		/* set the scene for the renderer */
		Engine::getInstance().getWindowByIndex(0)->getRenderer().setScene(mMainScene);
	}

	BasicScene* SceneManager::getScene(glm::u32 index)
	{
		/* check the bounds for the array */
		assert(index < mScenes.size());
		
		return mScenes[index];
	}

	BasicScene* SceneManager::operator[](glm::u32 index)
	{
		return getScene(index);
	}

	const BasicScene* SceneManager::getMainScene() const
	{
		return mMainScene;
	}

	const std::vector<BasicScene*>& SceneManager::getScenes() const
	{
		return mScenes;
	}

	SceneManager& SceneManager::getInstance()
	{
		static SceneManager instance;

		return instance;
	}
}
