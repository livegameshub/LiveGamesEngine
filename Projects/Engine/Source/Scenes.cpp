#include "Scenes.h"
#include "Resources.h"
#include "Engine.h"
#include "BasicScene.h"

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
		for (BasicScene* scene : mScenes)
		{
			assert(scene != nullptr);

			scene->release();

			delete scene;
			scene = nullptr;
			
		}
	}

	void Scenes::addScene(BasicScene* scene)
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
		Resources::getInstance().flushPendingItems();

		/* set the scene for the renderer */
		Engine::getInstance().getWindowByIndex(0)->getRenderer().setScene(mMainScene);
	}

	BasicScene* Scenes::getScene(glm::u32 index)
	{
		/* check the bounds for the array */
		assert(index < mScenes.size());
		
		return mScenes[index];
	}

	BasicScene* Scenes::operator[](glm::u32 index)
	{
		return getScene(index);
	}

	const BasicScene* Scenes::getMainScene() const
	{
		return mMainScene;
	}

	const std::vector<BasicScene*>& Scenes::getScenes() const
	{
		return mScenes;
	}

	Scenes& Scenes::getInstance()
	{
		static Scenes instance;

		return instance;
	}
}
