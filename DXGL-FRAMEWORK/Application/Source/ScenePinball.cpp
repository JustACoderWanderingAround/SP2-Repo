#include "ScenePinball.h"
#include "GL\glew.h"

// GLM Headers
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_inverse.hpp>
#include <glm\gtc\matrix_access.hpp>

//Include GLFW
#include <GLFW/glfw3.h>
#include <iostream>
#include "shader.hpp"
#include "Application.h"
#include "MeshBuilder.h"
#include "KeyboardController.h"
#include "LoadTGA.h"

ScenePinball::ScenePinball()
{
	srand(rand());
	srand(rand() % rand());
	srand(rand() % rand() % rand());
}

ScenePinball::~ScenePinball()
{
	/*for (std::vector<GameObject*>::iterator iter = interactables.begin(); iter != interactables.end(); iter++) {
		if (!(*iter == nullptr)) {
			delete* iter;
		}
	}*/
}

void ScenePinball::Init()
{
	srand(rand());
	srand(rand() % rand());
	srand(rand() % rand() % rand());
	srand(rand() % rand() % rand() % rand() % rand());
	
	// Set background color to dark blue
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	//Enable depth buffer and depth testing
	glEnable(GL_DEPTH_TEST);

	//Enable back face culling
	glEnable(GL_CULL_FACE);

	//Default to fill mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	// Load the shader programs
	m_programID = LoadShaders("Shader//Texture.vertexshader",
		"Shader//Text.fragmentshader");

	glUseProgram(m_programID);
		// m_parameters
		{
			// Get a handle for our "MVP" uniform
			m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
			m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
			m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
			m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
			m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
			m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
			m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");
			m_parameters[U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, "lights[0].type");
			m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
			m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
			m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
			m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
			m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
			m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");
			m_parameters[U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[0].spotDirection");
			m_parameters[U_LIGHT0_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[0].cosCutoff");
			m_parameters[U_LIGHT0_COSINNER] = glGetUniformLocation(m_programID, "lights[0].cosInner");
			m_parameters[U_LIGHT0_EXPONENT] = glGetUniformLocation(m_programID, "lights[0].exponent");

			m_parameters[U_LIGHT1_TYPE] = glGetUniformLocation(m_programID, "lights[1].type");
			m_parameters[U_LIGHT1_POSITION] = glGetUniformLocation(m_programID, "lights[1].position_cameraspace");
			m_parameters[U_LIGHT1_COLOR] = glGetUniformLocation(m_programID, "lights[1].color");
			m_parameters[U_LIGHT1_POWER] = glGetUniformLocation(m_programID, "lights[1].power");
			m_parameters[U_LIGHT1_KC] = glGetUniformLocation(m_programID, "lights[1].kC");
			m_parameters[U_LIGHT1_KL] = glGetUniformLocation(m_programID, "lights[1].kL");
			m_parameters[U_LIGHT1_KQ] = glGetUniformLocation(m_programID, "lights[1].kQ");
			m_parameters[U_LIGHT1_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[1].spotDirection");
			m_parameters[U_LIGHT1_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[1].cosCutoff");
			m_parameters[U_LIGHT1_COSINNER] = glGetUniformLocation(m_programID, "lights[1].cosInner");
			m_parameters[U_LIGHT1_EXPONENT] = glGetUniformLocation(m_programID, "lights[1].exponent");

			m_parameters[U_LIGHT2_TYPE] = glGetUniformLocation(m_programID, "lights[2].type");
			m_parameters[U_LIGHT2_POSITION] = glGetUniformLocation(m_programID, "lights[2].position_cameraspace");
			m_parameters[U_LIGHT2_COLOR] = glGetUniformLocation(m_programID, "lights[2].color");
			m_parameters[U_LIGHT2_POWER] = glGetUniformLocation(m_programID, "lights[2].power");
			m_parameters[U_LIGHT2_KC] = glGetUniformLocation(m_programID, "lights[2].kC");
			m_parameters[U_LIGHT2_KL] = glGetUniformLocation(m_programID, "lights[2].kL");
			m_parameters[U_LIGHT2_KQ] = glGetUniformLocation(m_programID, "lights[2].kQ");
			m_parameters[U_LIGHT2_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[2].spotDirection");
			m_parameters[U_LIGHT2_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[2].cosCutoff");
			m_parameters[U_LIGHT2_COSINNER] = glGetUniformLocation(m_programID, "lights[2].cosInner");
			m_parameters[U_LIGHT2_EXPONENT] = glGetUniformLocation(m_programID, "lights[2].exponent");

			m_parameters[U_LIGHT3_TYPE] = glGetUniformLocation(m_programID, "lights[3].type");
			m_parameters[U_LIGHT3_POSITION] = glGetUniformLocation(m_programID, "lights[3].position_cameraspace");
			m_parameters[U_LIGHT3_COLOR] = glGetUniformLocation(m_programID, "lights[3].color");
			m_parameters[U_LIGHT3_POWER] = glGetUniformLocation(m_programID, "lights[3].power");
			m_parameters[U_LIGHT3_KC] = glGetUniformLocation(m_programID, "lights[3].kC");
			m_parameters[U_LIGHT3_KL] = glGetUniformLocation(m_programID, "lights[3].kL");
			m_parameters[U_LIGHT3_KQ] = glGetUniformLocation(m_programID, "lights[3].kQ");
			m_parameters[U_LIGHT3_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[3].spotDirection");
			m_parameters[U_LIGHT3_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[3].cosCutoff");
			m_parameters[U_LIGHT3_COSINNER] = glGetUniformLocation(m_programID, "lights[3].cosInner");
			m_parameters[U_LIGHT3_EXPONENT] = glGetUniformLocation(m_programID, "lights[3].exponent");

			m_parameters[U_LIGHT4_TYPE] = glGetUniformLocation(m_programID, "lights[4].type");
			m_parameters[U_LIGHT4_POSITION] = glGetUniformLocation(m_programID, "lights[4].position_cameraspace");
			m_parameters[U_LIGHT4_COLOR] = glGetUniformLocation(m_programID, "lights[4].color");
			m_parameters[U_LIGHT4_POWER] = glGetUniformLocation(m_programID, "lights[4].power");
			m_parameters[U_LIGHT4_KC] = glGetUniformLocation(m_programID, "lights[4].kC");
			m_parameters[U_LIGHT4_KL] = glGetUniformLocation(m_programID, "lights[4].kL");
			m_parameters[U_LIGHT4_KQ] = glGetUniformLocation(m_programID, "lights[4].kQ");
			m_parameters[U_LIGHT4_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[4].spotDirection");
			m_parameters[U_LIGHT4_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[4].cosCutoff");
			m_parameters[U_LIGHT4_COSINNER] = glGetUniformLocation(m_programID, "lights[4].cosInner");
			m_parameters[U_LIGHT4_EXPONENT] = glGetUniformLocation(m_programID, "lights[4].exponent");

			m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
			m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");
			m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID,
				"colorTextureEnabled");
			m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");
			m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
			m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");
	
		}
		// Initialise camera properties
		mainFPSCam.Init(glm::vec3(3, 8, -2.4f), glm::vec3(3.02, 6.6f, -1.01f), glm::vec3(0.f, 1, 0.f));
		launcherCam.Init(glm::vec3(-0.5f, 6, -1.f), glm::vec3(-0.5, 4.8f, 0), glm::vec3(0.f, 1, 0.f), false);
		cameraArray.push_back(mainFPSCam);
		cameraArray.push_back(launcherCam);

		// Init VBO here
		for (int i = 0; i < NUM_GEOMETRY; ++i)
		{
			meshList[i] = nullptr;
		}


		// meshList
		{
			meshList[GEO_AXES] = MeshBuilder::GenerateAxes("Axes", 10000.f, 10000.f, 10000.f);
			meshList[GEO_SPHERE] = MeshBuilder::GenerateSphere("Sun", Color(1.f, 1.f, 1.f), 1.f, 16, 16);
			meshList[GEO_SILVER_SPHERE] = MeshBuilder::GenerateSphere("Player", Color(168 / 255, 169 / 255, 173 / 255), 1, 32, 32);
			//meshList[GEO_SILVER_SPHERE]->textureID = LoadTGA("Image//ball.tga");
			//meshList[GEO_SILVER_SPHERE] = MeshBuilder::GenerateOBJMTL("Player", "OBJ//Ball3.obj", "OBJ//Ball3.mtl");


			meshList[GEO_TENT] = MeshBuilder::GenerateOBJ("Tent", "OBJ//tent.obj");
			meshList[GEO_TENT]->textureID = LoadTGA("Image//tent.tga");

			//GUI
			meshList[GEO_UI] = MeshBuilder::GenerateQuad("UI", Color(1.f, 1.f, 1.f), 10);
			meshList[GEO_UI]->textureID = LoadTGA("Image//goldcoin.tga");
			meshList[GEO_LAUNCHER_UI] = MeshBuilder::GenerateQuad("Launcher", Color(1.f, 1.f, 1.f), 10);
			meshList[GEO_POWER_UI] = MeshBuilder::GenerateQuad("Power", Color(0.f, 1.f, 0.f), 10);
			meshList[GEO_TEXT] = MeshBuilder::GenerateText("comicsans",16 , 16);
			meshList[GEO_TEXT]->textureID = LoadTGA("Image//ComicSans.tga");
			meshList[GEO_GAMEOVER] = MeshBuilder::GenerateQuad("GameOver", Color(1.f, 1.f, 1.f), 10);
			meshList[GEO_GAMEOVER]->textureID = LoadTGA("Image//CarnivalUI.tga");

			//skybox
			meshList[GEO_TOP] = MeshBuilder::GenerateQuad("Top", Color(1.f, 1.f, 1.f), 1);
			meshList[GEO_TOP]->textureID = LoadTGA("Image//skyboxtop.tga");
			meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("Top", Color(1.f, 1.f, 1.f), 1);
			meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//skyboxbottom.tga");
			meshList[GEO_BACK] = MeshBuilder::GenerateQuad("Top", Color(1.f, 1.f, 1.f), 1);
			meshList[GEO_BACK]->textureID = LoadTGA("Image//skyboxback.tga");
			meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("Top", Color(1.f, 1.f, 1.f), 1);
			meshList[GEO_FRONT]->textureID = LoadTGA("Image//skyboxfront.tga");
			meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("Top", Color(1.f, 1.f, 1.f), 1);
			meshList[GEO_LEFT]->textureID = LoadTGA("Image//skyboxleft.tga");
			meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("Top", Color(1.f, 1.f, 1.f), 1);
			meshList[GEO_RIGHT]->textureID = LoadTGA("Image//skyboxright.tga");

			// for pinball 
			{
				meshList[GEO_CIRCLE] = MeshBuilder::GenerateCircle("CubeOrange", Color(255 / 255.f, 0, 0), 1.f, 12);
				meshList[GEO_SPHERE_BLACK] = MeshBuilder::GenerateSphere("SphereBlack", Color(0, 0, 0), 1.f, 36, 36);
				meshList[GEO_SPHERE_WHITE] = MeshBuilder::GenerateSphere("SphereWhite", Color(1, 1, 1), 1.f, 36, 36);
				meshList[GEO_TORUS] = MeshBuilder::GenerateTorus("TorusOrang", Color(121 / 255.f, 145 / 255.f, 80 / 255.f), 0.5f, 1.0f, 36, 36);
				meshList[GEO_GREY_CUBE] = MeshBuilder::GenerateCube("GreyCube", Color(68 / 255.f, 68 / 255.f, 68 / 255.f));
				meshList[GEO_MACHINELEG] = MeshBuilder::GenerateCylinder("Legs", Color(1.f, 1.f, 1.f), 5.f, 32.f, 1.f);
				meshList[GEO_MACHINELEG]->textureID = LoadTGA("Image//BodyPattern.tga");
				meshList[GEO_BASE] = MeshBuilder::GenerateCube("Body", Color(247 / 255.f, 181 / 255.f, 0), 1.f);
				//meshList[GEO_BASE]->textureID = LoadTGA("Image//Bluepattern.tga");
				meshList[GEO_SIDE] = MeshBuilder::GenerateCube("Body", Color(154 / 255.f, 61 / 255.f, 0), 1.f);
				meshList[GEO_SLOPE] = MeshBuilder::GenerateTri("obstacle", Color(125/255.f,249/255.f,1.f));
				meshList[GEO_TRIANGLE] = MeshBuilder::GenerateTri("Triangle", Color(154 / 255.f, 61 / 255.f, 0));

				// mat properties
				{

					meshList[GEO_SPHERE_BLACK]->material.kAmbient.Set(0.1f, 0.3f, 0.1f);
					meshList[GEO_SPHERE_BLACK]->material.kDiffuse.Set(0.2f, 0.4f, 0.2f);
					meshList[GEO_SPHERE_BLACK]->material.kSpecular.Set(0.3f, 0.5f, 0.3f);
					meshList[GEO_SPHERE_BLACK]->material.kShininess = 100.0f;
					meshList[GEO_SPHERE_WHITE]->material.kAmbient.Set(0.1f, 0.3f, 0.1f);
					meshList[GEO_SPHERE_WHITE]->material.kDiffuse.Set(0.2f, 0.4f, 0.2f);
					meshList[GEO_SPHERE_WHITE]->material.kSpecular.Set(0.3f, 0.5f, 0.3f);
					meshList[GEO_SPHERE_WHITE]->material.kShininess = 100.0f;
					meshList[GEO_SILVER_SPHERE]->material.kAmbient.Set(168 / 255, 171 / 255, 168 / 255);
					meshList[GEO_SILVER_SPHERE]->material.kDiffuse.Set(170 / 255, 176 / 255, 170 / 255);
					meshList[GEO_SILVER_SPHERE]->material.kSpecular.Set(171 / 255, 180 / 255, 171 / 255);
					meshList[GEO_SILVER_SPHERE]->material.kShininess = 68.f;
					meshList[GEO_BASE]->material.kAmbient.Set(247 / 255.f, 181 / 255.f, 0);
					meshList[GEO_BASE]->material.kDiffuse.Set(247 / 255.f, 181 / 255.f, 0);
					meshList[GEO_BASE]->material.kAmbient.Set(247 / 255.f, 181 / 255.f, 0);
					meshList[GEO_BASE]->material.kShininess = 100.f;
					meshList[GEO_SIDE]->material.kAmbient.Set(154 / 255.f, 61 / 255.f, 0);
					meshList[GEO_SIDE]->material.kDiffuse.Set(154 / 255.f, 61 / 255.f, 0);
					meshList[GEO_SIDE]->material.kAmbient.Set(154 / 255.f, 61 / 255.f, 0);
					meshList[GEO_SIDE]->material.kShininess = 100.f;
					meshList[GEO_SLOPE]->material.kAmbient.Set(125 / 255.f, 249 / 255.f, 1.f);
					meshList[GEO_SLOPE]->material.kDiffuse.Set(125 / 255.f, 249 / 255.f, 1.f);
					meshList[GEO_SLOPE]->material.kAmbient.Set(125 / 255.f, 249 / 255.f, 1.f);
					meshList[GEO_SLOPE]->material.kShininess = 75.f;
					meshList[GEO_MACHINELEG]->material.kAmbient.Set(1.f, 1.f, 1.f);
					meshList[GEO_MACHINELEG]->material.kDiffuse.Set(1.f, 1.f, 1.f);
					meshList[GEO_MACHINELEG]->material.kSpecular.Set(1.f, 1.f, 1.f);
					meshList[GEO_MACHINELEG]->material.kShininess = 100.f;
					meshList[GEO_TRIANGLE]->material.kAmbient.Set(154 / 255.f, 61 / 255.f, 0);
					meshList[GEO_TRIANGLE]->material.kDiffuse.Set(154 / 255.f, 61 / 255.f, 0);
					meshList[GEO_TRIANGLE]->material.kSpecular.Set(154 / 255.f, 61 / 255.f, 0);
					meshList[GEO_TRIANGLE]->material.kShininess = 100.f;
				}
			}
		};

		//ball
		{
		m_player = new GameObject(GameObject::GO_BALL);
		m_player->pos = glm::vec3(-0.6f, 2.42f, 0.f);
		//m_player->pos = glm::vec3(3.6f, 2.62f, 10.f);
		m_player->scale = glm::vec3(0.1f, 0.1f, 0.1f);
		m_player->vel = glm::vec3(0.f, 0.f, 0.f);
		m_player->active = true;
		m_player->mass = 1;
		m_player->dir = glm::vec3(0.f, 1.f, 0.f); 
		m_player->force = glm::vec3(0.f,0.f,-9.81f);
		score = 0;
		m_player->normal = glm::vec3(0, 0, 1);
		}

		//Flipper
		{
			//left
			m_flipper[0] = new GameObject(GameObject::GO_FLIPPER);
			m_flipper[0]->pos = glm::vec3(3.9f, 2.31f, 1.6f);
			m_flipper[0]->scale = glm::vec3(1.f, 0.4f, 0.1f);
			m_flipper[0]->vel = glm::vec3(0.f, 0.f, 0.f);
			m_flipper[0]->active = true;
			m_flipper[0]->mass = 1.f;
			m_flipper[0]->dir = glm::vec3(0.f, 1.f, 0.f);
			m_flipper[0]->normal = glm::vec3(0.f, 0.f, 1.f);
			rotation1 = -10;

			//right
			m_flipper[1] = new GameObject(GameObject::GO_FLIPPER);
			m_flipper[1]->pos = glm::vec3(2.4f, 2.31f, 1.6f);
			m_flipper[1]->scale = glm::vec3(1.f, 0.4f, 0.1f);
			m_flipper[1]->vel = glm::vec3(0.f, 0.f, 0.f);
			m_flipper[1]->active = true;
			m_flipper[1]->mass = 1.f;
			m_flipper[1]->dir = glm::vec3(0.f, 1.f, 0.f);
			m_flipper[1]->normal = glm::vec3(0.f, 0.f, 1.f);
			rotation2 = 10; }

		// Machine Parts
		{
			for (int i = 0; i < MAX_PARTS; i++)
			{
				PinballMachine[i] = new GameObject(GameObject::GO_WALL);
				PinballMachine[i]->active = true;
				PinballMachine[i]->mass = 1.f;
				PinballMachine[i]->vel = glm::vec3(0, 0, 0);
				PinballMachine[i]->dir = glm::vec3(0, 0, 0);
				PinballMachine[i]->torque = glm::vec3(0, 0, 0);
			}
			
			// 0 = base
			PinballMachine[0]->pos = glm::vec3(2.5f, 1.6f, 5.f);
			PinballMachine[0]->scale = glm::vec3(8.f, 1.f, 12.f);
			PinballMachine[0]->normal = glm::vec3(0, 1, 0);
			// 1 = front
			PinballMachine[1]->pos = glm::vec3(2.5f, 2.f, -1.5f);
			PinballMachine[1]->scale = glm::vec3(8.3f, 3.6f, 1.f);
			PinballMachine[1]->normal = glm::vec3(0, 0, 1);
			// 2 = left
			PinballMachine[2]->pos = glm::vec3(6.4f, 2.f, 4.5f);
			PinballMachine[2]->scale = glm::vec3(0.5f, 3.6f, 12.f);
			PinballMachine[2]->normal = glm::vec3(1, 0, 0);
			// 3 = right
			PinballMachine[3]->pos = glm::vec3(-1.4f, 2.f, 4.5f);
			PinballMachine[3]->scale = glm::vec3(0.5f, 3.6f, 12.f);
			PinballMachine[3]->normal = glm::vec3(-1, 0, 0);
			// 4 = back
			PinballMachine[4]->pos = glm::vec3(2.5f, 2.f, 11.f);
			PinballMachine[4]->scale = glm::vec3(8.3f, 3.6f, 1.f);
			PinballMachine[4]->normal = glm::vec3(0, 0, 1);
			// 5 = launcher wall
			PinballMachine[5]->pos = glm::vec3(-0.16f, 2.f, 3.f);
			PinballMachine[5]->scale = glm::vec3(0.4f, 1.f, 8.f);
			PinballMachine[5]->normal = glm::vec3(1, 0, 0);
			// 6 = catcher base
			PinballMachine[6]->pos = glm::vec3(3.f, 2.f, -0.6f);
			PinballMachine[6]->scale = glm::vec3(6.4f, 1.f, 1.6f);
			PinballMachine[6]->normal = glm::vec3(0, 0, 1);
			// 7 = catcher left slope
			PinballMachine[7]->pos = glm::vec3(5.1f, 2.29f, 0.2f);
			PinballMachine[7]->scale = glm::vec3(1.f, 0.5f, 2.5f);
			PinballMachine[7]->normal = glm::vec3(0, 0, 1);
			// 8 = catcher right slope
			PinballMachine[8]->pos = glm::vec3(1.f, 2.29f, 0.2f);
			PinballMachine[8]->scale = glm::vec3(1.f, 0.5f, 2.5f);
			PinballMachine[8]->normal = glm::vec3(0, 0, 1);
			// 9 = laucher slot blocker
			PinballMachine[9]->pos = glm::vec3(-0.6f, 1.5f, 7.35f);
			PinballMachine[9]->scale = glm::vec3(1.5f, 0.7f, 0.2f);
			PinballMachine[9]->normal = glm::vec3(1, 0, 1);
			// 10 = top left ball obstacle
			PinballMachine[10]->pos = glm::vec3(3.f, 2.3f, 9.f);
			PinballMachine[10]->scale = glm::vec3(0.3f, 0.3f, 0.3f);
			PinballMachine[10]->normal = glm::vec3(0, 0, 1);
			// 11 = top right ball obstacle
			PinballMachine[11]->pos = glm::vec3(1.f, 2.3f, 7.8f);
			PinballMachine[11]->scale = glm::vec3(0.3f, 0.3f, 0.3f);
			PinballMachine[11]->normal = glm::vec3(0, 0, 1);
			// 12 = bottom left ball obstacle
			PinballMachine[12]->pos = glm::vec3(4.f, 2.3f, 6.f);
			PinballMachine[12]->scale = glm::vec3(0.3f, 0.3f, 0.3f);
			PinballMachine[12]->normal = glm::vec3(0, 0, 1);
			// 13 = bottom right ball obstacle
			PinballMachine[13]->pos = glm::vec3(1.8f, 2.3f, 6.3f);
			PinballMachine[13]->scale = glm::vec3(0.3f, 0.3f, 0.3f);
			PinballMachine[13]->normal = glm::vec3(0, 0, 1);
			// 14 = right flipper wall part 3
			PinballMachine[14]->pos = glm::vec3(2.21f, 2.3f, 1.6f);
			PinballMachine[14]->scale = glm::vec3(0.4f, 0.4f, 0.2f);
			PinballMachine[14]->normal = glm::vec3(1, 0, 0);
			// 15 = left flipper wall part 1
			PinballMachine[15]->pos = glm::vec3(5.f, 2.3f, 2.2f);
			PinballMachine[15]->scale = glm::vec3(0.2f, 0.4f, 1.5f);
			PinballMachine[15]->normal = glm::vec3(1, 0, 0);
			// 16 = left flipper wall part 2
			PinballMachine[16]->pos = glm::vec3(4.5f, 2.3f, 1.6f);
			PinballMachine[16]->scale = glm::vec3(1.f, 0.4f, 0.4f);
			PinballMachine[16]->normal = glm::vec3(0, 0, 1);
			// 17 = right flipper wall part 1
			PinballMachine[17]->pos = glm::vec3(1.3f, 2.3f, 2.2f);
			PinballMachine[17]->scale = glm::vec3(0.2f, 0.4f, 1.5f);
			PinballMachine[17]->normal = glm::vec3(1, 0, 0);
			// 18 = right flipper wall part 2
			PinballMachine[18]->pos = glm::vec3(1.8f, 2.3f, 1.6f);
			PinballMachine[18]->scale = glm::vec3(1.f, 0.4f, 0.4f);
			PinballMachine[18]->normal = glm::vec3(0, 0, 1);
			// 19 = right corner
			PinballMachine[19]->pos = glm::vec3(-0.8f, 2.1f, 10.5f);
			PinballMachine[19]->scale = glm::vec3(1.5f, 1.5f, 1.f);
			PinballMachine[19]->normal = glm::vec3(0.7, 0, -1);
			yaw = glm::degrees(atan2(PinballMachine[19]->pos.x + PinballMachine[19]->scale.x, PinballMachine[19]->pos.z + PinballMachine[19]->scale.z));
			// 20 = left corner
			PinballMachine[20]->pos = glm::vec3(5.9f, 2.1f, 10.5f);
			PinballMachine[20]->scale = glm::vec3(1.5f, 1.5f, 1.f);
			PinballMachine[20]->normal = glm::vec3(-1, 0, -1);
			// 21 = left wall slope down
			PinballMachine[21]->pos = glm::vec3(6.09f, 2.4f, 4.08f);
			PinballMachine[21]->scale = glm::vec3(1.f, 0.5f, 0.4f);
			PinballMachine[21]->normal = glm::vec3(-1, 0, -1);
			// 22 = left wall slope up
			PinballMachine[22]->pos = glm::vec3(6.2f, 2.4f, 4.5f);
			PinballMachine[22]->scale = glm::vec3(1.f, 0.5f, 0.4f);
			PinballMachine[22]->normal = glm::vec3(-1, 0, 1);
			// 23 = right wall slope
			PinballMachine[23]->pos = glm::vec3(2.09f, 2.4f, 4.08f);
			PinballMachine[23]->scale = glm::vec3(1.f, 0.5f, 0.4f);
			PinballMachine[23]->normal = glm::vec3(1, 0, 1);
		}

		glm::mat4 projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 1000.0f);
		projectionStack.LoadMatrix(projection);

		glUniform1i(m_parameters[U_NUMLIGHTS], NUM_LIGHTS);
		// light params
		{
			// light that follows primary zakuCam
			light[0].position = glm::vec3(0, 25, -10);
			light[0].color.Set(1, 1, 1);
			light[0].type = Light::LIGHT_SPOT;
			light[0].power = 5.f;
			light[0].kC = 1.f;
			light[0].kL = 0.01f;
			light[0].kQ = 0.001f;
			light[0].cosCutoff = 5.f;
			light[0].cosInner = 1.f;
			light[0].exponent = 3.f;



			// main Hangar light 
			light[1].position = glm::vec3(0, 20, 0);
			light[1].type = Light::LIGHT_SPOT;
			//light[1].color.Set(1, 1, 1);
			light[1].color.Set(247 / 255.f, 181 / 255.f, 0);
			light[1].spotDirection = glm::normalize(light[1].position - glm::vec3(0, 0, 0));
			light[1].power = 7.5f;
			light[1].kC = 1.f;
			light[1].kL = 0.01f;
			light[1].kQ = 0.001f;
			light[1].cosCutoff = 45.f;
			light[1].cosInner = 30.f;
			light[1].exponent = 3.f;

			// room light 1
			light[2].position = glm::vec3(15, 10.f, 0);
			light[2].power = 3.f;
			light[2].type = Light::LIGHT_POINT;
			light[2].spotDirection = glm::vec3(0.f, -1.f, 0.f);
			light[2].cosCutoff = 65.f;
			light[2].cosInner = 10.f;
			light[2].exponent = 3.f;

			// room light 2
			light[3].position = glm::vec3(21, 10.f, 0);
			light[3].power = 3.f;
			light[3].type = Light::LIGHT_POINT;
			light[3].spotDirection = glm::vec3(0.f, -1.f, 0.f);
			light[3].cosCutoff = 65.f;
			light[3].cosInner = 10.f;
			light[3].exponent = 3.f;

			light[4].position = glm::vec3(5, 9.f, -1.5f);
			light[4].color.Set(251 / 255.f, 139 / 255.f, 35/255.f);
			light[4].power = 0.f;
			light[4].type = Light::LIGHT_DIRECTIONAL;
			light[4].spotDirection = glm::vec3(0.f, -1.f, 0.f);
			light[4].cosCutoff = 65.f;
			light[4].cosInner = 10.f;
			light[4].exponent = 3.f;
		}
		for (int i = 0; i < NUM_LIGHTS; i++) {
			glUniform3fv(m_parameters[U_LIGHT0_COLOR + (i * 11)], 1, &light[i].color.r);
			glUniform1i(m_parameters[U_LIGHT0_TYPE + (i * 11)], light[i].type);
			glUniform1f(m_parameters[U_LIGHT0_POWER + (i * 11)], light[i].power);
			glUniform1f(m_parameters[U_LIGHT0_KC + (i * 11)], light[i].kC);
			glUniform1f(m_parameters[U_LIGHT0_KL + (i * 11)], light[i].kL);
			glUniform1f(m_parameters[U_LIGHT0_KQ + (i * 11)], light[i].kQ);
			glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF + (i * 11)], cosf(glm::radians<float>(light[i].cosCutoff)));
			glUniform1f(m_parameters[U_LIGHT0_COSINNER + (i * 11)], cosf(glm::radians<float>(light[i].cosInner)));
			glUniform1f(m_parameters[U_LIGHT0_EXPONENT + (i * 11)], light[i].exponent);
		}
		
		cameraNum = 0;
		power = 0;
		BallLeft = 5;

		//test
		coins = 0;
}


void ScenePinball::Update(double dt)
{
	HandleKeyPress();

	//std::cout << "Pos: " << m_player->pos.x << ", " << m_player->pos.y << ", " << m_player->pos.z << std::endl;

	// spotlight for zaku cleaner view
	light[0].position = glm::vec3(cameraArray[1].position.x, cameraArray[1].position.y, cameraArray[1].position.z);
	light[0].spotDirection = glm::normalize(cameraArray[1].position - cameraArray[1].target);
	
	if (BallLeft >= 0 && m_player->active || BallLeft > 0 && !m_player->active) cameraArray[cameraNum].Update(dt);

	if (m_player->active)
	{
		m_player->pos.y = 2.42f;
		CollisionCheck();
		m_player->fixedUpdate(dt);
		ScoreAndCoin();
	}

	//std::cout << "X: " << light[0].position.x << " Y: " << light[0].position.y << " Z: " << light[0].position.z << std::endl;
	std::cout << "X: " << m_player->pos.x << " Y: " << m_player->pos.y << " Z: " << m_player->pos.z << std::endl;
	//std::cout << "X: " << cameraArray[0].position.x << " Y: " << cameraArray[0].position.y << " Z: " << cameraArray[0].position.z << std::endl;
	//std::cout << "X: " << cameraArray[0].target.x << " Y: " << cameraArray[0].target.y << " Z: " << cameraArray[0].target.z << std::endl;
}

void ScenePinball::Render()
{
	// Clear color buffer every frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Load view matrix stack and set it with camera position, target position and up direction
	viewStack.LoadIdentity(); {
		viewStack.LookAt(
			cameraArray[cameraNum].position.x, cameraArray[cameraNum].position.y, cameraArray[cameraNum].position.z,
			cameraArray[cameraNum].target.x, cameraArray[cameraNum].target.y, cameraArray[cameraNum].target.z,
			cameraArray[cameraNum].up.x, cameraArray[cameraNum].up.y, cameraArray[cameraNum].up.z
		);
		// Load identity matrix into the model stack
	} modelStack.LoadIdentity();

	for (int i = 0; i < NUM_LIGHTS; i++) {
		RenderLight(i);
	}
	for (int i = 0; i < NUM_LIGHTS; i++) {
		modelStack.PushMatrix(); {
			modelStack.Translate(light[i].position.x, light[i].position.y, light[i].position.z);
			modelStack.Scale(0.01f, 0.01f, 0.01f);
			RenderMesh(meshList[GEO_SPHERE], false);
		} modelStack.PopMatrix();
	}
	modelStack.PushMatrix(); {
		RenderMesh(meshList[GEO_AXES], false);
	} modelStack.PopMatrix();

	// render pinball Machine
	modelStack.PushMatrix(); {
		RenderPinballMachine();
	} modelStack.PopMatrix();

	RenderSkybox();
	
	//Render player
	if (m_player->active)
	{
		modelStack.PushMatrix();
		modelStack.Translate(m_player->pos.x, m_player->pos.y, m_player->pos.z);
		modelStack.Scale(m_player->scale.x, m_player->scale.y, m_player->scale.z);
		RenderMesh(meshList[GEO_SILVER_SPHERE], true);
		modelStack.PopMatrix();
	}

	modelStack.PushMatrix();
	modelStack.Translate(3.f, 0.f, 6.f);
	modelStack.Rotate(180, 0.f, 1.f, 0.f);
	modelStack.Scale(1.f, 1.f, 1.f);
	RenderMesh(meshList[GEO_TENT], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(4.5f, 6.5f, 10.3f);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(1.f, 1.f, 1.f);
	RenderText(meshList[GEO_TEXT], std::to_string(score), Color(1, 1, 1));
	modelStack.PopMatrix();

	//GUI
	if (BallLeft > 0 && m_player->active || BallLeft > 0 && !m_player->active)
	{
		RenderMeshOnScreen(meshList[GEO_UI], 100, 50, 20, 10);
		RenderTextOnScreen(meshList[GEO_TEXT], std::to_string(power), Color(50 / 255.f, 205 / 255.f, 50 / 255.f), 50, 600, 0);
		RenderTextOnScreen(meshList[GEO_TEXT], std::to_string(coins), Color(50 / 255.f, 205 / 255.f, 50 / 255.f), 100, 100, 0);
	}
	else if (BallLeft == 0 && !m_player->active)
	{
		RenderMeshOnScreen(meshList[GEO_GAMEOVER], 400, 300, 80, 60);
		RenderTextOnScreen(meshList[GEO_TEXT], "GAME OVER", Color(50 / 255.f, 205 / 255.f, 50 / 255.f), 50, 220, 350);
		RenderMeshOnScreen(meshList[GEO_UI], 300, 190, 20, 10);
		RenderTextOnScreen(meshList[GEO_TEXT], std::to_string(coins), Color(50 / 255.f, 205 / 255.f, 50 / 255.f), 100, 300, 140);
		//RenderTextOnScreen(meshList[GEO_TEXT], "Score: ", Color(50 / 255.f, 205 / 255.f, 50 / 255.f), 50, 200, 160);
		RenderTextOnScreen(meshList[GEO_TEXT], std::to_string(score), Color(50 / 255.f, 205 / 255.f, 50 / 255.f), 50, 300, 270);
	}
}

void ScenePinball::RenderMesh(Mesh* mesh, bool enableLight)
{
	glm::mat4 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, glm::value_ptr(MVP));
	modelView = viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, glm::value_ptr(modelView));
	if (enableLight)
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 1);
		modelView_inverse_transpose = glm::inverseTranspose(modelView);
		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, glm::value_ptr(modelView_inverse_transpose));

		//load material
		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
		glUniform1f(m_parameters[U_MATERIAL_SHININESS], mesh->material.kShininess);
	}
	else
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	}
	if (mesh->textureID > 0)
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
		glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	}
	else
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
	}

	mesh->Render();
	if (mesh->textureID > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void ScenePinball::RenderMeshOnScreen(Mesh* mesh, float x, float y, float sizex, float sizey)
{
	glDisable(GL_DEPTH_TEST);
	glm::mat4 ortho = glm::ortho(0.f, 800.f, 0.f, 600.f, -1000.f, 1000.f); // dimension of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity();

	//Use modelStack to position GUI on screen
	modelStack.Translate(x, y, 0.f);
	//modelStack.Rotate(180, 0.0f, 1.f, 0.f);
	//Use modelStack to scale the GUI
	modelStack.Scale(sizex, sizey, 1.f);


	RenderMesh(mesh, false); //UI should not have light
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);

}

