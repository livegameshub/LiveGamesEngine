#include "SceneManager.h"

namespace ai
{
	SceneManager::SceneManager()
		: mMainScene(nullptr)
	{
	}

	void SceneManager::Update()
	{
		if (mMainScene)
		{
			mMainScene->Update();
		}
	}

	void SceneManager::Release()
	{
		for (BasicScene* scene : mScenes)
		{
			if (scene)
			{
				scene->Release();

				delete scene;
				scene = nullptr;
			}
		}
	}

	void SceneManager::AddScene(BasicScene* scene)
	{
		if (scene)
		{
			mScenes.push_back(scene);
		}
	}

	void SceneManager::RemoveScene(glm::u32 index)
	{
		/* check the bounds for the array */

		if (index >= 0 && index < mScenes.size())
		{
			mScenes[index]->Release();

			mScenes.erase(mScenes.begin() + index);
		}
	}

	void SceneManager::SetMainScene(glm::u32 index)
	{
		BasicScene* new_scene = GetScene(index);

		if (new_scene)
		{
			// init the new scene
			new_scene->Init();

			if (mMainScene)
			{
				// release the old scene
				mMainScene->Release();
			}

			// swap the scenes
			mMainScene = new_scene;
		}
	}

	BasicScene* SceneManager::GetScene(glm::u32 index)
	{
		/* check the bounds for the array */

		if (index >= 0 && index < mScenes.size())
		{
			return mScenes[index];
		}

		return nullptr;
	}

	BasicScene* SceneManager::operator[](glm::u32 index)
	{
		return GetScene(index);
	}

	const BasicScene* SceneManager::GetMainScene() const
	{
		return mMainScene;
	}

	const std::vector<BasicScene*>& SceneManager::GetScenes() const
	{
		return mScenes;
	}

	SceneManager& SceneManager::GetInstance()
	{
		static SceneManager instance;

		return instance;
	}
}
