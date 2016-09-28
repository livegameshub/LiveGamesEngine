#ifndef _TEST_SCENE_H_
#define _TEST_SCENE_H_

#include "BasicScene.h"

namespace ai
{
	class TestScene : public BasicScene
	{
	public:
		TestScene();
		~TestScene();

		void Init() override;
		void Update() override;
		void Release() override;
	};
}

#endif
