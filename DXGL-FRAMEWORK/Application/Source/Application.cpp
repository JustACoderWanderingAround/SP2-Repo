
#include "Application.h"
#include "KeyboardController.h"

//Include GLEW
#include <GL/glew.h>

//Include GLFW
#include <GLFW/glfw3.h>

//Include the standard C++ headers
#include <stdio.h>
#include <stdlib.h>
#include "MouseController.h"	
#include "Scene.h"
#include "Scene1.h"
#include "SceneAssignment.h"
#include "ScenePinball.h"
#include "SceneCanTopple.h"
#include "SceneMain.h"
#include "SceneHitMen.h"
#include "SceneManager.h"

GLFWwindow* m_window;
const unsigned char FPS = 60; // FPS of this game
const unsigned int frameTime = 1000 / FPS; // time for each frame
int m_width, m_height;
bool gameStart;

//Define an error callback
static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
	_fgetchar();
}
//Define the mouse button callback
static void mousebtn_callback(GLFWwindow* window, int button, int action, int mods)
{
	// Send the callback to the mouse controller to handle
	if (action == GLFW_PRESS)
		MouseController::GetInstance()->UpdateMouseButtonPressed(button);
	else
		MouseController::GetInstance()->UpdateMouseButtonReleased(button);
}

//Define the mouse scroll callback
static void mousescroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	MouseController::GetInstance()->UpdateMouseScroll(xoffset, yoffset);
}


//Define the key input callback
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	KeyboardController::GetInstance()->Update(key, action);
}

void resize_callback(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, w, h); //update opengl the new window size
}

bool Application::IsKeyPressed(unsigned short key)
{
    return ((GetAsyncKeyState(key) & 0x8001) != 0);
}

Application::Application()
{
}

Application::~Application()
{
}

bool Application::IsMousePressed(unsigned short key) //0 - Left, 1 - Right, 2 - Middle
{
	return glfwGetMouseButton(m_window, key) != 0;
}
void Application::GetCursorPos(double* xpos, double* ypos)
{
	glfwGetCursorPos(m_window, xpos, ypos);
}

void Application::Init()
{

	//Set the error callback
	glfwSetErrorCallback(error_callback);

	//Initialize GLFW
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	//Set the GLFW window creation hints - these are optional
	glfwWindowHint(GLFW_SAMPLES, 4); //Request 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Request a specific OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Request a specific OpenGL version
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL

	//Create a window and create its OpenGL context
	m_width = 1000;
	m_height = 750;

	m_window = glfwCreateWindow(m_width, m_height, "Untitled Carnival Game", NULL, NULL);


	//If the window couldn't be created
	if (!m_window)
	{
		fprintf( stderr, "Failed to open GLFW window.\n" );
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//This function makes the context of the specified window current on the calling thread. 
	glfwMakeContextCurrent(m_window);



	//Sets the key callback
	glfwSetKeyCallback(m_window, key_callback);
	//Sets the mouse button callback
	glfwSetMouseButtonCallback(m_window, mousebtn_callback);

	//Sets the mouse scroll callback
	glfwSetScrollCallback(m_window, mousescroll_callback);
	

	if (enablePointer == false)
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	else
		if (showPointer == false)
			glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);


	//Sets the resize callback to handle window resizing
	glfwSetWindowSizeCallback(m_window, resize_callback);

	glewExperimental = true; // Needed for core profile
	//Initialize GLEW
	GLenum err = glewInit();

	//If GLEW hasn't initialized
	if (err != GLEW_OK) 
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		//return -1;
	}
	sceneNum = SCENE_NUM::SCENE_MAIN;

	gameStart = false;
}
void Application::Run()
{
	//Main Loop

	SceneManager::GetInstance()->InitScene();



	m_timer.startTimer();    // Start timer to calculate how long it takes to render this frame
	while (!glfwWindowShouldClose(m_window) && !IsKeyPressed(VK_ESCAPE))
	{
		//scene->Update(m_timer.getElapsedTime());
		//scene->Render();
		SceneManager::GetInstance()->RunScene(m_timer.getElapsedTime());
		//Swap buffers
		glfwSwapBuffers(m_window);
		

		KeyboardController::GetInstance()->PostUpdate();

		MouseController::GetInstance()->PostUpdate();


		double mouse_x, mouse_y;
		glfwGetCursorPos(m_window, &mouse_x, &mouse_y);
		MouseController::GetInstance()->UpdateMousePosition(mouse_x, mouse_y);

		//Get and organize events, like keyboard and mouse input, window resizing, etc...
		glfwPollEvents();
        m_timer.waitUntil(frameTime);       // Frame rate limiter. Limits each frame to a specified time in ms.   

	} //Check if the ESC key had been pressed or if the window had been closed
	SceneManager::GetInstance()->currScene->Exit();

}
int Application::GetWindowWidth()
{
	return m_width;
}
int Application::GetWindowHeight()
{
	return m_height;
}

bool Application::getGameStart()
{
	return gameStart;
}

void Application::setGameStart(bool Value)
{
	gameStart = Value;
}

void Application::Exit()
{
	KeyboardController::DestroyInstance();
	//Close OpenGL window and terminate GLFW
	glfwDestroyWindow(m_window);
	//Finalize and clean up GLFW
	glfwTerminate();
}

