#include "SceneAssignment.h"
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

SceneAssignment::SceneAssignment()
{
	srand(rand());
	srand(rand() % rand());
	srand(rand() % rand() % rand());
}

SceneAssignment::~SceneAssignment()
{
	/*for (std::vector<GameObject*>::iterator iter = interactables.begin(); iter != interactables.end(); iter++) {
		if (!(*iter == nullptr)) {
			delete* iter;
		}
	}*/
}

void SceneAssignment::Init()
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
		roomY = 8.f;
		initCamY = roomY + 1.3;
		// Initialise camera properties
		mainFPSCam.Init(glm::vec3(21, initCamY, 0.f), glm::vec3(0, initCamY, 0), glm::vec3(0.f, initCamY, 0.f));
		zakuCam.Init(glm::vec3(0, initCamY + 2, 15.f), glm::vec3(0, initCamY + 2, 0), glm::vec3(0.f, 1, 0.f), false);
		cameraArray.push_back(mainFPSCam);
		cameraArray.push_back(zakuCam);

		for (int i = 0; i < NUM_DIRTBALLS; i++) {
			GameObject* temp = new GameObject();
			temp->pos = glm::vec3(5 - rand() % 10, rand() % 10, 5.f - rand() % 10);
			int scale = 1 + rand() % 3;
			temp->scale = glm::vec3(scale, scale, scale);
			dirtBalls.push_back(temp);
		}
		// Init VBO here
		for (int i = 0; i < NUM_GEOMETRY; ++i)
		{
			meshList[i] = nullptr;
		}


		// meshList
		{
			meshList[GEO_AXES] = MeshBuilder::GenerateAxes("Axes", 10000.f, 10000.f, 10000.f);
			meshList[GEO_SPHERE] = MeshBuilder::GenerateSphere("Sun", Color(1.f, 1.f, 1.f), 1.f, 16, 16);
			meshList[GEO_CUBE] = MeshBuilder::GenerateCube("Arm", Color(247 / 255.f, 181 / 255.f, 0), 1.f);

			// skybox
			meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("Plane", Color(1.f, 1.f, 1.f), 100.f);
			meshList[GEO_LEFT]->textureID = LoadTGA("Image//Sky_NightTime01LF.tga");
			meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("Plane", Color(1.f, 1.f, 1.f), 100.f);
			meshList[GEO_RIGHT]->textureID = LoadTGA("Image//Sky_NightTime01RT.tga");
			meshList[GEO_TOP] = MeshBuilder::GenerateQuad("Plane", Color(1.f, 1.f, 1.f), 100.f);
			meshList[GEO_TOP]->textureID = LoadTGA("Image//Sky_NightTime01UP.tga");
			meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("Plane", Color(1.f, 1.f, 1.f), 100.f);
			meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//Sky_NightTime01DN.tga");
			meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("Plane", Color(1.f, 1.f, 1.f), 100.f);
			meshList[GEO_FRONT]->textureID = LoadTGA("Image//Sky_NightTime01FT.tga");
			meshList[GEO_BACK] = MeshBuilder::GenerateQuad("Plane", Color(1.f, 1.f, 1.f), 100.f);
			meshList[GEO_BACK]->textureID = LoadTGA("Image//Sky_NightTime01BK.tga");

			meshList[GEO_GREY_FLOOR] = MeshBuilder::GenerateQuad("floor.", Color(20 / 255.f, 21 / 255.f, 23 / 255.f));
			meshList[GEO_GREY_FLOOR]->textureID = LoadTGA("Image//floortexture.tga");


			meshList[GEO_PLAYER] = MeshBuilder::GenerateOBJMTL("player", "OBJ//mobil.obj", "OBJ//mobil.mtl");
			meshList[GEO_PLAYER]->textureID = LoadTGA("Image//mobil.tga");
			meshList[GEO_CROSSHAIR] = MeshBuilder::GenerateQuad("crosshair UI", Color(1,1,1));
			meshList[GEO_CROSSHAIR]->textureID = LoadTGA("Image//crosshair.TGA");

			meshList[GEO_DIRTBALL] = MeshBuilder::GenerateSphere("dirt", Color(123 / 255.f, 88 / 255.f, 4 / 255.f));




			// for zaku 
			{
				meshList[GEO_CIRCLE] = MeshBuilder::GenerateCircle("CubeOrange", Color(255 / 255.f, 0, 0), 1.f, 12);
				meshList[GEO_SPHERE_BLACK] = MeshBuilder::GenerateSphere("SphereOrange", Color(0, 0, 0), 1.f, 36, 36);
				meshList[GEO_TORUS] = MeshBuilder::GenerateTorus("TorusOrang", Color(121 / 255.f, 145 / 255.f, 80 / 255.f), 0.5f, 1.0f, 36, 36);
				meshList[GEO_ZAKU_HEAD] = MeshBuilder::GenerateDome("Head", Color(121 / 255.f, 145 / 255.f, 80 / 255.f), 1.f, 16, 16);
				meshList[GEO_ZAKU_CUBE] = MeshBuilder::GenerateCube("ZakuCube", Color(52 / 255.f, 68 / 255.f, 25 / 255.f));
				meshList[GEO_ZAKU_CUBE_ALT] = MeshBuilder::GenerateCube("ZakuCube", Color(121 / 255.f, 145 / 255.f, 80 / 255.f));
				meshList[GEO_GREY_CUBE] = MeshBuilder::GenerateCube("GreyCube", Color(68 / 255.f, 68 / 255.f, 68 / 255.f));
				meshList[GEO_ZAKU_CYLINDER] = MeshBuilder::GenerateCylinder("ZakuCyl", Color(52 / 255.f, 68 / 255.f, 25 / 255.f), 1, 36);
				meshList[GEO_ZAKU_CYLINDER_ALT] = MeshBuilder::GenerateCylinder("ZakuCyl", Color(121 / 255.f, 145 / 255.f, 80 / 255.f), 1, 36);
				meshList[GEO_GREY_CYLINDER] = MeshBuilder::GenerateCylinder("ZakuCyl", Color(0.5f, 0.5f, 0.5f), 1, 36);
				meshList[GEO_AXE_CUBE] = MeshBuilder::GenerateCube("ZakuCube", Color(102 / 255.f, 51 / 255.f, 0 / 255.f));
				// zaku mat properties
				{

					meshList[GEO_CIRCLE]->material.kAmbient.Set(225 / 255.f, 0, 0);
					meshList[GEO_CIRCLE]->material.kDiffuse.Set(245 / 255.f, 0, 0);
					meshList[GEO_CIRCLE]->material.kSpecular.Set(255 / 255.f, 0, 0);
					meshList[GEO_CIRCLE]->material.kShininess = 5.0f;
					meshList[GEO_SPHERE_BLACK]->material.kAmbient.Set(0.1f, 0.3f, 0.1f);
					meshList[GEO_SPHERE_BLACK]->material.kDiffuse.Set(0.2f, 0.4f, 0.2f);
					meshList[GEO_SPHERE_BLACK]->material.kSpecular.Set(0.3f, 0.5f, 0.3f);
					meshList[GEO_SPHERE_BLACK]->material.kShininess = 100.0f;
					meshList[GEO_GREY_CUBE]->material.kAmbient.Set(88 / 255.f, 88 / 255.f, 88 / 255.f);
					meshList[GEO_GREY_CUBE]->material.kDiffuse.Set(98 / 255.f, 98 / 255.f, 98 / 255.f);
					meshList[GEO_GREY_CUBE]->material.kSpecular.Set(108 / 255.f, 108 / 255.f, 108 / 255.f);
					meshList[GEO_GREY_CUBE]->material.kShininess = 40.0f;
					meshList[GEO_ZAKU_CUBE]->material.kAmbient.Set(22 / 255.f, 38 / 255.f, 5 / 255.f);
					meshList[GEO_ZAKU_CUBE]->material.kDiffuse.Set(52 / 255.f, 68 / 255.f, 25 / 255.f);
					meshList[GEO_ZAKU_CUBE]->material.kSpecular.Set(62 / 255.f, 78 / 255.f, 35 / 255.f);
					meshList[GEO_ZAKU_CUBE]->material.kShininess = 40.0f;
					meshList[GEO_ZAKU_CUBE_ALT]->material.kAmbient.Set(111 / 255.f, 135 / 255.f, 70 / 255.f);
					meshList[GEO_ZAKU_CUBE_ALT]->material.kDiffuse.Set(121 / 255.f, 145 / 255.f, 80 / 255.f);
					meshList[GEO_ZAKU_CUBE_ALT]->material.kSpecular.Set(131 / 255.f, 155 / 255.f, 90 / 255.f);
					meshList[GEO_ZAKU_CUBE_ALT]->material.kShininess = 40.0f;
					meshList[GEO_ZAKU_HEAD]->material.kAmbient.Set(111 / 255.f, 135 / 255.f, 70 / 255.f);
					meshList[GEO_ZAKU_HEAD]->material.kDiffuse.Set(121 / 255.f, 145 / 255.f, 80 / 255.f);
					meshList[GEO_ZAKU_HEAD]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
					meshList[GEO_ZAKU_HEAD]->material.kShininess = 40.0f;
					meshList[GEO_ZAKU_CYLINDER]->material.kAmbient.Set(22 / 255.f, 38 / 255.f, 5 / 255.f);
					meshList[GEO_ZAKU_CYLINDER]->material.kDiffuse.Set(52 / 255.f, 68 / 255.f, 25 / 255.f);
					meshList[GEO_ZAKU_CYLINDER]->material.kSpecular.Set(62 / 255.f, 78 / 255.f, 35 / 255.f);
					meshList[GEO_ZAKU_CYLINDER]->material.kShininess = 40.0f;
					meshList[GEO_ZAKU_CYLINDER_ALT]->material.kAmbient.Set(111 / 255.f, 135 / 255.f, 70 / 255.f);
					meshList[GEO_ZAKU_CYLINDER_ALT]->material.kDiffuse.Set(121 / 255.f, 145 / 255.f, 80 / 255.f);
					meshList[GEO_ZAKU_CYLINDER_ALT]->material.kSpecular.Set(131 / 255.f, 155 / 255.f, 90 / 255.f);
					meshList[GEO_ZAKU_CYLINDER_ALT]->material.kShininess = 10.0f;
					meshList[GEO_TORUS]->material.kAmbient.Set(111 / 255.f, 135 / 255.f, 70 / 255.f);
					meshList[GEO_TORUS]->material.kDiffuse.Set(121 / 255.f, 145 / 255.f, 80 / 255.f);
					meshList[GEO_TORUS]->material.kSpecular.Set(131 / 255.f, 155 / 255.f, 90 / 255.f);
					meshList[GEO_TORUS]->material.kShininess = 200.0f;
					meshList[GEO_GREY_CYLINDER]->material.kAmbient.Set(0.4f, 0.4f, 0.4f);
					meshList[GEO_GREY_CYLINDER]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
					meshList[GEO_GREY_CYLINDER]->material.kSpecular.Set(0.6f, 0.6f, 0.6f);
					meshList[GEO_GREY_CYLINDER]->material.kShininess = 200.0f;
					meshList[GEO_AXE_CUBE]->material.kAmbient.Set(92 / 255.f, 41 / 255.f, 0 / 255.f);
					meshList[GEO_AXE_CUBE]->material.kDiffuse.Set(102 / 255.f, 51 / 255.f, 0 / 255.f);
					meshList[GEO_AXE_CUBE]->material.kSpecular.Set(112 / 255.f, 61 / 255.f, 10 / 255.f);
					meshList[GEO_AXE_CUBE]->material.kShininess = 200.0f;
				}
			}
			// control room
			{
				meshList[GEO_GENERAL_FLOOR_1] = MeshBuilder::GenerateQuad("GeneralFloor", Color(1, 1, 1), 1.f, true);
				meshList[GEO_GENERAL_WALL_1] = MeshBuilder::GenerateQuad("GeneralWall", Color(1, 1, 1), 1.f, true);
				meshList[GEO_GENERAL_WALL_1]->textureID = LoadTGA("Image//GeneralWall.tga");
				meshList[GEO_GENERAL_FLOOR_1]->textureID = LoadTGA("Image//GeneralFloor.tga");

				meshList[GEO_GENERAL_FLOOR_2] = MeshBuilder::GenerateQuad("GeneralFloor", Color(1, 1, 1), 2.f, true);
				meshList[GEO_GENERAL_WALL_2] = MeshBuilder::GenerateQuad("GeneralWall", Color(1, 1, 1), 2.f, true);
				meshList[GEO_GENERAL_WALL_2]->textureID = LoadTGA("Image//GeneralWall.tga");
				meshList[GEO_GENERAL_FLOOR_2]->textureID = LoadTGA("Image//GeneralFloor.tga");

				meshList[GEO_GENERAL_FLOOR_5] = MeshBuilder::GenerateQuad("GeneralFloor", Color(1, 1, 1), 5.f, true);
				meshList[GEO_GENERAL_FLOOR_5]->textureID = LoadTGA("Image//GeneralFloor.tga");

				meshList[GEO_SECONDARY_WALL_1] = MeshBuilder::GenerateQuad("SecondaryWall", Color(1, 1, 1), 1.f, true);
				meshList[GEO_SECONDARY_WALL_1]->textureID = LoadTGA("Image//oldWall.tga");

				meshList[GEO_TOUCHSCREEN1] = MeshBuilder::GenerateOBJMTL("kiosk", "OBJ//kiosk.obj", "OBJ//kiosk.mtl");
				meshList[GEO_TOUCHSCREEN1]->textureID = LoadTGA("Image//kiosk.tga");



				meshList[GEO_TOUCHSCREEN2] = MeshBuilder::GenerateOBJMTL("kiosk", "OBJ//kiosk.obj", "OBJ//kiosk.mtl");
				meshList[GEO_TOUCHSCREEN2]->textureID = LoadTGA("Image//kiosk2.tga");
			}

			// multi use no texture
			{
				meshList[GEO_CLEANER] = MeshBuilder::GenerateOBJMTL("cleaner UFO", "OBJ//ufo.obj", "OBJ//ufo.mtl");
				meshList[GEO_CLEANER]->textureID = LoadTGA("Image//ufo.tga");
				meshList[GEO_UI] = MeshBuilder::GenerateQuad("UIBackground", Color(1, 1, 1), 100.f, false);
				meshList[GEO_UI]->textureID = LoadTGA("Image//TextBG.tga");
				meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
				meshList[GEO_TEXT]->textureID = LoadTGA("Image//ComicSans.tga");
			}
			meshList[GEO_ARROW] = MeshBuilder::GenerateOBJMTL("arrow!", "OBJ//Arrow.obj", "OBJ//Arrow.mtl");
			meshList[GEO_ARROW]->textureID = LoadTGA("Image//Arrow.tga");
			// other mat properties
			{
				meshList[GEO_GREY_FLOOR]->material.kAmbient.Set(0.4, 0.4, 0.4);
				meshList[GEO_GREY_FLOOR]->material.kDiffuse.Set(0.3, 0.3, 0.3);
				meshList[GEO_GREY_FLOOR]->material.kSpecular.Set(0.2, 0.2, 0.2);
				meshList[GEO_GREY_FLOOR]->material.kShininess = 100.f;
				meshList[GEO_DIRTBALL]->material.kAmbient.Set(0.4, 0.4, 0.4);
				meshList[GEO_DIRTBALL]->material.kDiffuse.Set(0.3, 0.3, 0.3);
				meshList[GEO_DIRTBALL]->material.kSpecular.Set(0.2, 0.2, 0.2);
				meshList[GEO_DIRTBALL]->material.kShininess = 100.f;

			}
		};

		glm::mat4 projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 1000.0f);
		projectionStack.LoadMatrix(projection);

		zakuPos = glm::vec3(0, 10.f, 0);

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

			light[4].position = glm::vec3(0, 9.f, -1.5f);
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
		
		door1pos = glm::vec3(19.f, 9.f, 1.25f);
		door2pos = glm::vec3(19.f, 9.f, -1.25f);
		m_player.pos = glm::vec3(21, 8.5f, 0.f);
		m_player.scale = glm::vec3(1, 1, 1);
		zakuCleaner.scale = glm::vec3(1, 1, 1);
		zakuCleanerPos = glm::vec3(0, 0, 0);
		interactables.emplace_back(new GameObject(glm::vec3(13, 8.5f, 0.f), std::vector<std::string>{"Press tab to press button", "Press space when near dirt to clean", "All balls cleaned! Press tab to exit"}, glm::vec3(0.5f, 1.0f, 0.75f)));
		interactables.emplace_back(new GameObject(glm::vec3(19, 8.5f, 0.f), std::vector<std::string>{"Press tab to open door"}, glm::vec3(1, 1, 1)));
		interactables.emplace_back(new GameObject(glm::vec3(13, 8.5f, -2.f), std::vector<std::string>{"Press tab to lower room", "Not all balls have been cleared!", "Room is lowered."}, glm::vec3(0.5f, 1.0f, 0.75f)));
		interactables.emplace_back(new GameObject(glm::vec3(11, 0.f, -3.f), std::vector<std::string>{"Press tab to launch zaku"}, glm::vec3(0.5f, 1.0f, 0.75f)));
		/*GameObject* swapCamButton = new GameObject();
		swapCamButton->pos = m_player.pos;
		swapCamButton->scale = glm::vec3(0.5f, 1.0f, 0.75f);*/
		cameraNum = 0;
		doorOpen = false;
		boosting = false;
}


