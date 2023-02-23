#include "SceneHitMen.h"
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
#include "SceneManager.h"
#include "Player.h"

SceneHitMen::SceneHitMen()
{
	srand(rand());
	srand(rand() % rand());
	srand(rand() % rand() % rand());
}

SceneHitMen::~SceneHitMen()
{
	/*for (std::vector<GameObject*>::iterator iter = interactables.begin(); iter != interactables.end(); iter++) {
		if (!(*iter == nullptr)) {
			delete* iter;
		}
	}*/
}

void SceneHitMen::Init()
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
		initCamY = 8.8;
		// Initialise camera properties
		//mainFPSCam.Init(glm::vec3(21, initCamY, 0.f), glm::vec3(0, initCamY, 0), glm::vec3(0.f, initCamY, 0.f));
		gunCam.Init(glm::vec3(0, initCamY, 27.f), glm::vec3(0, initCamY, 0), glm::vec3(0.f, 1, 0.f), false, false);
		mainFPSCam.Init(glm::vec3(0,0, 0.f), glm::vec3(-1, 0, 0), glm::vec3(0.f, 1, 0.f));
		// Init VBO here
		for (int i = 0; i < NUM_GEOMETRY; ++i)
		{
			meshList[i] = nullptr;
		}
		int counter = 0;
		int offSet = 0;
		for (int i = -2; i < 3; i++) {
			for (int j = -2; j < 3; j++) {
				doorMen.emplace_back(new GameObject);
				doorMen[counter]->pos = (glm::vec3(- 1 * j * 3.f + offSet, 9.5f + offSet, -1 * i * 1.1f));
				doorMenInitPos.emplace_back(doorMen[counter]->pos);
				doorMen[counter]->scale = glm::vec3(0.5f, 3.5f, 0.5f);
				doorMen[counter]->vel = glm::vec3(0, 0, 0);
				doorMen[counter]->force = glm::vec3(0, 0, 0);
				doorMen[counter]->active = true;
				doorMen[counter]->mass = 5;
				doorMen[counter]->momentOfInertia = 1.f;
				doorMen[counter]->dir = glm::vec3(0, 0, 1);
				counter += 1;
			}
			offSet += 1;
		}
		for (int i = 0; i < NUM_SHELLS; i++) {
			m_grapeShot[i] = new GameObject;
			m_grapeShot[i]->dir = glm::vec3(0, 0, 1);
			m_grapeShot[i]->pos = glm::vec3(gunCam.position.x, 6.5f, gunCam.position.z);
			m_grapeShot[i]->scale = glm::vec3(0.05f, 0.05f, 0.05f);
			m_grapeShot[i]->force = glm::vec3(0, 0, 0);
			m_grapeShot[i]->active = true;
			m_grapeShot[i]->mass = 0.5f;
			m_grapeShot[i]->momentOfInertia = 1.f;
			m_grapeShot[i]->vel = glm::vec3(0, 0, 0);
		}
		m_table1.pos = glm::vec3(0, 4.5f, 0);
		m_table1.scale = glm::vec3(28.f, 0.5f, 5.5f);
		m_table1.force = glm::vec3(0.f);
		m_table1.vel = glm::vec3(0.f);
		m_table1.mass = 10.f;

		m_table2.pos = glm::vec3(0, 5.6f, 0.8f);
		m_table2.scale = glm::vec3(28.f, 0.5f, 1.1f);
		m_table2.force = glm::vec3(0.f);
		m_table2.vel = glm::vec3(0.f);
		m_table2.mass = 10.f;

		m_table3.pos = glm::vec3(0, 6.6f, -0.2f);
		m_table3.scale = glm::vec3(28.f, 0.5f, 1.1f);
		m_table3.force = glm::vec3(0.f);
		m_table3.vel = glm::vec3(0.f);
		m_table3.mass = 10.f;

		m_floor.pos = glm::vec3(0, 0, 0);
		m_floor.scale = glm::vec3(100, 0, 100);
		// meshList
		{
			meshList[GEO_AXES] = MeshBuilder::GenerateAxes("Axes", 10000.f, 10000.f, 10000.f);
			meshList[GEO_SPHERE] = MeshBuilder::GenerateSphere("Sun", Color(1.f, 1.f, 1.f), 1.f, 16, 16);
			meshList[GEO_CUBE] = MeshBuilder::GenerateCube("Arm", Color(247 / 255.f, 181 / 255.f, 0), 1.f);

			meshList[GEO_DOORMAN] = MeshBuilder::GenerateOBJ("doorman","OBJ//doorman.obj");
			meshList[GEO_DOORMAN]->textureID = LoadTGA("image//doorman.tga");
			meshList[GEO_TABLE] = MeshBuilder::GenerateOBJ("table", "OBJ//table.obj");
			meshList[GEO_TABLE]->textureID = LoadTGA("image//table.tga");
			meshList[GEO_TENT] = MeshBuilder::GenerateOBJ("tent", "OBJ//tent.obj");
			meshList[GEO_TENT]->textureID = LoadTGA("image//tent.tga");
			meshList[GEO_GUN] = MeshBuilder::GenerateOBJMTL("gun", "OBJ//mosin.obj", "OBJ//mosin.mtl");
			meshList[GEO_GUN]->textureID = LoadTGA("image//mosin.tga");

			// skybox
			meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("Plane", Color(1.f, 1.f, 1.f), 100.f);
			meshList[GEO_LEFT]->textureID = LoadTGA("Image//skyboxleft.tga");
			meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("Plane", Color(1.f, 1.f, 1.f), 100.f);
			meshList[GEO_RIGHT]->textureID = LoadTGA("Image//skyboxright.tga");
			meshList[GEO_TOP] = MeshBuilder::GenerateQuad("Plane", Color(1.f, 1.f, 1.f), 100.f);
			meshList[GEO_TOP]->textureID = LoadTGA("Image//skyboxtop.tga");
			meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("Plane", Color(1.f, 1.f, 1.f), 100.f);
			meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//skyboxbottom.tga");
			meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("Plane", Color(1.f, 1.f, 1.f), 100.f);
			meshList[GEO_FRONT]->textureID = LoadTGA("Image//skyboxfront.tga");
			meshList[GEO_BACK] = MeshBuilder::GenerateQuad("Plane", Color(1.f, 1.f, 1.f), 100.f);
			meshList[GEO_BACK]->textureID = LoadTGA("Image//skyboxback.tga");
			meshList[GEO_TABLE]->material.kAmbient.Set(0.3f, 0.3f, 0.3f);
			meshList[GEO_TABLE]->material.kDiffuse.Set(0.7f, 0.7f, 0.7f);
			meshList[GEO_TABLE]->material.kSpecular.Set(0.9f, 0.9f, 0.9f);
			meshList[GEO_TABLE]->material.kShininess = 5.0f;
			meshList[GEO_TEXT] = MeshBuilder::GenerateText("comic sanz", 16, 16);
			meshList[GEO_TEXT]->textureID = LoadTGA("Image//ComicSans.tga");

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
		};

		glm::mat4 projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 1000.0f);
		projectionStack.LoadMatrix(projection);

		zakuPos = glm::vec3(0, 10.f, 0);

		glUniform1i(m_parameters[U_NUMLIGHTS], NUM_LIGHTS);
		// light params
		{
			// environment light
			light[0].position = glm::vec3(0, 25, 0);
			light[0].color.Set(1, 1, 1);
			light[0].type = Light::LIGHT_DIRECTIONAL;
			light[0].power = 1.f;
			light[0].kC = 1.f;
			light[0].kL = 0.01f;
			light[0].kQ = 0.001f;
			light[0].cosCutoff = 5.f;
			light[0].cosInner = 1.f;
			light[0].exponent = 3.f;
			light[0].spotDirection = glm::vec3(0, -1, 0);


			// main tent light 
			light[1].position = glm::vec3(0, 15, 0);
			light[1].type = Light::LIGHT_SPOT;
			//light[1].color.Set(1, 1, 1);
			light[1].color.Set(247 / 255.f, 181 / 255.f, 0);
			light[1].spotDirection = glm::vec3(0, 1, 0);
			light[1].power = 2.f;
			light[1].kC = 1.f;
			light[1].kL = 0.01f;
			light[1].kQ = 0.001f;
			light[1].cosCutoff = 45.f;
			light[1].cosInner = 30.f;
			light[1].exponent = 3.f;

			// room light 1
			light[2].position = glm::vec3(15, 10.f, 0);
			light[2].power = 0.f;
			light[2].type = Light::LIGHT_POINT;
			light[2].spotDirection = glm::vec3(0.f, -1.f, 0.f);
			light[2].cosCutoff = 65.f;
			light[2].cosInner = 10.f;
			light[2].exponent = 3.f;

			// room light 2
			light[3].position = glm::vec3(21, 10.f, 0);
			light[3].power = 0.f;
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
		m_bullet.mass = 1;
		m_bullet.pos = glm::vec3(gunCam.position.x, 6.5f, gunCam.position.z);
		m_bullet.dir = glm::vec3(0, 0, 1.f);
		m_bullet.vel = glm::vec3(0, 0, 0.f);
		m_bullet.scale = glm::vec3(0.3f, 0.3f, 0.3f);
		m_bullet.active = false;
		m_bullet.momentOfInertia = m_bullet.mass * pow(m_bullet.scale.x, 2);
		for (int i = 0; i < NUM_AMMO; i++) {
			m_ammo.emplace_back(new GameObject);
			m_ammo[i]->mass = 1;
			m_ammo[i]->pos = glm::vec3(gunCam.position.x, 6.5f, gunCam.position.z);
			m_ammo[i]->dir = glm::vec3(0, 0, 1.f);
			m_ammo[i]->vel = glm::vec3(0, 0, 0.f);
			m_ammo[i]->scale = glm::vec3(0.3f, 0.3f, 0.3f);
			m_ammo[i]->active = false;
			m_ammo[i]->momentOfInertia = m_bullet.mass * pow(m_bullet.scale.x, 2);
		}
		gunHori = 0;
		gunVerti = 0;
		cameraNum = 0;
		ammo = 15;
		score = 0;
		gameTimer = 20;
		reloadTimer = 2;
		bulletType = BULLET_TYPE::BULLET_SINGLE;
		reloading = false;
		totalAmmo = 30;
		currBullet = 0;
		gameOver = false;
}


