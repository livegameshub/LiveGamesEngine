#ifndef _SCENES_H_
#define _SCENES_H_

#include "EngineUtil.h"

namespace ai
{
	class BasicScene;

	class ENGINE_API Scenes
	{
	public:
		void update();
		void release();

		void addScene(BasicScene* scene);
		void setMainScene(glm::u32 index);
		void removeScene(glm::u32 index);

		BasicScene* getScene(glm::u32 index);
		BasicScene* operator[](glm::u32 index);

		const std::vector<BasicScene*>& getScenes() const;
		const BasicScene* getMainScene() const;

		static Scenes& getInstance();

	private:
		std::vector<BasicScene*> mScenes;

		BasicScene* mMainScene;

		Scenes();
	};
}

#endif // _SCENES_H_
