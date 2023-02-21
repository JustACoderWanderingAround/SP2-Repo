#include "SceneManager.h"
#include "SceneHitMen.h"
#include "SceneAssignment.h"
// todo: import all necessary .h files (main, canTopple, pinball)
#include <iostream>
SceneManager* SceneManager::m_instance = nullptr;

SceneManager::SceneManager()
{
	sceneNum = SCENE_NUM::SCENE_HITMEN;
	currScene = new SceneHitMen;
}

SceneManager::~SceneManager()
{
	if (m_instance) {
		delete m_instance;
		m_instance = nullptr;
	}
}

SceneManager* SceneManager::GetInstance()
{
	if (m_instance == nullptr) {
		m_instance = new SceneManager();
	}
	return m_instance;
}

void SceneManager::InitScene()
{
	currScene->Init();
}

void SceneManager::LoadScene(SCENE_NUM newSceneNum)
{
	Scene* temp;
	switch (newSceneNum) {
	case SCENE_NUM::SCENE_MAIN:
		/*temp = new SceneMain();
		ExitScene();
		currScene = temp;
		InitScene();*/
		break;
	case SCENE_NUM::SCENE_TEST:
		temp = new SceneAssignment();
		ExitScene();
		currScene = temp;
		InitScene();
		break;
	case SCENE_NUM::SCENE_HITMEN:
		temp = new SceneHitMen();
		ExitScene();
		currScene = temp;
		InitScene();
		break;
	case SCENE_NUM::SCENE_CANTOPPLE:
		/*temp = new SceneCanTopple();
		ExitScene();
		currScene = temp;
		InitScene();*/
		break;
	case SCENE_NUM::SCENE_PINBALL:
		/*temp = new ScenePinBall();
		ExitScene();
		currScene = temp;
		InitScene();*/
		break;
	default:
		std::cout << "Error!" << std::endl;
	}
	
}

void SceneManager::RunScene(double dt)
{
	currScene->Update(dt);
	if (currScene != nullptr)
		currScene->Render();
}

void SceneManager::ExitScene()
{
	currScene->Exit();
}