void SceneHitMen::Update(double dt)
{
	if (elapsedTime + 100 == DBL_MAX)
		elapsedTime = 0;
	if (dt > 0)
		elapsedTime += dt;
	gameOver = gameTimer < 0;
	if (!gameOver) {
		gameTimer -= dt;
		if (reloading && totalAmmo > 0) {
			if (reloadTimer > 0) {
				reloadTimer -= dt;
			}
			else {
				reloading = false;
				reloadTimer = 2;
				int temp = ammo;
				totalAmmo -= NUM_AMMO - temp;
				if (totalAmmo < 0)
					totalAmmo = 0;
				ammo += NUM_AMMO - temp;
			}
		}
		else
			reloading = false;
		glm::vec3 gravity = glm::vec3(0, -1.f, 0.f);
		if (cameraNum == 0) {
			gunCam.Update(static_cast<float>(dt));
		}
		else {
			mainFPSCam.Update(static_cast<float>(dt));
		}
		HandleKeyPress();
		if (reloadTimer > 0) {
			reloadTimer -= dt;
		}
		glm::vec3 view = glm::vec3(gunCam.position - gunCam.target);
		horiView = glm::degrees(atan2(view.x, view.z));
		vertiView = -1 * glm::degrees(atan2(view.y, view.z));
		gunHori = horiView;
		gunVerti = vertiView;
		for (int i = 0; i < NUM_SHELLS; i++) {
			m_grapeShot[i]->fixedUpdate(static_cast<float>(dt));
		}
		;
		for (int i = 0; i < NUM_DOORMEN; i++) {
			doorMen[i]->force.y = -5.f;
			int hitCounter = 0;
			if (doorMen[i]->CheckCCCollision(&m_table1) || doorMen[i]->CheckCCCollision(&m_table2) || doorMen[i]->CheckCCCollision(&m_table3) || doorMen[i]->pos.y < 0.0001f) {
				doorMen[i]->vel.y = 0;
				doorMen[i]->force.y = 0;
			}
			switch (bulletType) {
			case (BULLET_TYPE::BULLET_SHOTGUN):
				for (int j = 0; j < NUM_SHELLS; j++) {
					if (doorMen[i]->CheckCSCollision(m_grapeShot[j]) && doorMen[i]->active) {
						m_grapeShot[j]->CollisionResponse(doorMen[i]);
						m_grapeShot[j]->active = false;
						doorMen[i]->torque = m_bullet.pos - doorMen[i]->pos;
						hitCounter += 1;

					}
				}
				if (hitCounter > 2) {
					doorMen[i]->active = false;
				}
				if (hitCounter > 3) {
					score += 1;
				}
				break;
			case (BULLET_TYPE::BULLET_SINGLE):
				for (int k = 0; k < NUM_AMMO; k++) {
					if (m_ammo[k]->CheckCSCollision(&m_table1) || m_ammo[k]->pos.y < 0.0001f) {
						//m_ammo[k]->CollisionResponse(&m_table1);
						m_ammo[k]->force.y = 0;
						m_ammo[k]->vel.y = 0;
					}
					/*else {
						m_ammo[k]->force += m_ammo[k]->mass / gravity ;
					}*/
					if (doorMen[i]->CheckCSCollision(m_ammo[k]) && doorMen[i]->active) {
						m_ammo[k]->CollisionResponse(doorMen[i]);
						m_ammo[k]->active = false;
						doorMen[i]->active = false;
						doorMen[i]->torque = m_ammo[k]->pos - doorMen[i]->pos;
						score += 1;
					}
					m_ammo[k]->fixedUpdate(static_cast<float>(dt));
				}
				break;
			}
			if (doorMen[i]->active) {
				doorMen[i]->pos.x = sinf(elapsedTime * 1.5f) + doorMenInitPos[i].x;
			}
			for (int k = i; k == NUM_DOORMEN; k++) {
				if (doorMen[k]->CheckCSCollision(doorMen[i])) {
					doorMen[k]->CollisionResponse(doorMen[i]);
				}
			}

			doorMen[i]->fixedUpdate(static_cast<float>(dt));
		}
	}
	else
		{
		if (KeyboardController::GetInstance()->IsKeyPressed('Z')) {
			Player::GetInstance()->coins += score;
			SceneManager::GetInstance()->LoadScene(SceneManager::SCENE_NUM::SCENE_MAIN);
		}
	 }
	 std::cout << doorMen[0]->pos.y << std::endl;
}