void SceneAssignment::Update(double dt)
{
	HandleKeyPress();

	//std::cout << "Pos: " << cameraArray[0].position.x << ", " << cameraArray[0].position.y << ", " << cameraArray[0].position.z << std::endl;

	// spotlight for zaku cleaner view
	light[0].position = glm::vec3(cameraArray[1].position.x, cameraArray[1].position.y, cameraArray[1].position.z);
	light[0].spotDirection = glm::normalize(cameraArray[1].position - cameraArray[1].target);

	if (dirtBalls.size() < 1) {
		if (cameraNum == 1)
			interactables[0]->currText = 2;
		interactables[2]->currText = 0;
	}
	if (cameraNum == 1) 
		zakuCleaner.pos = cameraArray[1].position;
	showUI = false;
	for (int i = 0; i < interactables.size(); i++) {
		
		interactables[i]->interacting = (glm::distance(m_player.pos, interactables[i]->pos) < 1.5f);
		if (interactables[i]->interacting) {
			if (doorOpen == true and i == 1)
				continue;
			currInteractable = i;
			showUI = true;
		}
	}
	for (int j = 0; j < dirtBalls.size(); j++) {
		dirtBalls[j]->interacting = glm::distance(zakuCleaner.pos, dirtBalls[j]->pos) < zakuCleaner.scale.x + dirtBalls[j]->scale.x + 3;
	}
	if (KeyboardController::GetInstance()->IsKeyDown(GLFW_KEY_SPACE) && cameraNum == 1) {
		for (int j = 0; j < dirtBalls.size(); j++) {
			if (dirtBalls[j]->interacting && dirtBalls[j]->scale.x > 0) {
				dirtBalls[j]->scale.x -= 0.1f* static_cast<float>(dt);
				dirtBalls[j]->scale.y -= 0.1f* static_cast<float>(dt);
				dirtBalls[j]->scale.z -= 0.1f* static_cast<float>(dt);
			}
			else if (dirtBalls[j]->scale.x < 0) {
				dirtBalls[j]->scale = glm::vec3(0, 0, 0);
				dirtBalls.erase(dirtBalls.begin() + j);
			}
		}
	}
	if (doorOpen == true) {
		if (door1pos.z < 4.5f) {
			door1pos.z += 1.5f * static_cast<float>(dt);
			door2pos.z -= 1.5f * static_cast<float>(dt);
		}
	}
	if (lowered) {
		if (roomY > 0.1f) {
			roomY -= 0.001f * static_cast<float>(dt);
		}
		else
			interactables[2]->currText = 3;
	}
	// cameraArray[0] represents first person camera
	if (!lowered) {
		if (!doorOpen && cameraArray[0].position.x < 19) {
			cameraArray[0].position.x = 19.5;
		}
		if (cameraArray[0].position.x < 12) {
			cameraArray[0].position.x = 12.099;
		}
		if (cameraArray[0].position.x > 22) {
			cameraArray[0].position.x = 21.999;
		}
		if (cameraArray[0].position.z > 2.3) {
			cameraArray[0].position.z = 2.29;
		}if (cameraArray[0].position.z < -2.3) {
			cameraArray[0].position.z = -2.29;
		}
	}
	else
	{
		if (cameraArray[0].position.x < -50) {
			cameraArray[0].position.x = -49.999;
		}
		if (cameraArray[0].position.x > 50) {
			cameraArray[0].position.x = 49.999;
		}
		if (cameraArray[0].position.z > 50) {
			cameraArray[0].position.z = 49.999;
		}if (cameraArray[0].position.z < -50) {
			cameraArray[0].position.z = -49.999;
		}
	}
	if (boosting) {
		if (zakuPos.y < 80) {
			zakuPos.y += 5.f * static_cast<float>(dt);
		}
		light[4].power = 8.f;
		glUniform1f(m_parameters[U_LIGHT4_POWER], light[4].power);
		light[4].position = glm::vec3(0.f, zakuPos.y - 1, -1.5f);
	}

	cameraArray[0].position.y = roomY + 1.3;
	cameraArray[cameraNum].Update(dt);
	m_player.pos = cameraArray[0].position;
}