void ScenePinball::RenderText(Mesh* mesh, std::string text, Color color)
{
	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;

	// Disable back face culling
	glDisable(GL_CULL_FACE);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		glm::mat4 characterSpacing = glm::translate(
			glm::mat4(1.f),
			glm::vec3(i * 1.0f, 0, 0));
		glm::mat4 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, glm::value_ptr(MVP));

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	glEnable(GL_CULL_FACE);

}

void ScenePinball::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
{
	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;

	glDisable(GL_DEPTH_TEST);
	glm::mat4 ortho = glm::ortho(0.f, 800.f, 0.f, 600.f, -100.f, 100.f); // dimension of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Translate(x, y, 0);
	modelStack.Scale(size, size, size);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	int lineCount = 0;
	for (unsigned i = 0; i < text.length(); ++i)
	{
		glm::mat4 characterSpacing = glm::translate(
			glm::mat4(1.f),
			glm::vec3(0.5f + i * 1.0f, 0.5f, 0)
		);
		glm::mat4 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, glm::value_ptr(MVP));

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();

	glEnable(GL_DEPTH_TEST);

}

void ScenePinball::RenderPinballMachine()
{
	modelStack.PushMatrix();
	{
		//modelStack.Translate(1.f, .f, 4.f);
		//modelStack.Scale(0.5f, 0.5f, 0.5f);
		//legs
		modelStack.PushMatrix();{
			modelStack.PushMatrix();
			modelStack.Translate(5.f, 0.f, 10.f);
			modelStack.Scale(0.5, 1.f, 0.5);
			RenderMesh(meshList[GEO_MACHINELEG], true);
			modelStack.PopMatrix();
			modelStack.PushMatrix();
			modelStack.Translate(0.f, 0.f, 10.f);
			modelStack.Scale(0.5, 1.f, 0.5);
			RenderMesh(meshList[GEO_MACHINELEG], true);
			modelStack.PopMatrix();
			modelStack.PushMatrix();
			modelStack.Translate(5.f, 0.f, 0.f);
			modelStack.Scale(0.5, 0.5, 0.5);
			RenderMesh(meshList[GEO_MACHINELEG], true);
			modelStack.PopMatrix();
			modelStack.PushMatrix();
			modelStack.Translate(0.f, 0.f, 0.f);
			modelStack.Scale(0.5, 0.5, 0.5);
			RenderMesh(meshList[GEO_MACHINELEG], true);
			modelStack.PopMatrix(); }
		modelStack.PopMatrix();
		//body
		modelStack.PushMatrix(); {
			//base
			modelStack.PushMatrix();
			modelStack.Translate(PinballMachine[0]->pos.x, PinballMachine[0]->pos.y, PinballMachine[0]->pos.z);
			modelStack.Scale(PinballMachine[0]->scale.x, PinballMachine[0]->scale.y, PinballMachine[0]->scale.z);
			RenderMesh(meshList[GEO_BASE], true);
			modelStack.PopMatrix();

			//Right Corner
			modelStack.PushMatrix();
			modelStack.Translate(PinballMachine[19]->pos.x, PinballMachine[19]->pos.y, PinballMachine[19]->pos.z);
			modelStack.Rotate(-30,0, 1, 0);
			modelStack.Scale(PinballMachine[19]->scale.x, PinballMachine[19]->scale.y, PinballMachine[19]->scale.z);
			RenderMesh(meshList[GEO_SIDE], true);
			modelStack.PopMatrix();

			//left Corner
			modelStack.PushMatrix();
			modelStack.Translate(PinballMachine[20]->pos.x, PinballMachine[20]->pos.y, PinballMachine[20]->pos.z);
			modelStack.Rotate(30, 0, 1, 0);
			modelStack.Scale(PinballMachine[20]->scale.x, PinballMachine[20]->scale.y, PinballMachine[20]->scale.z);
			RenderMesh(meshList[GEO_SIDE], true);
			modelStack.PopMatrix();
			
			//funnel
			modelStack.PushMatrix(); {
				//left slope
				modelStack.PushMatrix();
				modelStack.Translate(PinballMachine[7]->pos.x, PinballMachine[7]->pos.y, PinballMachine[7]->pos.z);
				modelStack.Rotate(-110.f, 0.f, 1.f, 0.f);
				//modelStack.Rotate(90.f, 0.f, 0.f, 1.f);
				modelStack.Scale(PinballMachine[7]->scale.x, PinballMachine[7]->scale.y, PinballMachine[7]->scale.z);
				RenderMesh(meshList[GEO_SIDE], true);
				modelStack.PopMatrix();
				//right slope
				modelStack.PushMatrix();
				modelStack.Translate(PinballMachine[8]->pos.x, PinballMachine[8]->pos.y, PinballMachine[8]->pos.z);
				modelStack.Rotate(110.f, 0.f, 1.f, 0.f);
				//modelStack.Rotate(-90.f, 0.f, 0.f, 1.f);
				modelStack.Scale(PinballMachine[8]->scale.x, PinballMachine[8]->scale.y, PinballMachine[8]->scale.z);
				RenderMesh(meshList[GEO_SIDE], true);
				modelStack.PopMatrix();

				modelStack.Translate(PinballMachine[6]->pos.x, PinballMachine[6]->pos.y, PinballMachine[6]->pos.z);
				modelStack.Scale(PinballMachine[6]->scale.x, PinballMachine[6]->scale.y, PinballMachine[6]->scale.z);
				RenderMesh(meshList[GEO_SIDE], true);
			}modelStack.PopMatrix();

			//left side
			modelStack.PushMatrix();
			modelStack.Translate(PinballMachine[2]->pos.x, PinballMachine[2]->pos.y, PinballMachine[2]->pos.z);
			modelStack.Scale(PinballMachine[2]->scale.x, PinballMachine[2]->scale.y, PinballMachine[2]->scale.z);
			RenderMesh(meshList[GEO_SIDE], true);
			modelStack.PopMatrix();
			//right side
			modelStack.PushMatrix();
			modelStack.Translate(PinballMachine[3]->pos.x, PinballMachine[3]->pos.y, PinballMachine[3]->pos.z);
			modelStack.Scale(PinballMachine[3]->scale.x, PinballMachine[3]->scale.y, PinballMachine[3]->scale.z);
			RenderMesh(meshList[GEO_SIDE], true);
			modelStack.PopMatrix();
			//Back side
			modelStack.PushMatrix();
				//Board
				modelStack.PushMatrix();
				//ball left display
				for (int i = 0; i < BallLeft; i++)
				{
					modelStack.PushMatrix();
					modelStack.Translate(-1.f,9.5f-i,10.5f);
					modelStack.Scale(0.3f,0.3f,0.3f);
					RenderMesh(meshList[GEO_SPHERE_WHITE], true);
					modelStack.PopMatrix();
				}
				modelStack.Translate(2.5f, 5.5f, 11.f);
				modelStack.Scale(8.3f, 10.f, 1.f);
				RenderMesh(meshList[GEO_SIDE], true);
				modelStack.PopMatrix();
			modelStack.Translate(PinballMachine[4]->pos.x, PinballMachine[4]->pos.y, PinballMachine[4]->pos.z);
			modelStack.Scale(PinballMachine[4]->scale.x, PinballMachine[4]->scale.y, PinballMachine[4]->scale.z);
			RenderMesh(meshList[GEO_SIDE], true);
			modelStack.PopMatrix();
			//Front Panel
			modelStack.PushMatrix();
				modelStack.PushMatrix();
					modelStack.PushMatrix();
					modelStack.Translate(-0.6f, 2.f, -2.7f);
					modelStack.Scale(-0.4f, 0.4f, 0.4f);
					RenderMesh(meshList[GEO_SPHERE], true);
					modelStack.PopMatrix();
				modelStack.Translate(-0.6f,2.f,-2.f);
				modelStack.Rotate(90, 1.f, 0.f, 0.f);
				modelStack.Scale(0.2f, 0.2f, 0.2f);
				RenderMesh(meshList[GEO_MACHINELEG], true);
				modelStack.PopMatrix();
			modelStack.Translate(PinballMachine[1]->pos.x, PinballMachine[1]->pos.y, PinballMachine[1]->pos.z);
			modelStack.Scale(PinballMachine[1]->scale.x, PinballMachine[1]->scale.y, PinballMachine[1]->scale.z);
			RenderMesh(meshList[GEO_SIDE], true);
			modelStack.PopMatrix();
		}
		modelStack.PopMatrix();
		//launcher area
		modelStack.PushMatrix(); {
			modelStack.PushMatrix();
				//ball launcher box
				/*
				{
				modelStack.PushMatrix();
				modelStack.Translate(-0.5f, 1.7f, -0.8f);
				modelStack.Scale(0.3f,0.7f,0.5f);
				RenderMesh(meshList[GEO_SIDE], true);
				modelStack.PopMatrix();
				modelStack.PushMatrix();
				modelStack.Translate(-1.1f, 1.7f, -0.8f);
				modelStack.Scale(0.3f, 0.7f, 0.5f);
				RenderMesh(meshList[GEO_SIDE], true);
				modelStack.PopMatrix();
				modelStack.PushMatrix();
				modelStack.Translate(-0.8f, 1.74f, -0.5f);

				modelStack.Scale(0.7f, 0.7f, 0.2f);
				RenderMesh(meshList[GEO_SIDE], true);
				modelStack.PopMatrix();
				}*/
			modelStack.Translate(PinballMachine[5]->pos.x, PinballMachine[5]->pos.y, PinballMachine[5]->pos.z);
			modelStack.Scale(PinballMachine[5]->scale.x, PinballMachine[5]->scale.y, PinballMachine[5]->scale.z);
			RenderMesh(meshList[GEO_SIDE], true);
			modelStack.PopMatrix();
			//Launcher blocker
			modelStack.PushMatrix();
			modelStack.Translate(PinballMachine[9]->pos.x,PinballMachine[9]->pos.y,PinballMachine[9]->pos.z);
			modelStack.Rotate(40, 0.f, 1.f, 0.f);
			modelStack.Scale(PinballMachine[9]->scale.x, PinballMachine[9]->scale.y, PinballMachine[9]->scale.z);
			RenderMesh(meshList[GEO_SIDE], true);
			modelStack.PopMatrix();
		}
		modelStack.PopMatrix();
		//obstacle
		modelStack.PushMatrix(); {
			//top left ball
			modelStack.PushMatrix();
			modelStack.Translate(PinballMachine[10]->pos.x, PinballMachine[10]->pos.y, PinballMachine[10]->pos.z);
			modelStack.Scale(PinballMachine[10]->scale.x, PinballMachine[10]->scale.y, PinballMachine[10]->scale.z);
			RenderMesh(meshList[GEO_SPHERE_BLACK], true);
			modelStack.PopMatrix();
			//top right ball
			modelStack.PushMatrix();
			modelStack.Translate(PinballMachine[11]->pos.x, PinballMachine[11]->pos.y, PinballMachine[11]->pos.z);
			modelStack.Scale(PinballMachine[11]->scale.x, PinballMachine[11]->scale.y, PinballMachine[11]->scale.z);
			RenderMesh(meshList[GEO_SPHERE_BLACK], true);
			modelStack.PopMatrix();
			//bottom left ball
			modelStack.PushMatrix();
			modelStack.Translate(PinballMachine[12]->pos.x, PinballMachine[12]->pos.y, PinballMachine[12]->pos.z);
			modelStack.Scale(PinballMachine[12]->scale.x, PinballMachine[12]->scale.y, PinballMachine[12]->scale.z);
			RenderMesh(meshList[GEO_SPHERE_BLACK], true);
			modelStack.PopMatrix();
			//bottom right ball
			modelStack.PushMatrix();
			modelStack.Translate(PinballMachine[13]->pos.x, PinballMachine[13]->pos.y, PinballMachine[13]->pos.z);
			modelStack.Scale(PinballMachine[13]->scale.x, PinballMachine[13]->scale.y, PinballMachine[13]->scale.z);
			RenderMesh(meshList[GEO_SPHERE_BLACK], true);
			modelStack.PopMatrix();

			//Left wall slope
			modelStack.PushMatrix();
			modelStack.Translate(PinballMachine[22]->pos.x, PinballMachine[22]->pos.y, PinballMachine[22]->pos.z);
			modelStack.Rotate(-30.f, 0.f, 1.f, 0.f);
			modelStack.Scale(PinballMachine[22]->scale.x, PinballMachine[22]->scale.y, PinballMachine[22]->scale.z);
			RenderMesh(meshList[GEO_SIDE], true);
			modelStack.PopMatrix();
			modelStack.PushMatrix();
			modelStack.Translate(PinballMachine[21]->pos.x, PinballMachine[21]->pos.y, PinballMachine[21]->pos.z);
			modelStack.Rotate(-120.f, 0.f, 1.f, 0.f);
			modelStack.Scale(PinballMachine[21]->scale.x, PinballMachine[21]->scale.y, PinballMachine[21]->scale.z);
			RenderMesh(meshList[GEO_SIDE], true);
			modelStack.PopMatrix();


			//right side triangle
			/*
			modelStack.PushMatrix();
			modelStack.Translate(2.6f, 2.4f, 3.5f);
			modelStack.Rotate(90.f, 0.f, 0.f, 1.f);
			modelStack.Scale(1.f, 1.8f, 1.8f);
			RenderMesh(meshList[GEO_SLOPE], true);
			modelStack.PopMatrix();*/
		
			//left side flipper area
			modelStack.PushMatrix();
				modelStack.PushMatrix();
				modelStack.Translate(PinballMachine[15]->pos.x, PinballMachine[15]->pos.y, PinballMachine[15]->pos.z);
				//modelStack.Rotate(-10.f, 0.f, 1.f, 0.f);
				modelStack.Scale(PinballMachine[15]->scale.x, PinballMachine[15]->scale.y, PinballMachine[15]->scale.z);
				RenderMesh(meshList[GEO_SIDE], true);
				modelStack.PopMatrix();
			modelStack.Translate(PinballMachine[16]->pos.x, PinballMachine[16]->pos.y, PinballMachine[16]->pos.z);
			//modelStack.Rotate(-10.f, 0.f, 1.f, 0.f);
			modelStack.Scale(PinballMachine[16]->scale.x, PinballMachine[16]->scale.y, PinballMachine[16]->scale.z);
			RenderMesh(meshList[GEO_SIDE], true);
			modelStack.PopMatrix();

			//right side flipper area
			modelStack.PushMatrix();
				modelStack.PushMatrix();
				modelStack.Translate(PinballMachine[17]->pos.x, PinballMachine[17]->pos.y, PinballMachine[17]->pos.z);
				//modelStack.Rotate(-10.f, 0.f, 1.f, 0.f);
				modelStack.Scale(PinballMachine[17]->scale.x, PinballMachine[17]->scale.y, PinballMachine[17]->scale.z);
				RenderMesh(meshList[GEO_SIDE], true);
				modelStack.PopMatrix();

				modelStack.PushMatrix();
				modelStack.Translate(PinballMachine[14]->pos.x, PinballMachine[14]->pos.y, PinballMachine[14]->pos.z);
				modelStack.Rotate(-90.f, 0.f, 1.f, 0.f);
				modelStack.Scale(PinballMachine[14]->scale.x, PinballMachine[14]->scale.y, PinballMachine[14]->scale.z);
				RenderMesh(meshList[GEO_SIDE], true);
				modelStack.PopMatrix();
			modelStack.Translate(PinballMachine[18]->pos.x, PinballMachine[18]->pos.y, PinballMachine[18]->pos.z);
			//modelStack.Rotate(10.f, 0.f, 1.f, 0.f);
			modelStack.Scale(PinballMachine[18]->scale.x, PinballMachine[18]->scale.y, PinballMachine[18]->scale.z);
			RenderMesh(meshList[GEO_SIDE], true);
			modelStack.PopMatrix();

			//flipper 1
			modelStack.PushMatrix();
			modelStack.Translate(m_flipper[0]->pos.x, m_flipper[0]->pos.y, m_flipper[0]->pos.z);
			modelStack.Rotate(rotation1, 0.f, 1.f, 0.f);
			modelStack.Scale(m_flipper[0]->scale.x, m_flipper[0]->scale.y, m_flipper[0]->scale.z);
			RenderMesh(meshList[GEO_SIDE], true);
			modelStack.PopMatrix();

			//flipper 2
			modelStack.PushMatrix();
			modelStack.Translate(m_flipper[1]->pos.x, m_flipper[1]->pos.y, m_flipper[1]->pos.z);
			modelStack.Rotate(rotation2, 0.f, 1.f, 0.f);
			modelStack.Scale(m_flipper[1]->scale.x, m_flipper[1]->scale.y, m_flipper[1]->scale.z);
			RenderMesh(meshList[GEO_SIDE], true);
			modelStack.PopMatrix();
		}
		modelStack.PopMatrix();
	}
	modelStack.PopMatrix();
}

