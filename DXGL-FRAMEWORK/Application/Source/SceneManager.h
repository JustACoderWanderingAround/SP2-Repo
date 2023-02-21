#pragma once
#include "Scene.h"
class SceneManager
{
public:
	enum class SCENE_NUM {
		SCENE_TEST = 0,
		SCENE_MAIN,
		SCENE_HITMEN,
		SCENE_CANTOPPLE,
		SCENE_PINBALL,
		TOTAL_SCENE
	};
	SCENE_NUM sceneNum;
	Scene* currScene;
	SceneManager();
	~SceneManager();
	static SceneManager* GetInstance();
	void InitScene();
	void LoadScene();
	void RunScene(double dt);
	void ExitScene();

};