void SceneAssignment::Render()
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
	// Render objects
	modelStack.PushMatrix(); {
		RenderMesh(meshList[GEO_AXES], false);
	}modelStack.PopMatrix();
	modelStack.PushMatrix(); {
		modelStack.Translate(door1pos.x, door1pos.y, door1pos.z); 
		modelStack.Scale(0.1, 2, 2.5);
		RenderMesh(meshList[GEO_GREY_CUBE], false);
	} modelStack.PopMatrix();
	modelStack.PushMatrix(); {
		modelStack.Translate(door2pos.x, door2pos.y, door2pos.z);
		modelStack.Scale(0.1, 2, 2.5);
		RenderMesh(meshList[GEO_GREY_CUBE], false);
	} modelStack.PopMatrix();
	// render cleaner model
	if (cameraNum != 1) {
		modelStack.PushMatrix(); {
			modelStack.Translate(cameraArray[1].position.x, cameraArray[1].position.y, cameraArray[1].position.z);
			modelStack.PushMatrix(); {
				modelStack.Translate(0, 2, 0);
				if (interactables[0]->interacting && cameraNum != 1)
					RenderMesh(meshList[GEO_ARROW], false);
			} modelStack.PopMatrix();
			modelStack.Rotate(glm::degrees(atan2(cameraArray[1].rotatedView.x, cameraArray[1].rotatedView.z)), 0.f, 1.f, 0.f);
			modelStack.Rotate(glm::degrees(atan2(cameraArray[1].rotatedView.y, cameraArray[1].rotatedView.z)), 1.f, 0.f, 0.f);
			modelStack.Scale(0.05f, 0.05f, 0.05f);
			RenderMesh(meshList[GEO_CLEANER], true);
		} modelStack.PopMatrix();
	}
	for (int j = 0; j < dirtBalls.size(); j++) {
		modelStack.PushMatrix(); {
			modelStack.Translate(dirtBalls[j]->pos.x, dirtBalls[j]->pos.y, dirtBalls[j]->pos.z);
			modelStack.Scale(dirtBalls[j]->scale.x, dirtBalls[j]->scale.y, dirtBalls[j]->scale.z);
			RenderMesh(meshList[GEO_DIRTBALL], true);
		} modelStack.PopMatrix();
	}

	if (!cameraNum == 0) {
		modelStack.PushMatrix(); {
			modelStack.Translate(m_player.pos.x, m_player.pos.y, m_player.pos.z);
			modelStack.Rotate(glm::degrees(
				atan2(cameraArray[0].yawView.x, cameraArray[0].yawView.z)), 0.f, 1.f, 0.f);
			modelStack.Scale(0.18f, 0.18f, 0.18f);
			RenderMesh(meshList[GEO_PLAYER], false);
		} modelStack.PopMatrix();
	}
	modelStack.PushMatrix(); {
		RenderMesh(meshList[GEO_AXES], false);
	} modelStack.PopMatrix();

	// render hangar floor
	modelStack.PushMatrix(); {
		modelStack.Rotate(-90, 1.f, 0.f, 0.f);
		modelStack.Scale(50.f, 50.f, 1.f);
		RenderMesh(meshList[GEO_GREY_FLOOR], true);
	} modelStack.PopMatrix();
	// render hangar walls
	modelStack.PushMatrix(); {
		modelStack.PushMatrix(); {
			modelStack.Translate(0.f, 25.f, 25.f);
			modelStack.Rotate(-180, 0.f, 1.f, 0.f);
			modelStack.Scale(50, 50, 0);
			RenderMesh(meshList[GEO_SECONDARY_WALL_1], false);
		} modelStack.PopMatrix();
		modelStack.PushMatrix(); {
			modelStack.Translate(0.f, 25.f, -25.f);
			modelStack.Scale(50, 50, 0);
			RenderMesh(meshList[GEO_SECONDARY_WALL_1], false);
		} modelStack.PopMatrix();
		modelStack.PushMatrix(); {
			modelStack.Translate(25.f, 25.f, 0.f);
			modelStack.Rotate(-90, 0.f, 1.f, 0.f);
			modelStack.Scale(50, 50, 0);
			RenderMesh(meshList[GEO_SECONDARY_WALL_1], false);
		} modelStack.PopMatrix();
		modelStack.PushMatrix(); {
			modelStack.Translate(-25.f, 25.f, 0.f);
			modelStack.Rotate(90, 0.f, 1.f, 0.f);
			modelStack.Scale(50, 50, 0);
			RenderMesh(meshList[GEO_SECONDARY_WALL_1], false);
		} modelStack.PopMatrix();

	} modelStack.PopMatrix();

	// render zaku
	modelStack.PushMatrix(); {
		RenderZaku();
	} modelStack.PopMatrix();
	RenderSkybox();

	// control room
	RenderControlRoom();
	
	// UI
	if (showUI) {
		RenderMeshOnScreen(meshList[GEO_UI], 400, 55, 8, 0.5f);
		RenderTextOnScreen(meshList[GEO_TEXT], interactables[currInteractable]->strings[interactables[currInteractable]->currText], Color(1, 1, 1), 18, 15, 45);
	}
	if (cameraNum == 1) {
		RenderMeshOnScreen(meshList[GEO_CROSSHAIR], 400, 300, 800, 800);
	}
}


