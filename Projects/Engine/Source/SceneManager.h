#ifndef _SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_

#include "EngineUtil.h"
#include "BasicScene.h"

namespace ai
{
	class ENGINE_API SceneManager
	{
	public:
		void Update();
		void Release();

		void AddScene(BasicScene* scene);
		void SetMainScene(glm::u32 index);
		void RemoveScene(glm::u32 index);

		BasicScene* GetScene(glm::u32 index);
		BasicScene* operator[](glm::u32 index);

		const std::vector<BasicScene*>& GetScenes() const;
		const BasicScene* GetMainScene() const;

		static SceneManager& GetInstance();

	private:
		std::vector<BasicScene*> mScenes;

		BasicScene* mMainScene;

		SceneManager();
	};
}

#endif
