#ifndef _SCENES_H_
#define _SCENES_H_

#include "EngineUtil.h"

namespace lg
{
	class Scene;

	class ENGINE_API Scenes
	{
	public:
		void update();
		void release();

		void addScene(Scene* scene);
		void setMainScene(glm::u32 index);
		void removeScene(glm::u32 index);

		Scene* getScene(glm::u32 index);
		Scene* operator[](glm::u32 index);

		const std::vector<Scene*>& getScenes() const;
		const Scene* getMainScene() const;

		static Scenes& getInstance();

	private:
		std::vector<Scene*> mScenes;

		Scene* mMainScene;

		Scenes();
	};
}

#endif // _SCENES_H_