void SceneAssignment::RenderMesh(Mesh* mesh, bool enableLight)
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

void SceneAssignment::RenderMeshOnScreen(Mesh* mesh, float x, float y, float sizex, float sizey)
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

void SceneAssignment::RenderText(Mesh* mesh, std::string text, Color color)
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

void SceneAssignment::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
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

void SceneAssignment::RenderZaku()
{
	// Render the zaku
	//overall transform
	modelStack.PushMatrix(); {
		modelStack.Translate(zakuPos.x, zakuPos.y, zakuPos.z);
		// render torso parts
		modelStack.PushMatrix(); {
			// head 
			modelStack.PushMatrix(); {
				modelStack.Translate(0.0f, 2.1f, 0.0f);
				// top part of head
				modelStack.PushMatrix(); {
					modelStack.Rotate(180, 1.0f, 0.0f, 0.0f);
					RenderMesh(meshList[GEO_ZAKU_HEAD], true);
				} modelStack.PopMatrix();
				// black thing with eye
				modelStack.PushMatrix(); {
					// eye
					modelStack.Scale(0.8, 0.8, 0.8);
					modelStack.PushMatrix(); {
						modelStack.Translate(0.f, -0.1f, 1.f);
						modelStack.Rotate(90, 1.f, 0.f, 0.f);
						modelStack.Scale(0.3f, 0.1f, 0.3f);
						RenderMesh(meshList[GEO_CIRCLE], true);
					} modelStack.PopMatrix();
					RenderMesh(meshList[GEO_SPHERE_BLACK], true);
				} modelStack.PopMatrix();
				// toob around helmet
				modelStack.PushMatrix(); {
					modelStack.Translate(0.0f, -0.55f, 0.0f);
					modelStack.Scale(0.8f, 0.4f, 0.8f);
					RenderMesh(meshList[GEO_TORUS], true);
				} modelStack.PopMatrix();
				// left and right bar thing
				modelStack.PushMatrix(); {
					modelStack.Translate(-0.75, -0.2, 0.3);
					modelStack.Scale(0.2f, 0.8f, 0.2f);
					RenderMesh(meshList[GEO_ZAKU_CUBE_ALT], true);
				} modelStack.PopMatrix();
				modelStack.PushMatrix(); {
					modelStack.Translate(0.75, -0.2, 0.3);
					modelStack.Scale(0.2f, 0.8f, 0.2f);
					RenderMesh(meshList[GEO_ZAKU_CUBE_ALT], true);
				} modelStack.PopMatrix();
				modelStack.PushMatrix(); {
					modelStack.Translate(0.f, -0.6f, 1.15f);
					modelStack.Scale(0.6f, 0.35f, 0.2f);
					RenderMesh(meshList[GEO_ZAKU_CUBE_ALT], true);
				} modelStack.PopMatrix();
			} modelStack.PopMatrix();
			// right arm
			modelStack.PushMatrix(); {
				// shoulder joint
				modelStack.Translate(-3.25f, 0.25f, 0.f);
				modelStack.PushMatrix(); {
					modelStack.Translate(-1.f, -0.5f, 0.f);
					modelStack.Scale(0.1f, 4.f, 2.f);
					RenderMesh(meshList[GEO_ZAKU_CUBE_ALT], true);
				} modelStack.PopMatrix();
				modelStack.PushMatrix(); {
					modelStack.Translate(0.f, 1.47f, 0.f);
					modelStack.Scale(2, 0.1f, 2);
					RenderMesh(meshList[GEO_ZAKU_CUBE_ALT], true);
				} modelStack.PopMatrix();
				// upper arm
				modelStack.PushMatrix(); {
					modelStack.Translate(0.f, -1.45f, 0.f);
					// elbow 
					modelStack.PushMatrix(); {
						modelStack.Translate(0.f, -0.75f, 0.f);
						// lower arm
						modelStack.PushMatrix(); {
							modelStack.Translate(0.f, -0.35f, 0.f);
							modelStack.Scale(1.f, 1.5f, 1.f);
							modelStack.Translate(0.f, -0.5f, 0.f);
							// hand
							modelStack.PushMatrix(); {
								modelStack.Translate(0.f, -0.55f, 0.f);
								// bang
								modelStack.PushMatrix(); {
									modelStack.Translate(0.f, -0.3f, 0.f);
									// grip
									modelStack.PushMatrix(); {
										modelStack.Scale(0.1f, 0.1f, 2.f);
										RenderMesh(meshList[GEO_GREY_CUBE], true);
									} modelStack.PopMatrix();
									// mag
									modelStack.PushMatrix(); {
										modelStack.Translate(0.f, -0.5f, 0.f);
										modelStack.Scale(0.1f, 0.3f, 2.f);
										RenderMesh(meshList[GEO_GREY_CUBE], true);
									} modelStack.PopMatrix();
									// upper rec
									modelStack.PushMatrix(); {
										modelStack.Translate(0.f, 0.0f, 1.f);
										modelStack.Scale(0.3f, 2.5f, 0.3f);
										RenderMesh(meshList[GEO_GREY_CUBE], true);
									} modelStack.PopMatrix();
									// barrel
									modelStack.PushMatrix(); {
										modelStack.Translate(0.f, -1.35f, 1.35f);
										modelStack.Scale(0.5f, 3.5f, 0.7f);
										RenderMesh(meshList[GEO_GREY_CUBE], true);
									} modelStack.PopMatrix();
								} modelStack.PopMatrix();
								modelStack.Scale(0.1f, 2 / 3.f, 0.9f);
								RenderMesh(meshList[GEO_GREY_CUBE], true);
							} modelStack.PopMatrix();
							RenderMesh(meshList[GEO_ZAKU_CUBE_ALT], true);

						} modelStack.PopMatrix();
						modelStack.Scale(0.65f, 0.75f, 0.65f);
						RenderMesh(meshList[GEO_GREY_CUBE], true);
					} modelStack.PopMatrix();
					modelStack.Scale(1.2f, 1.2f, 1.f);
					RenderMesh(meshList[GEO_ZAKU_CUBE_ALT], true);
				} modelStack.PopMatrix();
				modelStack.Scale(1.6f, 1.7f, 1.5f);
				RenderMesh(meshList[GEO_ZAKU_CUBE_ALT], true);
			} modelStack.PopMatrix();
			// left arm
			modelStack.PushMatrix(); {
				// shoulder
				modelStack.Translate(3.25f, 0.25f, 0.f);
				modelStack.PushMatrix(); {
					modelStack.Translate(0.3f, 0.1f, 0.f);
					modelStack.Rotate(135, 0.0f, 0.f, 1.f);
					modelStack.Scale(1.2f, 1.2f, 1.2f);
					RenderMesh(meshList[GEO_ZAKU_HEAD], true);
				} modelStack.PopMatrix();
				// upper arm 
				modelStack.PushMatrix(); {
					modelStack.Translate(0.f, -1.45f, 0.f);
					// elbow
					modelStack.PushMatrix(); {
						modelStack.Translate(0.f, -0.75f, 0.f);
						// lower arm
						modelStack.PushMatrix(); {
							modelStack.Translate(0.f, -0.35f, 0.f);


							modelStack.Scale(1.f, 1.5f, 1.f);
							modelStack.Translate(0.f, -0.5f, 0.f);
							// hand
							modelStack.PushMatrix(); {
								modelStack.Translate(0.f, -0.55f, 0.f);
								modelStack.PushMatrix(); {
									// club
									modelStack.PushMatrix(); {
										modelStack.Scale(1.5f, 1.5f, 1.5f);

										modelStack.PushMatrix(); {
											modelStack.Translate(0.f, -0.2f, 1.5f);
											modelStack.PushMatrix(); {
												modelStack.Translate(0.f, 0.f, 1.8f);
												modelStack.Scale(0.1f, 2.f, 1.0f);
												RenderMesh(meshList[GEO_GREY_CUBE], true);
											} modelStack.PopMatrix();
											modelStack.Scale(0.2f, 0.2f, 5.f);
											RenderMesh(meshList[GEO_AXE_CUBE], true);
										} modelStack.PopMatrix();
									} modelStack.PopMatrix();
								} modelStack.PopMatrix();
								modelStack.Scale(0.1f, 2 / 3.f, 0.9f);
								RenderMesh(meshList[GEO_GREY_CUBE], true);
							} modelStack.PopMatrix();
							RenderMesh(meshList[GEO_ZAKU_CUBE_ALT], true);
						} modelStack.PopMatrix();
						modelStack.Scale(0.65f, 0.75f, 0.65f);
						RenderMesh(meshList[GEO_GREY_CUBE], true);
					} modelStack.PopMatrix();
					modelStack.Scale(1.2f, 1.2f, 1.f);
					RenderMesh(meshList[GEO_ZAKU_CUBE_ALT], true);
				} modelStack.PopMatrix();
				modelStack.Scale(1.6f, 1.7f, 1.5f);
				RenderMesh(meshList[GEO_ZAKU_CUBE_ALT], true);
			} modelStack.PopMatrix();
			modelStack.Scale(1.0f, 1.3f, 1.0f);
			// smaller  angled cubes on torso
			modelStack.PushMatrix(); {
				// grey
				modelStack.Translate(0.0f, 0.0f, 1.f);
				modelStack.Rotate(45, 1.0f, 0.0f, 0.0f);
				// green L
				modelStack.PushMatrix(); {
					modelStack.Translate(1.2f, 0.f, 0.f);
					modelStack.Scale(2.5f, 1.39f, 1.39f);
					RenderMesh(meshList[GEO_ZAKU_CUBE], true);
				} modelStack.PopMatrix();
				// green R
				modelStack.PushMatrix(); {
					modelStack.Translate(-1.2f, 0.f, 0.f);
					modelStack.Scale(2.5f, 1.39f, 1.39f);
					RenderMesh(meshList[GEO_ZAKU_CUBE], true);
				} modelStack.PopMatrix();
				modelStack.Scale(2.f, 1.4f, 1.4f);
				RenderMesh(meshList[GEO_GREY_CUBE], true);
				modelStack.PushMatrix(); {
					RenderMesh(meshList[GEO_ZAKU_CUBE], true);
				} modelStack.PopMatrix();
			} modelStack.PopMatrix();
			// green sides
			modelStack.PushMatrix(); {
				// LEFT
				modelStack.PushMatrix(); {
					// shoulder cube
					modelStack.Translate(1.5f, 0.f, 0.0f);
					modelStack.Scale(2.0f, 1.99f, 1.9f);
					RenderMesh(meshList[GEO_ZAKU_CUBE], true);
					// shoulder angled cube
				} modelStack.PopMatrix();
				// right
				modelStack.PushMatrix(); {
					modelStack.Translate(-1.5f, 0.f, 0.0f);
					modelStack.Scale(2.0f, 1.99f, 1.9f);
					RenderMesh(meshList[GEO_ZAKU_CUBE], true);
				} modelStack.PopMatrix();
			} modelStack.PopMatrix();
			// lower torso + skirts
			modelStack.PushMatrix(); {
				modelStack.Translate(0.f, -2.5f, 0.f);
				modelStack.Scale(3.f, 0.5f, 0.5f);
				RenderMesh(meshList[GEO_GREY_CUBE], true);
			} modelStack.PopMatrix();
			// booster
			modelStack.PushMatrix(); {
				modelStack.Translate(0.f, 0.f, -1.5f);
				if (boosting) {
					modelStack.PushMatrix(); {
						modelStack.Translate(0.f, -0.8f, 0.f);
						modelStack.Rotate(35, 1.f, 0.f, 0.0f);
						modelStack.Scale(0.5, 2.f, 0.5f);
						meshList[GEO_GREY_CUBE]->material.kAmbient.Set(225 / 255.f, 88 / 255.f, 34 / 255.f);
						meshList[GEO_GREY_CUBE]->material.kDiffuse.Set(235 / 255.f, 98 / 255.f, 44 / 255.f);
						meshList[GEO_GREY_CUBE]->material.kSpecular.Set(245 / 255.f, 108 / 255.f, 54 / 255.f);
						meshList[GEO_GREY_CUBE]->material.kShininess = 40.0f;
						RenderMesh(meshList[GEO_GREY_CUBE], true);
						meshList[GEO_GREY_CUBE]->material.kAmbient.Set(88 / 255.f, 88 / 255.f, 88 / 255.f);
						meshList[GEO_GREY_CUBE]->material.kDiffuse.Set(98 / 255.f, 98 / 255.f, 98 / 255.f);
						meshList[GEO_GREY_CUBE]->material.kSpecular.Set(108 / 255.f, 108 / 255.f, 108 / 255.f);
					} modelStack.PopMatrix();
					modelStack.PushMatrix(); {
						modelStack.Translate(0.f, -0.8f, 0.f);
						modelStack.Rotate(35, 1.f, 0.f, 0.7f);
						modelStack.Scale(0.5, 1.5f, 0.5f);
						meshList[GEO_GREY_CUBE]->material.kAmbient.Set(225 / 255.f, 88 / 255.f, 34 / 255.f);
						meshList[GEO_GREY_CUBE]->material.kDiffuse.Set(235 / 255.f, 98 / 255.f, 44 / 255.f);
						meshList[GEO_GREY_CUBE]->material.kSpecular.Set(245 / 255.f, 108 / 255.f, 54 / 255.f);
						meshList[GEO_GREY_CUBE]->material.kShininess = 40.0f;
						RenderMesh(meshList[GEO_GREY_CUBE], true);
						meshList[GEO_GREY_CUBE]->material.kAmbient.Set(88 / 255.f, 88 / 255.f, 88 / 255.f);
						meshList[GEO_GREY_CUBE]->material.kDiffuse.Set(98 / 255.f, 98 / 255.f, 98 / 255.f);
						meshList[GEO_GREY_CUBE]->material.kSpecular.Set(108 / 255.f, 108 / 255.f, 108 / 255.f);
					} modelStack.PopMatrix();
					modelStack.PushMatrix(); {
						modelStack.Translate(0.f, -0.8f, 0.f);
						modelStack.Rotate(35, 1.f, 0.f, -0.7f);
						modelStack.Scale(0.5, 1.5f, 0.5f);
						meshList[GEO_GREY_CUBE]->material.kAmbient.Set(225 / 255.f, 88 / 255.f, 34 / 255.f);
						meshList[GEO_GREY_CUBE]->material.kDiffuse.Set(235 / 255.f, 98 / 255.f, 44 / 255.f);
						meshList[GEO_GREY_CUBE]->material.kSpecular.Set(245 / 255.f, 108 / 255.f, 54 / 255.f);
						meshList[GEO_GREY_CUBE]->material.kShininess = 40.0f;
						RenderMesh(meshList[GEO_GREY_CUBE], true);
						meshList[GEO_GREY_CUBE]->material.kAmbient.Set(88 / 255.f, 88 / 255.f, 88 / 255.f);
						meshList[GEO_GREY_CUBE]->material.kDiffuse.Set(98 / 255.f, 98 / 255.f, 98 / 255.f);
						meshList[GEO_GREY_CUBE]->material.kSpecular.Set(108 / 255.f, 108 / 255.f, 108 / 255.f);
					} modelStack.PopMatrix();
				}
				RenderMesh(meshList[GEO_GREY_CUBE], true);
			} modelStack.PopMatrix();
			modelStack.Scale(2.f, 2.f, 2.f);
			meshList[GEO_GREY_CUBE]->Render();
			RenderMesh(meshList[GEO_GREY_CUBE], true);
			// tubey things near stomach
			modelStack.PushMatrix(); {
				modelStack.Translate(0.0f, -0.2f, 0.0f);
				modelStack.Scale(0.8f, 0.8f, 0.8f);
				modelStack.PushMatrix(); {
					modelStack.Translate(0.0f, -0.7f, 0.0f);
					// front
					modelStack.PushMatrix(); {
						modelStack.Translate(0.0f, 0.0f, 0.8f);
						// stomach tube front 1
						modelStack.PushMatrix(); {
							modelStack.Rotate(90, 0.0f, 0.0f, 1.0f);
							modelStack.Scale(0.25f, 1.0f, 0.25f);
							RenderMesh(meshList[GEO_ZAKU_CYLINDER], true);
							meshList[GEO_ZAKU_CYLINDER]->Render();
						} modelStack.PopMatrix();
						modelStack.PushMatrix(); {
							modelStack.Rotate(-90, 0.0f, 0.0f, 1.0f);
							modelStack.Scale(0.25f, 1.0f, 0.25f);
							RenderMesh(meshList[GEO_ZAKU_CYLINDER], true);
							meshList[GEO_ZAKU_CYLINDER]->Render();
						} modelStack.PopMatrix();
						// stomach cube front 1
						modelStack.PushMatrix(); {
							modelStack.Translate(0.75f, 0.0f, 0.0f);
							modelStack.Scale(0.5f, 0.5f, 0.5f);
							RenderMesh(meshList[GEO_ZAKU_CUBE_ALT], true);
						} modelStack.PopMatrix();
						// stomach cube front 2
						modelStack.PushMatrix(); {
							modelStack.Translate(-0.75f, 0.0f, 0.0f);
							modelStack.Scale(0.5f, 0.5f, 0.5f);
							RenderMesh(meshList[GEO_ZAKU_CUBE_ALT], true);
						} modelStack.PopMatrix();
					} modelStack.PopMatrix();
					// rear toob + cube
					modelStack.PushMatrix(); {
						modelStack.Translate(0.0f, 0.0f, -0.8f);
						// stomach tube rear 1
						modelStack.PushMatrix(); {
							modelStack.Translate(-0.5f, 0.f, 0.f);
							modelStack.Rotate(90, 0.0f, 0.0f, 1.0f);
							modelStack.Scale(0.25f, 2.0f, 0.25f);
							RenderMesh(meshList[GEO_ZAKU_CYLINDER_ALT], true);
						} modelStack.PopMatrix();
						// stomach cube rear 1
						modelStack.PushMatrix(); {
							modelStack.Translate(0.75f, 0.0f, 0.0f);
							modelStack.Scale(0.5f, 0.5f, 0.5f);
							RenderMesh(meshList[GEO_ZAKU_CUBE_ALT], true);
						} modelStack.PopMatrix();
						// stomach cube rear 2
						modelStack.PushMatrix(); {
							modelStack.Translate(-0.75f, 0.0f, 0.0f);
							modelStack.Scale(0.5f, 0.5f, 0.5f);
							RenderMesh(meshList[GEO_ZAKU_CUBE_ALT], true);
						} modelStack.PopMatrix();
					} modelStack.PopMatrix();
					// left toob
					modelStack.PushMatrix(); {
						modelStack.Translate(0.75f, 0.0f, 0.6f);
						modelStack.Rotate(90, 1.0f, 0.0f, 0.0f);
						modelStack.Scale(0.25f, 2.5f, 0.25f);
						RenderMesh(meshList[GEO_ZAKU_CYLINDER_ALT], true);
					} modelStack.PopMatrix();
					// right toob
					modelStack.PushMatrix(); {
						modelStack.Translate(-0.75f, 0.0f, 0.6f);
						modelStack.Rotate(90, 1.0f, 0.0f, 0.0f);
						modelStack.Scale(0.25f, 2.5f, 0.25f);
						RenderMesh(meshList[GEO_ZAKU_CYLINDER_ALT], true);
					} modelStack.PopMatrix();
				}modelStack.PopMatrix();
			} modelStack.PopMatrix();
			modelStack.PushMatrix(); {
				modelStack.Translate(0.0f, -0.5f, 0.0f);
				modelStack.Scale(0.7f, 1.f, 0.7f);
				RenderMesh(meshList[GEO_GREY_CUBE], true);
			} modelStack.PopMatrix();
		} modelStack.PopMatrix();
		// upper hips and skirts
		modelStack.PushMatrix(); {
			modelStack.Translate(0.f, -3.25f, 0.f);
			modelStack.PushMatrix(); {
				modelStack.PushMatrix(); {
					modelStack.Scale(4, 1.0f, 3);
					RenderMesh(meshList[GEO_ZAKU_CUBE], true);
				} modelStack.PopMatrix();
				modelStack.Scale(1.f, 2.5f, 1.f);
				RenderMesh(meshList[GEO_GREY_CUBE], true);
			} modelStack.PopMatrix();
		} modelStack.PopMatrix();
		// lower hips 
		modelStack.PushMatrix(); {
			modelStack.Translate(0.0f, -4.5f, 0.0f);
			// legs
			modelStack.PushMatrix(); {
				modelStack.Scale(0.75f, 1.0f, 1.0f);
				// right leg
				modelStack.PushMatrix(); {
					modelStack.Translate(-1.75f, 0.0f, 0.0f);
					// lower leg
					modelStack.PushMatrix(); {
						// moves lower leg + knee
						modelStack.Translate(-0.7f, -1.8f, 0.0f);
						// lower leg
						modelStack.PushMatrix(); {
							modelStack.Translate(0.7f, -0.6f, 0.0f);
							// feet
							modelStack.PushMatrix(); {
								modelStack.Translate(0.f, -3.f, 0.0f);
								// top of foot
								modelStack.PushMatrix(); {
									modelStack.Translate(0.f, 0.7f, 0.25f);
									modelStack.Scale(0.8f, 1.0f, 1.7f);
									RenderMesh(meshList[GEO_GREY_CUBE], true);
								} modelStack.PopMatrix();
								// heel
								modelStack.PushMatrix(); {
									modelStack.Translate(0.f, 0.f, -0.5f);
									modelStack.Scale(1.0f, 0.5f, 1.0f);
									RenderMesh(meshList[GEO_GREY_CUBE], true);
								} modelStack.PopMatrix();
								// front 
								modelStack.PushMatrix(); {
									modelStack.Translate(0.f, 0.f, 1.5f);
									modelStack.Scale(1.0f, 0.5f, 1.0f);
									RenderMesh(meshList[GEO_GREY_CUBE], true);
								} modelStack.PopMatrix();
							} modelStack.PopMatrix();
							modelStack.Scale(1.5f, 1.8f, 1.5f);
							modelStack.Translate(0.0f, -0.5f, 0.0f);
							RenderMesh(meshList[GEO_ZAKU_CUBE_ALT], true);

						} modelStack.PopMatrix();
						// knee
						modelStack.Rotate(90, 0.0f, 0.0f, 1.0f);
						modelStack.Scale(1.0f, 2.5f, 0.5f);
						RenderMesh(meshList[GEO_GREY_CYLINDER], true);
					} modelStack.PopMatrix();
					// upper leg piece
					modelStack.PushMatrix(); {
						//modelStack.PushMatrix();
						// moves upper leg
						modelStack.Translate(0.0f, -0.5f, 0.0f);
						// front outer upper leg piece
						modelStack.PushMatrix(); {
							modelStack.Translate(-1.f, -0.39f, 0.0f);
							modelStack.Scale(0.5f, 3.2f, 1.5f);
							RenderMesh(meshList[GEO_ZAKU_CUBE], true);
						} modelStack.PopMatrix();
						modelStack.Scale(1.5f, 2.5, 1.5f);
						RenderMesh(meshList[GEO_ZAKU_CUBE_ALT], true);
					} modelStack.PopMatrix();
					RenderMesh(meshList[GEO_ZAKU_CUBE_ALT], true);
				} modelStack.PopMatrix();
				// left leg
				modelStack.PushMatrix(); {
					modelStack.Translate(1.75f, 0.0f, 0.0f);
					// lower leg
					modelStack.PushMatrix(); {
						// moves lower leg + knee
						modelStack.Translate(-0.7f, -1.8f, 0.0f);
						// lower leg
						modelStack.PushMatrix(); {
							modelStack.Translate(0.7f, -0.6f, 0.0f);
							// feet
							modelStack.PushMatrix(); {
								modelStack.Translate(0.f, -3.f, 0.0f);
								// top of foot
								modelStack.PushMatrix(); {
									modelStack.Translate(0.f, 0.7f, 0.25f);
									modelStack.Scale(0.8f, 1.0f, 1.7f);
									RenderMesh(meshList[GEO_GREY_CUBE], true);
								} modelStack.PopMatrix();
								// heel
								modelStack.PushMatrix(); {
									modelStack.Translate(0.f, 0.f, -0.5f);
									modelStack.Scale(1.0f, 0.5f, 1.0f);
									RenderMesh(meshList[GEO_GREY_CUBE], true);
								} modelStack.PopMatrix();
								// front 
								modelStack.PushMatrix(); {
									modelStack.Translate(0.f, 0.f, 1.5f);
									modelStack.Scale(1.0f, 0.5f, 1.0f);
									RenderMesh(meshList[GEO_GREY_CUBE], true);
								} modelStack.PopMatrix();
							} modelStack.PopMatrix();
							modelStack.Scale(1.5f, 1.8f, 1.5f);
							modelStack.Translate(0.0f, -0.5f, 0.0f);
							RenderMesh(meshList[GEO_ZAKU_CUBE_ALT], true);

						} modelStack.PopMatrix();
						// little extra flap
						modelStack.PushMatrix(); {
							modelStack.Translate(0.7f, -0.6f, 0.0f);
							modelStack.Scale(1.5f, 1.8f, 1.5f);
							modelStack.Translate(0.0f, -0.5f, 0.0f);
							RenderMesh(meshList[GEO_ZAKU_CUBE_ALT], true);
						} modelStack.PopMatrix();
						// knee 
						modelStack.Rotate(90, 0.0f, 0.0f, 1.0f);
						modelStack.Scale(1.0f, 2.5f, 0.5f);
						RenderMesh(meshList[GEO_GREY_CYLINDER], true);
					} modelStack.PopMatrix();
					// upper leg
					modelStack.PushMatrix(); {
						modelStack.Translate(0.0f, -0.5f, 0.0f);
						// front outer upper leg piece
						modelStack.PushMatrix(); {
							modelStack.Translate(1.0f, -0.39f, 0.0f);
							modelStack.Scale(0.5f, 3.2f, 1.5f);
							RenderMesh(meshList[GEO_ZAKU_CUBE], true);
						} modelStack.PopMatrix();
						modelStack.Scale(1.5f, 2.5f, 1.5f);
						RenderMesh(meshList[GEO_ZAKU_CUBE_ALT], true);
					} modelStack.PopMatrix();
					RenderMesh(meshList[GEO_ZAKU_CUBE_ALT], true);

				} modelStack.PopMatrix();
			} modelStack.PopMatrix();
			modelStack.Scale(2.5f, 1.0f, 1.0f);
			RenderMesh(meshList[GEO_GREY_CUBE], true);
		} modelStack.PopMatrix();

	} modelStack.PopMatrix();
}