void ScenePinball::RenderSkybox()
{
	modelStack.PushMatrix(); {
		modelStack.Translate(0.f, -49.f, 0.f);
		modelStack.Rotate(-90, 1.f, 0.f, 0.f);
		modelStack.Scale(100, 100, 0);
		RenderMesh(meshList[GEO_BOTTOM], false);
	}  modelStack.PopMatrix();
	modelStack.PushMatrix(); {
		modelStack.Translate(0.f, 49.f, 0.f);
		modelStack.Rotate(-90, 0.f, 0.f, 1.f);
		modelStack.Rotate(90, 0.f, 1.f, 0.f);
		modelStack.Scale(100, 100, 0);
		RenderMesh(meshList[GEO_TOP], false);
	} modelStack.PopMatrix();
	modelStack.PushMatrix(); {
		modelStack.Translate(0.f, 0.f, 49.f);
		modelStack.Rotate(-180, 1.f, 0.f, 0.f);
		modelStack.Scale(100, 100, 0);
		RenderMesh(meshList[GEO_LEFT], false);
	} modelStack.PopMatrix();
	modelStack.PushMatrix(); {
		modelStack.Translate(0.f, 0.f, -49.f);
		modelStack.Rotate(180, 0.f, 0.f, 1.f);
		modelStack.Scale(100, 100, 0);
		RenderMesh(meshList[GEO_RIGHT], false);
	} modelStack.PopMatrix();
	modelStack.PushMatrix(); {
		modelStack.Translate(-49.f, 0.f, 0.f);
		modelStack.Rotate(-90, 0.f, 1.f, 0.f);
		modelStack.Rotate(-180, 1.f, 0.f, 0.f);
		modelStack.Scale(100, 100, 0);
		RenderMesh(meshList[GEO_BACK], false);
	} modelStack.PopMatrix();
	modelStack.PushMatrix(); {
		modelStack.Translate(49.f, 0.f, 0.f);
		modelStack.Rotate(90, 0.f, 1.f, 0.f);
		modelStack.Rotate(180, 1.f, 0.f, 0.f);
		modelStack.Scale(100, 100, 0);
		RenderMesh(meshList[GEO_FRONT], false);
	} modelStack.PopMatrix();
}

