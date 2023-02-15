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
		initCamY = 5;
		// Initialise camera properties
		mainFPSCam.Init(glm::vec3(21, initCamY, 0.f), glm::vec3(0, initCamY, 0), glm::vec3(0.f, initCamY, 0.f));
		zakuCam.Init(glm::vec3(0, initCamY, 15.f), glm::vec3(0, initCamY, 0), glm::vec3(0.f, 1, 0.f), false);
		cameraArray.push_back(mainFPSCam);
		cameraArray.push_back(zakuCam);
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
				doorMen[counter]->pos = (glm::vec3(- 1 * j * 3.f + offSet, 5.f + offSet, -1 * i * 1.f));
				doorMenInitPos.emplace_back(doorMen[counter]->pos);
				doorMen[counter]->scale = glm::vec3(0.5f, 0.5f, 0.5f);
				doorMen[counter]->vel = glm::vec3(0, 0, 0);
				doorMen[counter]->force = glm::vec3(0, 0, 0);
				counter += 1;
			}
			offSet += 1;
		}
		m_table.pos = glm::vec3(0, 0, 0);
		m_table.scale = glm::vec3(5, 5, 5);
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
		
		m_player.pos = glm::vec3(0, 0, 0);

		cameraNum = 1;
}


void SceneHitMen::Update(double dt)
{
	if (elapsedTime + 100 == DBL_MAX)
		elapsedTime = 0;
	elapsedTime += dt;
	glm::vec3 gravity = glm::vec3(0, -5.f, 0.f);
	for (int i = 0; i < NUM_DOORMEN; i++) {
		//if (doorMen[i]->vel.y < 10)
			//doorMen[i]->vel += gravity;
		doorMen[i]->pos.x =  5.f * sin(elapsedTime * 1.5f) + doorMenInitPos[i].x;
		doorMen[i]->fixedUpdate(dt);
	}
	HandleKeyPress();


	// spotlight for zaku cleaner view
	//light[0].position = glm::vec3(cameraArray[1].position.x, cameraArray[1].position.y, cameraArray[1].position.z);
	//light[0].spotDirection = glm::normalize(cameraArray[1].position - cameraArray[1].target);
	cameraArray[cameraNum].Update(dt);
}

void SceneHitMen::Render()
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
	for (int i = 0; i < NUM_DOORMEN; i++) {
		modelStack.PushMatrix(); {
			modelStack.Translate(doorMen[i]->pos.x, doorMen[i]->pos.y, doorMen[i]->pos.z);
			modelStack.Scale(doorMen[i]->scale.x, doorMen[i]->scale.y, doorMen[i]->scale.z);
			RenderMesh(meshList[GEO_DOORMAN], false);
		} modelStack.PopMatrix();
	}
	modelStack.PushMatrix(); {
		modelStack.Scale(5.f, 5.f, 5.f);
		RenderMesh(meshList[GEO_TABLE], false);
	} modelStack.PopMatrix();
	modelStack.PushMatrix(); {
		modelStack.Translate(0.f, 4.5f, 0.8f);
		modelStack.Scale(5.f, 1.5f, 1.f);
		RenderMesh(meshList[GEO_TABLE], false);
	} modelStack.PopMatrix();
	modelStack.PushMatrix(); {
		modelStack.Translate(0.f, 4.5f, -0.2f);
		modelStack.Scale(5.f, 2.5f, 1.f);
		RenderMesh(meshList[GEO_TABLE], false);
	} modelStack.PopMatrix();
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
/*
void SceneHitMen::RenderZaku()
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
*/
void SceneHitMen::RenderSkybox()
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
		std::cout << i << std::endl;
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
		else if (cameraNum == 1)
			cameraNum = 2;
		else
			cameraNum = 0;
	}
	
}