void SceneAssignment::RenderSkybox()
{
	modelStack.PushMatrix(); {
		modelStack.Translate(0.f, -500.f, 0.f);
		modelStack.Rotate(-90, 1.f, 0.f, 0.f);
		modelStack.Scale(10, 10, 0);
		RenderMesh(meshList[GEO_BOTTOM], false);
	}  modelStack.PopMatrix();
	modelStack.PushMatrix(); {
		modelStack.Translate(0.f, 500.f, 0.f);
		modelStack.Rotate(90, 1.f, 0.f, 0.f);
		modelStack.Scale(10, 10, 0);
		RenderMesh(meshList[GEO_TOP], false);
	} modelStack.PopMatrix();
	modelStack.PushMatrix(); {
		modelStack.Translate(0.f, 0.f, 500.f);
		modelStack.Rotate(-180, 0.f, 1.f, 0.f);
		modelStack.Scale(10, 10, 0);
		RenderMesh(meshList[GEO_LEFT], false);
	} modelStack.PopMatrix();
	modelStack.PushMatrix(); {
		modelStack.Translate(0.f, 0.f, -500.f);
		modelStack.Scale(10, 10, 0);
		RenderMesh(meshList[GEO_RIGHT], false);
	} modelStack.PopMatrix();
	modelStack.PushMatrix(); {
		modelStack.Translate(500.f, 0.f, 0.f);
		modelStack.Rotate(-90, 0.f, 1.f, 0.f);
		modelStack.Scale(10, 10, 0);
		RenderMesh(meshList[GEO_BACK], false);
	} modelStack.PopMatrix();
	modelStack.PushMatrix(); {
		modelStack.Translate(-500.f, 0.f, 0.f);
		modelStack.Rotate(90, 0.f, 1.f, 0.f);
		modelStack.Scale(10, 10, 0);
		RenderMesh(meshList[GEO_FRONT], false);
	} modelStack.PopMatrix();
}