void SceneHitMen::Render()
{
	
	// Clear color buffer every frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Load view matrix stack and set it with camera position, target position and up direction
	viewStack.LoadIdentity(); {
		if (cameraNum == 0) {
			viewStack.LookAt(
				gunCam.position.x, gunCam.position.y, gunCam.position.z,
				gunCam.target.x, gunCam.target.y, gunCam.target.z,
				gunCam.up.x, gunCam.up.y, gunCam.up.z
			);
		}
		else if (cameraNum == 1) {
			viewStack.LookAt(
				mainFPSCam.position.x, mainFPSCam.position.y, mainFPSCam.position.z,
				mainFPSCam.target.x, mainFPSCam.target.y, mainFPSCam.target.z,
				mainFPSCam.up.x, mainFPSCam.up.y, mainFPSCam.up.z
			);
		}
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
	for (int i = 0; i < NUM_DOORMEN; i++) {
		
			modelStack.PushMatrix(); {
				modelStack.Translate(doorMen[i]->pos.x, doorMen[i]->pos.y - 1.8f, doorMen[i]->pos.z);
				modelStack.Rotate(glm::degrees(atan2(doorMen[i]->dir.x, doorMen[i]->dir.z)), 0.f, 1.f, 0.f);
				modelStack.Rotate(glm::degrees(atan2(doorMen[i]->dir.y, doorMen[i]->dir.z)), 1.f, 0.f, 0.f);
				modelStack.Scale(0.5f, 0.5f, 0.5f);
				RenderMesh(meshList[GEO_DOORMAN], true);
				
			} modelStack.PopMatrix();
			/*modelStack.PushMatrix(); {
			modelStack.Translate(doorMen[i]->pos.x, doorMen[i]->pos.y, doorMen[i]->pos.z);
			modelStack.Rotate(glm::degrees(atan2(doorMen[i]->dir.x, doorMen[i]->dir.z)), 0.f, 1.f, 0.f);
			modelStack.Rotate(glm::degrees(atan2(doorMen[i]->dir.y, doorMen[i]->dir.z)), 1.f, 0.f, 0.f);
			modelStack.Scale(doorMen[i]->scale.x, doorMen[i]->scale.y, doorMen[i]->scale.z);
			RenderMesh(meshList[GEO_CUBE], true);
			} modelStack.PopMatrix();*/
		
	}
	modelStack.PushMatrix(); {
		modelStack.Scale(1.5f, 1, 1);
		RenderMesh(meshList[GEO_TENT], true);
	} modelStack.PopMatrix();
	modelStack.PushMatrix(); {
		modelStack.Translate(gunCam.position.x, gunCam.position.y, gunCam.position.z);
		modelStack.Rotate(gunVerti, 1.f, 0.f, 0.f);
		modelStack.PushMatrix(); {
			modelStack.Translate(0.f, -0.5f, 0.f);
			modelStack.Rotate(gunHori, 0.f, 1.f, 0.f);
			RenderMesh(meshList[GEO_GUN], true);
		} modelStack.PopMatrix();
	} modelStack.PopMatrix();
	// render tables
	modelStack.PushMatrix(); {
		modelStack.Scale(12.f, 1.f, 1.f);
		modelStack.PushMatrix(); {
			modelStack.Scale(1.f, 5.f, 5.f);
			RenderMesh(meshList[GEO_TABLE], true);
		} modelStack.PopMatrix();
		modelStack.PushMatrix(); {
			modelStack.Translate(0.f, 4.5f, 0.8f);
			modelStack.Scale(1.f, 1.5f, 1.f);
			RenderMesh(meshList[GEO_TABLE], true);
		} modelStack.PopMatrix();
		modelStack.PushMatrix(); {
			modelStack.Translate(0.f, 4.5f, -0.2f);
			modelStack.Scale(1.f, 2.5f, 1.f);
			RenderMesh(meshList[GEO_TABLE], true);
		} modelStack.PopMatrix();
		modelStack.PushMatrix(); {
			modelStack.Translate(0.f, 0.f, 25.f);
			modelStack.Scale(0.5f, 5.f, 5.f);
			RenderMesh(meshList[GEO_TABLE], true);
		} modelStack.PopMatrix();
	}modelStack.PopMatrix();
	if (m_bullet.pos.z < 20) {
		modelStack.PushMatrix(); {
			modelStack.Translate(m_bullet.pos.x, m_bullet.pos.y, m_bullet.pos.z);
			modelStack.Rotate(glm::degrees(atan2(m_bullet.dir.x, m_bullet.dir.z)), 0.f, 1.f, 0.f);
			modelStack.Rotate(glm::degrees(atan2(m_bullet.dir.y, m_bullet.dir.z)), 1.f, 0.f, 0.f);
			modelStack.Scale(m_bullet.scale.x, m_bullet.scale.y, m_bullet.scale.z);
			RenderMesh(meshList[GEO_SPHERE], false);
		} modelStack.PopMatrix();
	}
	for (int i = 0; i < NUM_SHELLS; i++) {

			modelStack.PushMatrix(); {
				modelStack.Translate(m_grapeShot[i]->pos.x, m_grapeShot[i]->pos.y, m_grapeShot[i]->pos.z);
				modelStack.Scale(m_grapeShot[i]->scale.x, m_grapeShot[i]->scale.y, m_grapeShot[i]->scale.z);
				RenderMesh(meshList[GEO_SPHERE], false);
			} modelStack.PopMatrix();
		
	}
	for (int i = 0; i < NUM_AMMO; i++) {

		modelStack.PushMatrix(); {
			modelStack.Translate(m_ammo[i]->pos.x, m_ammo[i]->pos.y, m_ammo[i]->pos.z);
			modelStack.Rotate(glm::degrees(atan2(m_ammo[i]->dir.x, m_ammo[i]->dir.z)), 0.f, 1.f, 0.f);
			modelStack.Rotate(glm::degrees(atan2(m_ammo[i]->dir.y, m_ammo[i]->dir.z)), 1.f, 0.f, 0.f);
			modelStack.Scale(m_ammo[i]->scale.x, m_ammo[i]->scale.y, m_ammo[i]->scale.z);
			RenderMesh(meshList[GEO_SPHERE], false);
		} modelStack.PopMatrix();

	}
	RenderSkybox();
	RenderTextOnScreen(meshList[GEO_TEXT], std::string("Score: " + std::to_string(score)), Color(255.f / 255.f, 165 / 255.f, 0.f ), 40, 0, 550);
	RenderTextOnScreen(meshList[GEO_TEXT], std::string("Time: " + std::to_string(gameTimer)), Color(255.f / 255.f, 165 / 255.f, 0.f), 40, 400, 550);
	if (reloading)
		RenderTextOnScreen(meshList[GEO_TEXT], std::string("Reloading: " + std::to_string(reloadTimer)), Color(255.f / 255.f, 165 / 255.f, 0.f), 40, 250, 30);
	else{
		if (totalAmmo > 0 || ammo > 0) {
			if (ammo < 0) {
				ammo = 0;
			}
			RenderTextOnScreen(meshList[GEO_TEXT], std::string("Ammo:" + std::to_string(ammo) + "/" + std::to_string(totalAmmo)), Color(255.f / 255.f, 165 / 255.f, 0.f), 40, 400, 30);
		}
		else
			RenderTextOnScreen(meshList[GEO_TEXT], "No ammo!", Color(0.f, 0.f, 0.f), 40, 400, 30);
	}
	std::string shotGunString;
	std::string singleString;
	if (bulletType == BULLET_TYPE::BULLET_SINGLE) {
		singleString = "> SingleShot";
		shotGunString = "BuckShot";
	}
	else
	{
		singleString = "SingleShot";
		shotGunString = "> BuckShot";
	}
	RenderTextOnScreen(meshList[GEO_TEXT], singleString, Color(255.f / 255.f, 165 / 255.f, 0.f), 20, 550, 400);
	RenderTextOnScreen(meshList[GEO_TEXT], shotGunString, Color(255.f / 255.f, 165 / 255.f, 0.f), 20, 550, 360);
	if (gameOver) {
		RenderTextOnScreen(meshList[GEO_TEXT], "Time's up, game over!", Color(1.f, 0.f, 0.f), 40, 0, 300);
		RenderTextOnScreen(meshList[GEO_TEXT], "Press Z to exit", Color(1.f, 0.f, 0.f), 40, 0, 240);
	}
}


void SceneHitMen::RenderMesh(Mesh* mesh, bool enableLight)
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

void SceneHitMen::RenderMeshOnScreen(Mesh* mesh, float x, float y, float sizex, float sizey)
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

void SceneHitMen::RenderText(Mesh* mesh, std::string text, Color color)
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

void SceneHitMen::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
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
void SceneHitMen::RenderSkybox()
{
	modelStack.PushMatrix();
	{
		modelStack.Translate(0.f, 0.f, -50.f);
		modelStack.Rotate(180, 0.f, 0.f, 1.f);
		modelStack.Scale(1, 1.f, 1);
		meshList[GEO_FRONT]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
		meshList[GEO_FRONT]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_FRONT]->material.kSpecular.Set(0.9f, 0.9f, 0.9f);
		RenderMesh(meshList[GEO_FRONT], false);
	}
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	{
		modelStack.Translate(0.f, 0.f, 50.f);
		modelStack.Rotate(180, 0.f, 1.f, 0.f);
		modelStack.Rotate(180, 0.f, 0.f, 1.f);
		modelStack.Scale(1, 1.f, 1);
		meshList[GEO_BACK]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
		meshList[GEO_BACK]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_BACK]->material.kSpecular.Set(0.9f, 0.9f, 0.9f);
		RenderMesh(meshList[GEO_BACK], false);
	}
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	{
		modelStack.Translate(-50.f, 0.f, 0.f);
		modelStack.Rotate(90, 0.f, 1.f, 0.f);
		modelStack.Rotate(180, 0.f, 0.f, 1.f);
		modelStack.Scale(1, 1.f, 1);
		meshList[GEO_RIGHT]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
		meshList[GEO_RIGHT]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_RIGHT]->material.kSpecular.Set(0.9f, 0.9f, 0.9f);
		RenderMesh(meshList[GEO_RIGHT], false);
	}
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	{
		modelStack.Translate(50.f, 0.f, 0.f);
		modelStack.Rotate(90, 0.f, -1.f, 0.f);
		modelStack.Rotate(180, 0.f, 0.f, 1.f);
		modelStack.Scale(1, 1.f, 1);
		meshList[GEO_LEFT]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
		meshList[GEO_LEFT]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_LEFT]->material.kSpecular.Set(0.9f, 0.9f, 0.9f);
		RenderMesh(meshList[GEO_LEFT], false);
	}
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	{
		modelStack.Rotate(90, -1.f, 0.f, 0.f);
		modelStack.Rotate(180, 0.f, 0.f, 1.f);
		meshList[GEO_BOTTOM]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
		meshList[GEO_BOTTOM]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_BOTTOM]->material.kSpecular.Set(0.9f, 0.9f, 0.9f);
		RenderMesh(meshList[GEO_BOTTOM], false);
	}
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	{
		modelStack.Translate(0.f, 50.f, 0.f);
		modelStack.Rotate(90, 1.f, 0.f, 0.f);
		modelStack.Rotate(180, 0.f, 0.f, 1.f);

		meshList[GEO_TOP]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
		meshList[GEO_TOP]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_TOP]->material.kSpecular.Set(0.9f, 0.9f, 0.9f);
		RenderMesh(meshList[GEO_TOP], false);
	}
	modelStack.PopMatrix();
}