void ScenePinball::RenderLight(int lightIndex)
{
	if (light[lightIndex].type == Light::LIGHT_DIRECTIONAL)
	{
		glm::vec3 lightDir(light[lightIndex].position.x, light[lightIndex].position.y, light[lightIndex].position.z);
		glm::vec3 lightDirection_cameraspace = viewStack.Top() * glm::vec4(lightDir, 0);
		glUniform3fv(m_parameters[U_LIGHT0_POSITION + (lightIndex * 11)], 1, glm::value_ptr(lightDirection_cameraspace));
	}
	else if (light[lightIndex].type == Light::LIGHT_SPOT)
	{
		glm::vec3 lightPosition_cameraspace = viewStack.Top() * glm::vec4(light[lightIndex].position, 1);
		glUniform3fv(m_parameters[U_LIGHT0_POSITION + (lightIndex * 11)], 1, glm::value_ptr(lightPosition_cameraspace));
		glm::vec3 spotDirection_cameraspace = viewStack.Top() * glm::vec4(light[lightIndex].spotDirection, 0);
		glUniform3fv(m_parameters[U_LIGHT0_SPOTDIRECTION + (lightIndex * 11)], 1, glm::value_ptr(spotDirection_cameraspace));
	}
	else {
		// Calculate the light position in camera space
		glm::vec3 lightPosition_cameraspace = viewStack.Top() * glm::vec4(light[lightIndex].position, 1);
		glUniform3fv(m_parameters[U_LIGHT0_POSITION + (lightIndex * 11)], 1, glm::value_ptr(lightPosition_cameraspace));
	}
}

