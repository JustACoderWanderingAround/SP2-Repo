#pragma once
#include "Scene.h"
class SceneManager
{
	SceneManager();
	~SceneManager();
	static SceneManager* m_instance;
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
	static SceneManager* GetInstance();
	void InitScene();
	void LoadScene(SCENE_NUM sceneNum);
	void RunScene(double dt);
	void ExitScene();

};

