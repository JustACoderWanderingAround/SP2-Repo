#include "SceneManager.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

SceneManager* SceneManager::GetInstance()
{
	return nullptr;
}

void SceneManager::InitScene()
{
}

void SceneManager::LoadScene()
{
}

void SceneManager::RunScene(double dt)
{
	currScene->Update(dt);
	currScene->Render();
}

void SceneManager::ExitScene()
{
}