void SceneHitMen::RenderLight(int lightIndex)
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

void SceneHitMen::Exit()
{
	// Cleanup VBO here
	for (int i = 0; i < NUM_GEOMETRY; ++i)
	{
		if (meshList[i])
		{
			delete meshList[i];
		}
	}
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}

void SceneHitMen::HandleKeyPress()
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
		if (cameraNum == 0) {
			cameraNum = 1;
		}
		else
			cameraNum = 0;
	}
	switch (bulletType) {
	case BULLET_TYPE::BULLET_SINGLE:
		if (KeyboardController::GetInstance()->IsKeyPressed(0x20) && ammo > 0 && !reloading) {
			/*m_bullet.active = true;
			m_bullet.vel = glm::vec3(0, 0, 0);
			m_bullet.pos = gunCam.position;
			glm::vec3 view = glm::normalize(glm::vec3(gunCam.position - gunCam.target));
			m_bullet.dir = view;
			m_bullet.vel = m_bullet.dir * -100.f;*/
			m_ammo[currBullet]->active = true;
			m_ammo[currBullet]->vel = glm::vec3(0, 0, 0);
			m_ammo[currBullet]->pos = gunCam.position;
			glm::vec3 view = glm::normalize(glm::vec3(gunCam.position - gunCam.target));
			m_ammo[currBullet]->dir = view;
			m_ammo[currBullet]->vel = m_ammo[currBullet]->dir * -10.f;
			ammo -= 1;
			currBullet++;
		}
		break;
	case BULLET_TYPE::BULLET_SHOTGUN:
		if (KeyboardController::GetInstance()->IsKeyPressed(0x20) && ammo > 2 && !reloading) {
			glm::vec3 view = glm::normalize(glm::vec3(gunCam.position - gunCam.target));
			for (int i = 0; i < NUM_SHELLS; i++) {
				m_grapeShot[i]->pos = gunCam.position;
				m_grapeShot[i]->dir = view;
				m_grapeShot[i]->dir.y += ((rand() % 5) - 1.5f) * ((rand() % 4) * 0.01f);
				m_grapeShot[i]->dir.x += ((rand() % 3) - 1.5f) * ((rand() % 4) * 0.01f);
				m_grapeShot[i]->dir = glm::normalize(m_grapeShot[i]->dir);
				m_grapeShot[i]->vel = m_grapeShot[i]->dir * -50.f;
			}
			ammo -= 5;
		}
		break;
	}
	if (KeyboardController::GetInstance()->IsKeyPressed(GLFW_KEY_LEFT_CONTROL)) {
		switch (bulletType) {
		case (BULLET_TYPE::BULLET_SINGLE):
			bulletType = BULLET_TYPE::BULLET_SHOTGUN;
			break;
		case (BULLET_TYPE::BULLET_SHOTGUN):
			bulletType = BULLET_TYPE::BULLET_SINGLE;
			break;
		}
	}
	if (KeyboardController::GetInstance()->IsKeyPressed('R') && totalAmmo > 0) {
		reloading = true;
		reloadTimer = 2;
		currBullet = 0;
	}
}
