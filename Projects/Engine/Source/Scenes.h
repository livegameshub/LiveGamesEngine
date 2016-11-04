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
		void setMainScene(u32 index);
		void removeScene(u32 index);

		Scene* getScene(u32 index);
		Scene* operator[](u32 index);

		const vector<Scene*>& getScenes() const;
		const Scene* getMainScene() const;

		static Scenes& getInstance();

	private:
		vector<Scene*> mScenes;

		Scene* mMainScene;

		Scenes();
	};
}

#endif // _SCENES_H_