void ScenePinball::BallMovement(double dt) {
	/*
	if (m_player->active) {
		//f=ma
		glm::vec3 acceleration = m_player->force * (1.f / (float)m_player->mass);
		m_player->vel += acceleration * (float)dt * 2;
		if (m_player->vel.LengthSquared() > MAX_SPEED * MAX_SPEED) //exercise 10
		{
			m_player->vel.Normalize() *= MAX_SPEED;
		}
		m_player->pos += m_player->vel * (float)dt * 2;

		//obtain u
		temp = m_player->vel;
		// V = u+at
		m_player->vel += (float)dt * 2 * gravity;
		// s = 0.5*(u+v)t
		m_player->pos += 0.5f * (float)dt * 2 * (m_player->vel + temp);
		//m_Disc[i]->pos += (float)dt * 2 * (m_Disc[i]->vel);

		//p = mass * velo

	}*/
}

void ScenePinball::ScoreAndCoin() {
	for (int i = 10; i < 14; i++)
	{
		if (PinballMachine[i]->CheckSSCollision(m_player))
		{
			score += 1000;
		}
	}

	if (BallLeft == 0)
	{
		float coin_convert;
		coin_convert = score / 3000;
		coins = static_cast<int>(coin_convert);
	}
}

void ScenePinball::CollisionCheck()
{
	if (PinballMachine[0]->CheckCSCollision(m_player))
	{
	}
	//machine and launcher wall
		for (int i = 1; i < 6; i++)
		{
			if (PinballMachine[i]->CheckCSCollision(m_player))
			{
				m_player->vel = m_player->vel - (2.0f * dot(m_player->vel, PinballMachine[i]->normal)) * PinballMachine[i]->normal;
				m_player->vel.x -= 0.5f;
				std::cout << "Collision wall Hit" << std::endl;
			}
		}

		//launcher
		if (PinballMachine[9]->CheckCSCollision(m_player))
		{
			m_player->vel = m_player->vel - (2.0f * dot(m_player->vel, PinballMachine[9]->normal)) * PinballMachine[9]->normal;
			//m_player->CollisionResponse(PinballMachine[4]);
			//m_player->WallCollisionResponse(PinballMachine[i]);
			//m_player->vel = glm::vec3(1, 0, 0);
			std::cout << "Collision launch blocker Hit" << std::endl;
		}

		//bottom funnel wall and slope
		for (int i = 6; i < 9; i++)
		{
			if (PinballMachine[i]->CheckCSCollision(m_player))
			{
				m_player->active = false;
				ballLaunch = false;
				std::cout << "hit the bottom" << std::endl;
			}
		}

		//corner
		for (int i = 19; i < 21; i++)
		{
			if (PinballMachine[i]->CheckCSCollision(m_player))
			{
				m_player->vel = m_player->vel.x - (2.0f * dot(m_player->vel, PinballMachine[i]->normal)) * PinballMachine[i]->normal;
				PinballMachine[9]->pos = glm::vec3(-0.6f, 2.15f, 7.37f);
				std::cout << "Collision slope Hit" << std::endl;
			}
		}
		
		//sphere obstacle
		for (int i = 10; i < 14; i++)
		{
			if (PinballMachine[i]->CheckSSCollision(m_player))
			{
				m_player->vel = m_player->vel - (2.0f * dot(m_player->vel, PinballMachine[i]->normal)) * PinballMachine[i]->normal;
				std::cout << "Collision Sphere Hit" << std::endl;
			}
		}

		//funnel
		for (int i = 15; i < 19; i++)
		{
			if (PinballMachine[i]-> CheckCSCollision(m_player))
			{
				m_player->vel = m_player->vel - (2.0f * dot(m_player->vel, PinballMachine[i]->normal)) * PinballMachine[i]->normal;
				std::cout << "Collision funnel Hit" << std::endl;
			}
		}

		//Flipper
		for (int i = 0; i < 2; i++)
		{
			if (m_flipper[i]->CheckCSCollision(m_player))
			{
				m_player->vel = m_player->vel - (2.0f * dot(m_player->vel, m_flipper[i]->normal)) * m_flipper[i]->normal;
				std::cout << "Collision flipper Hit" << std::endl;
			}
		}

		//wall slope
		for (int i = 21; i < 23; i++)
		{
			if (PinballMachine[i]->CheckCSCollision(m_player))
			{
				m_player->vel = m_player->vel.x - (2.0f * dot(m_player->vel, PinballMachine[i]->normal)) * PinballMachine[i]->normal;
				std::cout << "Collision wall slope Hit" << std::endl;
			}
		}
}

