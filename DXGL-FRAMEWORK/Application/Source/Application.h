
#ifndef APPLICATION_H
#define APPLICATION_H

#include "timer.h"

class Application
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
	Application();
	~Application();
	void Init();
	void Run();
	void Exit();
	static bool IsKeyPressed(unsigned short key);
	static bool IsMousePressed(unsigned short key);
	static void GetCursorPos(double* xpos, double* ypos);
	static bool getGameStart();
	static void setGameStart(bool Value);


	static int GetWindowWidth();
	static int GetWindowHeight();
private:
	SCENE_NUM sceneNum;
	bool enablePointer = false;
	bool showPointer = false;
	bool isEnterUp;
	//Declare a window object
	StopWatch m_timer;
};

#endif