void SceneAssignment::RenderLight(int lightIndex)
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

void SceneAssignment::RenderControlRoom() {

	modelStack.PushMatrix(); {
		// main room floor
		modelStack.Translate(15.f, roomY, 0.f);
		modelStack.PushMatrix(); {
			modelStack.Translate(0.f, 0.1f, 0.f);
			modelStack.Rotate(-90, 1.0f, 0, 0);
			modelStack.PushMatrix(); {
				modelStack.Translate(5.f, 0.f, 0.f);
				RenderMesh(meshList[GEO_GENERAL_FLOOR_5], true);
			} modelStack.PopMatrix();
			RenderMesh(meshList[GEO_GENERAL_FLOOR_5], true);
		} modelStack.PopMatrix();
		modelStack.PushMatrix(); {
			modelStack.Rotate(-90, 1.0f, 0, 0);
			RenderMesh(meshList[GEO_GENERAL_FLOOR_5], true);
		} modelStack.PopMatrix();
		// main ceiling
		modelStack.PushMatrix(); {
			modelStack.Translate(0.f, 2.f, 0.f);
			modelStack.PushMatrix(); {
				modelStack.Translate(2.5f, 0.1f, 0.f);
				modelStack.Scale(10, 0.1f, 5.2);
				RenderMesh(meshList[GEO_GREY_CUBE], true);
			} modelStack.PopMatrix();
			modelStack.PushMatrix(); {
				modelStack.Rotate(180, 0.f, 0.f, 1.f);
				modelStack.Rotate(-90, 1.0f, 0, 0);
				RenderMesh(meshList[GEO_GENERAL_FLOOR_5], true);
			} modelStack.PopMatrix();
			modelStack.PushMatrix(); {
				modelStack.Translate(5.f, 0.f, 0.f);
				modelStack.Rotate(180, 0.f, 0.f, 1.f);
				modelStack.Rotate(-90, 1.0f, 0, 0);
				RenderMesh(meshList[GEO_GENERAL_FLOOR_5], true);
			} modelStack.PopMatrix();
		} modelStack.PopMatrix();
		// wall right
		modelStack.PushMatrix(); {
			modelStack.Translate(0.f, 1.f, -2.5f);
			modelStack.PushMatrix(); {
				modelStack.PushMatrix(); {
					modelStack.Translate(2.5f, 0.f, -0.1f);
					modelStack.Scale(10, 2, 0.1f);
					RenderMesh(meshList[GEO_GREY_CUBE], true);
				} modelStack.PopMatrix();
			} modelStack.PopMatrix();
			modelStack.PushMatrix(); {
				modelStack.Translate(-1.5f, 0.f, 0.f);
				RenderMesh(meshList[GEO_GENERAL_WALL_2], true);
			} modelStack.PopMatrix();
			modelStack.PushMatrix(); {
				modelStack.Translate(0.5f, 0.f, 0.f);
				RenderMesh(meshList[GEO_GENERAL_WALL_2], true);
			} modelStack.PopMatrix();
			modelStack.PushMatrix(); {
				modelStack.Translate(2.5f, 0.f, 0.f);
				RenderMesh(meshList[GEO_GENERAL_WALL_2], true);
			} modelStack.PopMatrix();
			modelStack.PushMatrix(); {
				modelStack.Translate(4.5f, 0.f, 0.f);
				RenderMesh(meshList[GEO_GENERAL_WALL_2], true);
			} modelStack.PopMatrix();
			modelStack.PushMatrix(); {
				modelStack.Translate(6.5f, 0.f, 0.f);
				RenderMesh(meshList[GEO_GENERAL_WALL_2], true);
			} modelStack.PopMatrix();
			modelStack.PushMatrix(); {
				modelStack.Translate(7.5f, 0.f, 1.0f);
				modelStack.Rotate(-90, 0.f, 1.f, 0.f);
				RenderMesh(meshList[GEO_GENERAL_WALL_2], true);
			} modelStack.PopMatrix();
		} modelStack.PopMatrix();

		// wall left
		modelStack.PushMatrix(); {
			modelStack.Translate(0.f, 1.f, 2.5f);
			modelStack.Rotate(180, 0.f, 1.f, 0.f);
			modelStack.PushMatrix(); {
				modelStack.PushMatrix(); {
					modelStack.Translate(-2.5f, 0.f, -0.1f);
					modelStack.Scale(10, 2, 0.1f);
					RenderMesh(meshList[GEO_GREY_CUBE], true);
				} modelStack.PopMatrix();
				modelStack.Translate(-1.5f, 0.f, 0.f);
				RenderMesh(meshList[GEO_GENERAL_WALL_2], true);
			} modelStack.PopMatrix();
			modelStack.PushMatrix(); {
				modelStack.Translate(0.5f, 0.f, 0.f);
				RenderMesh(meshList[GEO_GENERAL_WALL_2], true);
			} modelStack.PopMatrix();
			modelStack.PushMatrix(); {
				modelStack.Translate(-2.5f, 0.f, 0.f);
				RenderMesh(meshList[GEO_GENERAL_WALL_2], true);
			} modelStack.PopMatrix();
			modelStack.PushMatrix(); {
				modelStack.Translate(-4.5f, 0.f, 0.f);
				RenderMesh(meshList[GEO_GENERAL_WALL_2], true);
			} modelStack.PopMatrix();
			modelStack.PushMatrix(); {
				modelStack.Translate(-6.5f, 0.f, 0.f);
				RenderMesh(meshList[GEO_GENERAL_WALL_2], true);
			} modelStack.PopMatrix();
			modelStack.PushMatrix(); {
				modelStack.Translate(-7.5f, 0.f, 1.0f);
				modelStack.Rotate(90, 0.f, 1.f, 0.f);
				RenderMesh(meshList[GEO_GENERAL_WALL_2], true);
			} modelStack.PopMatrix();
			modelStack.PushMatrix(); {
				modelStack.Translate(-7.5f, 0.f, 2.5f);
				modelStack.Rotate(90, 0.f, 1.f, 0.f);
				RenderMesh(meshList[GEO_GENERAL_WALL_2], true);
			} modelStack.PopMatrix();
		} modelStack.PopMatrix();
	} modelStack.PopMatrix();

	// render control room objects
	//render touch screen
	modelStack.PushMatrix(); {
		modelStack.Translate(interactables[0]->pos.x, roomY, interactables[0]->pos.z);
		modelStack.Rotate(90, 0.f, 1.f, 0.f);
		//modelStack.Scale(interactables[0]->scale.x, interactables[0]->scale.y, interactables[0]->scale.z);
		RenderMesh(meshList[GEO_TOUCHSCREEN1], false);
	} modelStack.PopMatrix();

	modelStack.PushMatrix(); {
		modelStack.Translate(interactables[2]->pos.x, roomY, interactables[2]->pos.z);
		modelStack.Rotate(90, 0.f, 1.f, 0.f);
		//modelStack.Scale(interactables[0]->scale.x, interactables[0]->scale.y, interactables[0]->scale.z);
		RenderMesh(meshList[GEO_TOUCHSCREEN2], false);
	} modelStack.PopMatrix();

	modelStack.PushMatrix(); {
		modelStack.Translate(interactables[3]->pos.x, interactables[3]->pos.y, interactables[3]->pos.z);
		//modelStack.Rotate(90, 0.f, 1.f, 0.f);
		//modelStack.Scale(interactables[0]->scale.x, interactables[0]->scale.y, interactables[0]->scale.z);
		RenderMesh(meshList[GEO_TOUCHSCREEN2], false);
	} modelStack.PopMatrix();

	modelStack.PushMatrix(); {
		modelStack.Translate(17.f, roomY + 0.5f, 2.49f);
		modelStack.Rotate(180, 0.f, 1.f, 0.f);
		modelStack.Scale(0.25f, 1.f, 1.f);
		RenderText(meshList[GEO_TEXT], std::string("Dirtballs left: " + std::to_string(dirtBalls.size())), (255 / 255.f, 182 / 255.f, 0.f));
	} modelStack.PopMatrix();
}

void SceneAssignment::Exit()
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
	for (int i = 0; i < dirtBalls.size(); ++i)
	{
		if (dirtBalls[i])
		{
			delete dirtBalls[i];
		}
	}
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}

void SceneAssignment::HandleKeyPress()
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

	// cam change
	if (KeyboardController::GetInstance()->IsKeyPressed(GLFW_KEY_TAB)) {
		if (interactables[0]->interacting) {
			if (cameraNum == 0) {
				cameraNum = 1;
			}
			else
				cameraNum = 0;
			interactables[0]->currText = cameraNum;
		}
		else if (interactables[1]->interacting) 
			doorOpen = true;
		else if (interactables[2]->interacting) {
			if (dirtBalls.size() < 1) {

				lowered = true;
				interactables[2]->currText = 2;
			}
			else
				interactables[2]->currText = 1;
		}
		else if (interactables[3]->interacting) {
			boosting = true;
		}

	}
	
}