void ScenePinball::Exit()
{
	// Cleanup VBO here
	for (int i = 0; i < NUM_GEOMETRY; ++i)
	{
		std::cout << i << std::endl;
		if (meshList[i])
		{
			delete meshList[i];
		}
	}
	for (int i = 0; i < interactables.size(); ++i)
	{
		if (interactables[i])
		{
			delete interactables[i];
		}
	}
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}

void ScenePinball::HandleKeyPress()
{
	if (KeyboardController::GetInstance()->IsKeyPressed(0x31))
	{
		// Key press to enable culling
		glEnable(GL_CULL_FACE);
	}
	if (KeyboardController::GetInstance()->IsKeyPressed(0x32))
	{
		// Key press to disable culling
		glDisable(GL_CULL_FACE);
	}
	if (KeyboardController::GetInstance()->IsKeyPressed(0x33))
	{
		// Key press to enable fill mode for the polygon
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
	}
	if (KeyboardController::GetInstance()->IsKeyPressed(0x34))
	{
		// Key press to enable wireframe mode for the polygon
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode
	}

	if (BallLeft >= 0 && m_player->active || BallLeft > 0 && !m_player->active)
	{
		// cam change
		if (KeyboardController::GetInstance()->IsKeyPressed(GLFW_KEY_TAB)) {
			if (cameraNum == 0) {//fps
				cameraNum = 1;
			}
			else if (cameraNum == 1)//launcher
				cameraNum = 0;
			else
				cameraNum = 0;
		}

		if (KeyboardController::GetInstance()->IsKeyPressed(GLFW_KEY_F1))
		{
			posAdd += 1.2;
		}
		else if (KeyboardController::GetInstance()->IsKeyPressed(GLFW_KEY_F2))
		{
			posAdd -= 0.2;
		}

		// Power Control
		if (Application::IsKeyPressed(GLFW_KEY_K))
		{
			if (power < 25)
			{
				power += 0.5;
			}
		}
		else if (Application::IsKeyPressed(GLFW_KEY_L))
		{
			if (power > 5)
			{
				power -= 0.5;
			}
		}
		//to fire
		if (!bRKeyStateSpace && !ballLaunch && Application::IsKeyPressed(GLFW_KEY_SPACE))
		{
			bRKeyStateSpace = true;
			if (!m_player->active && BallLeft > 0)
			{
				m_player->pos = glm::vec3(-0.6f, 2.42f, 0.f);
				m_player->vel = glm::vec3(0, 0, 0);
				PinballMachine[9]->pos = glm::vec3(-0.6f, 1.5f, 7.35f);
				m_player->active = true;
			}
		}
		else if (bRKeyStateSpace && !Application::IsKeyPressed(GLFW_KEY_SPACE))
		{
			bRKeyStateSpace = false;
			ballLaunch = true;
			m_player->vel = glm::vec3(0.f, 0.f, power);
			std::cout << m_player->vel.x << std::endl;
			BallLeft--;
			//PinballMachine[9]->pos = glm::vec3(-0.6f, 2.15f, 7.35f);
			if (power != 0)
			{
				power = 0;
			}
		}

		// Flipper control left
		if (!bRKeyStateZ && Application::IsKeyPressed(GLFW_KEY_Z))
		{
			bRKeyStateZ = true;
			rotation1 = 15;
		}
		else if (bRKeyStateZ && !Application::IsKeyPressed(GLFW_KEY_Z))
		{
			bRKeyStateZ = false;
			rotation1 = -10;
		}

		// Flipper control right
		if (!bRKeyStateX && Application::IsKeyPressed(GLFW_KEY_X))
		{
			bRKeyStateX = true;
			rotation2 = -15;
		}
		else if (bRKeyStateX && !Application::IsKeyPressed(GLFW_KEY_X))
		{
			bRKeyStateX = false;
			rotation2 = 10;
		}

		//Test score
		if (!bRKeyState && Application::IsKeyPressed(GLFW_KEY_O))
		{
			bRKeyState = true;
			score += 1000;
		}
		else if (bRKeyState && !Application::IsKeyPressed(GLFW_KEY_O))
		{
			bRKeyState = false;
		}
	}
	if (!bRKeyStateR && Application::IsKeyPressed(GLFW_KEY_R))
	{
		bRKeyStateR = true;
	}
	else if (bRKeyStateR && !Application::IsKeyPressed(GLFW_KEY_R))
	{
		bRKeyStateR = false;
		m_player->pos = glm::vec3(-0.6f, 2.42f, 0.f);
		m_player->vel = glm::vec3(0, 0, 0);
		PinballMachine[9]->pos = glm::vec3(-0.6f, 1.5f, 7.35f);
		m_player->active = true;
		score = 0;
		BallLeft = 5;
	}
}
