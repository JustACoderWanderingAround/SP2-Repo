#include "SceneCanTopple.h"
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

SceneCanTopple::SceneCanTopple()
{
	srand(rand());
	srand(rand() % rand());
	srand(rand() % rand() % rand());
}

SceneCanTopple::~SceneCanTopple()
{
	/*for (std::vector<GameObject*>::iterator iter = interactables.begin(); iter != interactables.end(); iter++) {
		if (!(*iter == nullptr)) {
			delete* iter;
		}
	}*/
}

void SceneCanTopple::Init()
{
	srand(rand());
	srand(rand() % rand());
	srand(rand() % rand() % rand());
	srand(rand() % rand() % rand() % rand() % rand());

	float temp2;
	int score = 0;
	gameActive = true;
	timer = 30;
	
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
		camera.Init(glm::vec3(0, 10, 11), glm::vec3(0, 0, 0), glm::vec3(0.f, 1, 0.f));

		// Init VBO here
		for (int i = 0; i < NUM_GEOMETRY; ++i)
		{
			meshList[i] = nullptr;
		}

		// meshList
		{
			meshList[GEO_AXES] = MeshBuilder::GenerateAxes("Axes", 10000.f, 10000.f, 10000.f);
			meshList[GEO_SPHERE] = MeshBuilder::GenerateSphere("Sun", Color(1.f, 1.f, 1.f), 1.f, 16, 16);
			meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("Plane", Color(1.f, 1.f, 1.f), 100.f);
			meshList[GEO_LEFT]->textureID = LoadTGA("Image//skyboxleft.tga");

			meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
			meshList[GEO_TEXT]->textureID = LoadTGA("Image//OpaqueComicSans.tga");

			meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("Plane", Color(1.f, 1.f, 1.f), 100.f);
			meshList[GEO_RIGHT]->textureID = LoadTGA("Image//skyboxright.tga");

			meshList[GEO_TOP] = MeshBuilder::GenerateQuad("Plane", Color(1.f, 1.f, 1.f), 100.f);
			meshList[GEO_TOP]->textureID = LoadTGA("Image//skyboxtop.tga");

			meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("Plane", Color(1.f, 1.f, 1.f), 100.f);
			meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//skyboxbottom.tga");

			meshList[GEO_BACK] = MeshBuilder::GenerateQuad("Plane", Color(1.f, 1.f, 1.f), 100.f);
			meshList[GEO_BACK]->textureID = LoadTGA("Image//skyboxback.tga");

			meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("Plane", Color(1.f, 1.f, 1.f), 100.f);
			meshList[GEO_FRONT]->textureID = LoadTGA("Image//skyboxfront.tga");
			meshList[GEO_FLOOR] = MeshBuilder::GenerateCube("Floor", Color(0, 0.5f, 0), 1.f);

			meshList[GEO_CANCOLLIDER] = MeshBuilder::GenerateCube("Floor", Color(1, 0.5F, 0.5F), 1.f);


			meshList[GEO_BALL] = MeshBuilder::GenerateSphere("Sun", Color(1.f, 1.f, 1.f), 1.f, 16, 16);
			meshList[GEO_TABLECOLLIDEBOX] = MeshBuilder::GenerateCube("TableCollideBox", Color(1.f, 1.f, 1.f), 1.f);

			// 16 x 16 is the number of columns and rows for the text
			//meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
			//eshList[GEO_TEXT]->textureID = LoadTGA("Image//ArialNarrow.tga");

			meshList[GEO_BALLER] = MeshBuilder::GenerateOBJ("Baller", "OBJ//baller.obj");
			meshList[GEO_BALLER]->textureID = LoadTGA("Image//baller.tga");

			meshList[GEO_BARREL] = MeshBuilder::GenerateOBJ("Baller", "OBJ//barrel.obj");
			meshList[GEO_BARREL]->textureID = LoadTGA("Image//barrel.tga");

			meshList[GEO_TENT] = MeshBuilder::GenerateOBJ("tent", "OBJ//tent.obj");
			meshList[GEO_TENT]->textureID = LoadTGA("Image//bluetent.tga");

			meshList[GEO_SODACAN] = MeshBuilder::GenerateOBJ("SodaCan", "OBJ//sodacan.obj");
			meshList[GEO_SODACAN]->textureID = LoadTGA("Image/sodacan.tga");

			meshList[GEO_TABLE] = MeshBuilder::GenerateOBJ("Table", "OBJ//table.obj");
			meshList[GEO_TABLE]->textureID = LoadTGA("Image//table.tga");
		};

		glm::mat4 projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 1000.0f);
		projectionStack.LoadMatrix(projection);

		int ballerX = 2, ballerY = 0, ballerZ = 8;

		m_ball = new GameObject(GameObject::GO_BALL);
		// Ball Value initialisation
		m_ball->pos = camera.position;
		m_ball->scale = glm::vec3(0.5f, 0.5f, 0.5f);
		m_ball->vel = glm::vec3(0.f, 0.f, 0.f);
		m_ball->force = glm::vec3(0.f, 0.f, 0.f);
		m_ball->active = false;
		m_ball->mass = 2;

		m_table = new GameObject(GameObject::GO_TABLE);
		// position set to (half width and 10% of the screen height
		m_table->pos = glm::vec3(0, 5.6f, -10);
		m_table->scale = glm::vec3(12.5f, 1, 10.f);
		m_table->vel = glm::vec3(0.f, 0.f, 0.f);
		m_table->force = glm::vec3(0.f, 0.f, 0.f);
		m_table->active = false;
		m_table->mass = 10;

		m_floor = new GameObject(GameObject::GO_FLOOR);
		// position set to (half width and 10% of the screen height
		m_floor->pos = glm::vec3(0, -1.f, 0);
		m_floor->scale = glm::vec3(50, 1.f, 50);
		m_floor->vel = glm::vec3(0.f, 0.f, 0.f);
		m_floor->force = glm::vec3(0.f, 0.f, 0.f);
		m_floor->active = false;
		m_floor->mass = 50.f;


		CreateCanStack(0, -10, 0);
		CreateCanStack(-3, -7, 1);
		CreateCanStack(3, -7, 2);



		glUniform1i(m_parameters[U_NUMLIGHTS], NUM_LIGHTS);
		// light params
		{
			//light that follows primary zakuCam
			//light[0].position = glm::vec3(0, 25, -10);
			//light[0].color.Set(1, 1, 1);
			//light[0].type = Light::LIGHT_SPOT;
			////light[0].power = 5.f;
			//light[0].kC = 1.f;
			//light[0].kL = 0.01f;
			//light[0].kQ = 0.001f;
			//light[0].cosCutoff = 5.f;
			//light[0].cosInner = 1.f;
			//light[0].exponent = 3.f;



			 //main Hangar light 
			light[1].position = glm::vec3(0, 15, -10);
			light[1].type = Light::LIGHT_SPOT;
			//light[1].color.Set(1, 1, 1);
			light[1].color.Set(247 / 255.f, 181 / 255.f, 0);
			light[1].spotDirection = glm::normalize(light[1].position - glm::vec3(0, 0, 0));
			light[1].power = 1.f;
			light[1].kC = 1.f;
			light[1].kL = 0.01f;
			light[1].kQ = 0.001f;
			light[1].cosCutoff = 45.f;
			light[1].cosInner = 30.f;
			light[1].exponent = 3.f;

			// room light 1
			light[2].position = glm::vec3(15, 20.f, 0);
			light[2].power = 1.f;
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
		
		cameraNum = 0;
		doorOpen = false;
		boosting = false;
}


void SceneCanTopple::Update(double dt)
{
	HandleKeyPress();

	if (timer <= 0)
	{
		gameActive = false;
	}

	if (gameActive == true)
	{
		timer -= dt;
		if (KeyboardController::GetInstance()->IsKeyDown('V'))
		{
			poweringUp = true;
		}

		if (poweringUp == true)
		{
			if (throwingPower < 60)
			{
				throwingPower += dt * 50;
			}
			if (KeyboardController::GetInstance()->IsKeyUp('V'))
			{
				m_ball->vel = glm::vec3(0, 0, 0);
				m_ball->pos = camera.position;
				m_ball->dir = glm::normalize(camera.position - camera.target);
				//m_ball->force.x = camera.target.x;
				//m_ball->force.y = camera.target.y;
				//m_ball->force.z = camera.target.z;
				m_ball->vel = -(m_ball->dir * glm::vec3(throwingPower, throwingPower, throwingPower) / m_ball->mass);

				poweringUp = false;
				m_ball->active = true;
				throwingPower = 0;
			}
		}



		//m_ball->dir = glm::normalize(camera.position - camera.target);


			m_ball->vel.y -= 0.1f;

			if (m_table->CheckCSCollision(m_ball))
			{
				m_ball->CollisionResponse(m_table);

			}

			if (m_floor->CheckCSCollision(m_ball))
			{
				//m_ball->vel.x = (m_ball->vel.x / 1.5) * -1;
				m_ball->CollisionResponse(m_floor);
				//m_ball->vel.z = (m_ball->vel.z / 1.5) * -1;

			}


			m_ball->fixedUpdate(static_cast<float>(dt));

			for (int i = 0; i < MAX_CANS; i++)
			{
				m_can[i]->fixedUpdate(static_cast<float>(dt));
				if (m_can[i]->touched == true)
				{
					m_can[i]->vel.y -= 0.1f;
				}

				if (m_can[i]->CheckCCCollision(m_table))
				{
					m_can[i]->vel.y = 0;
					m_can[i]->collidingWithTable = true;
				}

				if (m_can[i]->CheckCCCollision(m_floor))
				{
					m_can[i]->vel.y = 0.4f;
				}

				if (m_can[i]->CheckCSCollision(m_ball))
				{
					m_can[i]->CollisionResponse(m_ball);
					if (m_can[i]->touched == true)
					{

					}
					else
					{
						m_can[i]->touched = true;
						score += 1;
					}
					//std::cout << "Hi";
				}



			}
		}


		std::cout << camera.target.x << "," << camera.target.y << "," << camera.target.z << std::endl;
		//std::cout << "Pos: " << cameraArray[0].position.x << ", " << cameraArray[0].position.y << ", " << cameraArray[0].position.z << std::endl;

		// spotlight for zaku cleaner view
		light[0].position = glm::vec3(camera.position.x, camera.position.y, camera.position.z);
		light[0].spotDirection = glm::normalize(camera.position - camera.target);
		camera.Update(dt);
	
}

void SceneCanTopple::Render()
{
	if (gameActive == true)
	{
		// Clear color buffer every frame
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Load view matrix stack and set it with camera position, target position and up direction
		viewStack.LoadIdentity(); {
			viewStack.LookAt(
				camera.position.x, camera.position.y, camera.position.z,
				camera.target.x, camera.target.y, camera.target.z,
				camera.up.x, camera.up.y, camera.up.z
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
				//RenderMesh(meshList[GEO_SPHERE], false);
			} modelStack.PopMatrix();
		}
		modelStack.PushMatrix(); {
			RenderMesh(meshList[GEO_AXES], false);
		} modelStack.PopMatrix();

		modelStack.PushMatrix();
		// Render Sun



		modelStack.PushMatrix(); // Render light visualiser
		modelStack.Translate(light[1].position.x, light[1].position.y, light[1].position.z);
		RenderMesh(meshList[GEO_SPHERE], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix(); // Render floor
		modelStack.Scale(50, 0.2f, 50);
		modelStack.Translate(0, -0.2f, 0);
		meshList[GEO_FLOOR]->material.kAmbient.Set(0.5f, 0.5, 0.5f);
		meshList[GEO_FLOOR]->material.kDiffuse.Set(0.7f, 0.7f, 0.7f);
		meshList[GEO_FLOOR]->material.kSpecular.Set(0.9f, 0.9f, 0.9f);
		meshList[GEO_FLOOR]->material.kShininess = 2.5f;
		RenderMesh(meshList[GEO_FLOOR], true);
		modelStack.PopMatrix();

		if (m_ball->active == true)
		{
			modelStack.PushMatrix();
			modelStack.Translate(m_ball->pos.x, m_ball->pos.y, m_ball->pos.z);
			modelStack.Scale(m_ball->scale.x, m_ball->scale.y, m_ball->scale.z);
			meshList[GEO_BALL]->material.kAmbient.Set(0.5f, 0.5, 0.5f);
			meshList[GEO_BALL]->material.kDiffuse.Set(0.7f, 0.7f, 0.7f);
			meshList[GEO_BALL]->material.kSpecular.Set(0.9f, 0.9f, 0.9f);
			meshList[GEO_BALL]->material.kShininess = 2.5f;
			RenderMesh(meshList[GEO_BALL], true);
			modelStack.PopMatrix();
		}

		modelStack.PushMatrix();  // Render Player / Steve
		modelStack.Translate(-1.5f, 0, -10);
		modelStack.Scale(0.5f, 0.5f, 0.5f);
		modelStack.Rotate(0, 0, 1, 0);
		meshList[GEO_TABLE]->material.kAmbient.Set(0.3f, 0.3f, 0.3f);
		meshList[GEO_TABLE]->material.kDiffuse.Set(0.7f, 0.7f, 0.7f);
		meshList[GEO_TABLE]->material.kSpecular.Set(0.9f, 0.9f, 0.9f);
		meshList[GEO_TABLE]->material.kShininess = 5.0f;
		RenderMesh(meshList[GEO_TABLE], true);
		modelStack.PopMatrix();

		/*modelStack.PushMatrix();
		modelStack.Translate(m_table->pos.x, m_table->pos.y, m_table->pos.z);
		modelStack.Scale(m_table->scale.x, m_table->scale.y, m_table->scale.z);
		RenderMesh(meshList[GEO_TABLECOLLIDEBOX], true);
		modelStack.PopMatrix();*/

		modelStack.PushMatrix();  // Render Player / Steve
		modelStack.Translate(0, 0, -10);
		modelStack.Scale(1, 1, 1);
		modelStack.Rotate(0, 0, 1, 0);
		meshList[GEO_TENT]->material.kAmbient.Set(0.3f, 0.3f, 0.3f);
		meshList[GEO_TENT]->material.kDiffuse.Set(0.7f, 0.7f, 0.7f);
		meshList[GEO_TENT]->material.kSpecular.Set(0.9f, 0.9f, 0.9f);
		meshList[GEO_TENT]->material.kShininess = 5.0f;
		RenderMesh(meshList[GEO_TENT], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();  // Render Player / Steve
		modelStack.Translate(2, 0, 8);
		modelStack.Scale(1.5, 1.5, 1.5);
		modelStack.Rotate(180, 0, 1, 0);
		meshList[GEO_BALLER]->material.kAmbient.Set(0.3f, 0.3f, 0.3f);
		meshList[GEO_BALLER]->material.kDiffuse.Set(0.7f, 0.7f, 0.7f);
		meshList[GEO_BALLER]->material.kSpecular.Set(0.9f, 0.9f, 0.9f);
		meshList[GEO_BALLER]->material.kShininess = 5.0f;
		RenderMesh(meshList[GEO_BALLER], true);
		modelStack.PopMatrix();

		RenderCanStack();

		RenderBarrels(-12, -20);
		RenderBarrels(-15, -20);
		RenderBarrels(-15, -16);
		RenderBarrels(-15, -5);

		RenderSkybox();

		std::string temp2("Power:" + std::to_string(throwingPower)); // loading in current time
		RenderTextOnScreen(meshList[GEO_TEXT], temp2.substr(0, 8), Color(1, 1, 0), 40, 0, 40);

		std::string temp3("Timer:" + std::to_string(timer)); // loading in current time
		RenderTextOnScreen(meshList[GEO_TEXT], temp3.substr(0, 8), Color(1, 1, 0), 40, 0, 560);

		std::string temp4("Score:" + std::to_string(score)); // loading in current time
		RenderTextOnScreen(meshList[GEO_TEXT], temp4.substr(0, 8), Color(1, 1, 0), 40, 0, 0);
	}
	else
	{
	std::string temp5("Time's up!"); // loading in current time
	RenderTextOnScreen(meshList[GEO_TEXT], temp5.substr(0, 10), Color(1, 1, 0), 40, 0, 280);
	}
}


void SceneCanTopple::RenderMesh(Mesh* mesh, bool enableLight)
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

void SceneCanTopple::RenderMeshOnScreen(Mesh* mesh, float x, float y, float sizex, float sizey)
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

void SceneCanTopple::RenderText(Mesh* mesh, std::string text, Color color)
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

void SceneCanTopple::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
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

void SceneCanTopple::RenderSkybox()
{
	modelStack.PushMatrix();
	{
		modelStack.Translate(0.f, 0.f, -50.f);
		modelStack.Rotate(180, 0.f, 0.f, 1.f);
		modelStack.Scale(1, 0.5, 1);
		meshList[GEO_FRONT]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
		meshList[GEO_FRONT]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_FRONT]->material.kSpecular.Set(0.9f, 0.9f, 0.9f);
		RenderMesh(meshList[GEO_FRONT], enableLight);
	}
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	{
		modelStack.Translate(0.f, 0.f, 50.f);
		modelStack.Rotate(180, 0.f, 1.f, 0.f);
		modelStack.Rotate(180, 0.f, 0.f, 1.f);
		modelStack.Scale(1, 0.5, 1);
		meshList[GEO_BACK]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
		meshList[GEO_BACK]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_BACK]->material.kSpecular.Set(0.9f, 0.9f, 0.9f);
		RenderMesh(meshList[GEO_BACK], enableLight);
	}
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	{
		modelStack.Translate(-50.f, 0.f, 0.f);
		modelStack.Rotate(90, 0.f, 1.f, 0.f);
		modelStack.Rotate(180, 0.f, 0.f, 1.f);
		modelStack.Scale(1, 0.5, 1);
		meshList[GEO_RIGHT]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
		meshList[GEO_RIGHT]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_RIGHT]->material.kSpecular.Set(0.9f, 0.9f, 0.9f);
		RenderMesh(meshList[GEO_RIGHT], enableLight);
	}
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	{
		modelStack.Translate(50.f, 0.f, 0.f);
		modelStack.Rotate(90, 0.f, -1.f, 0.f);
		modelStack.Rotate(180, 0.f, 0.f, 1.f);
		modelStack.Scale(1, 0.5, 1);
		meshList[GEO_LEFT]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
		meshList[GEO_LEFT]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_LEFT]->material.kSpecular.Set(0.9f, 0.9f, 0.9f);
		RenderMesh(meshList[GEO_LEFT], enableLight);
	}
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	{
		modelStack.Translate(0.f, -10.f, 0.f);
		modelStack.Rotate(90, -1.f, 0.f, 0.f);
		modelStack.Rotate(180, 0.f, 0.f, 1.f);
		meshList[GEO_BOTTOM]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
		meshList[GEO_BOTTOM]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_BOTTOM]->material.kSpecular.Set(0.9f, 0.9f, 0.9f);
		RenderMesh(meshList[GEO_BOTTOM], enableLight);
	}
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	{
		modelStack.Translate(0.f, 22.f, 0.f);
		modelStack.Rotate(90, 1.f, 0.f, 0.f);
		modelStack.Rotate(180, 0.f, 0.f, 1.f);

		meshList[GEO_TOP]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
		meshList[GEO_TOP]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_TOP]->material.kSpecular.Set(0.9f, 0.9f, 0.9f);
		RenderMesh(meshList[GEO_TOP], enableLight);
	}
	modelStack.PopMatrix();
}

void SceneCanTopple::RenderLight(int lightIndex)
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

void SceneCanTopple::Exit()
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

void SceneCanTopple::HandleKeyPress()
{
	if (KeyboardController::GetInstance()->IsKeyPressed('I'))
	{
		camera.position.y += 0.5f;
		camera.target.y += 0.5f;

	}
	if (KeyboardController::GetInstance()->IsKeyPressed('J'))
	{
		m_ball->pos.x -= 0.5f;
	}
	if (KeyboardController::GetInstance()->IsKeyPressed('K'))
	{
		camera.position.y -= 0.5f;
		camera.target.y -= 0.5f;
	}
	if (KeyboardController::GetInstance()->IsKeyPressed('L'))
	{
		camera.position.x += 0.5f;
	}

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
	//if (KeyboardController::GetInstance()->IsKeyPressed(GLFW_KEY_TAB)) {
	//	gameActive = true;

	//	m_ball->vel = glm::vec3(0, 0, 0);
	//	m_ball->pos = camera.position;
	//	m_ball->dir = glm::normalize(camera.position - camera.target);
	//	//m_ball->force.x = camera.target.x;
	//	//m_ball->force.y = camera.target.y;
	//	//m_ball->force.z = camera.target.z;
	//	m_ball->vel = -(m_ball->dir * 25.f);

	//	m_ball->active = true;
	//}
	
}

void SceneCanTopple::RenderCanStack()
{
	for (int i = 0; i < MAX_CANS; i++)
	{
		if (m_can[i]->active == true)
		{
			modelStack.PushMatrix();  // Render Player / Steve
			modelStack.Translate(m_can[i]->pos.x, m_can[i]->pos.y - 0.7f, m_can[i]->pos.z);
			modelStack.Scale(m_can[i]->scale.x, 1, m_can[i]->scale.z);
			modelStack.Rotate(0, 0, 1, 0);
			meshList[GEO_SODACAN]->material.kAmbient.Set(0.3f, 0.3f, 0.3f);
			meshList[GEO_SODACAN]->material.kDiffuse.Set(0.7f, 0.7f, 0.7f);
			meshList[GEO_SODACAN]->material.kSpecular.Set(0.9f, 0.9f, 0.9f);
			meshList[GEO_SODACAN]->material.kShininess = 5.0f;
			RenderMesh(meshList[GEO_SODACAN], true);
			modelStack.PopMatrix();
		}

		//modelStack.PushMatrix();  // Render Player / Steve
		//modelStack.Translate(m_can[i]->pos.x, m_can[i]->pos.y, m_can[i]->pos.z);
		//modelStack.Scale(m_can[i]->scale.x, m_can[i]->scale.y, m_can[i]->scale.z);
		//modelStack.Rotate(0, 0, 1, 0);
		//meshList[GEO_CANCOLLIDER]->material.kAmbient.Set(0.3f, 0.3f, 0.3f);
		//meshList[GEO_CANCOLLIDER]->material.kDiffuse.Set(0.7f, 0.7f, 0.7f);
		//meshList[GEO_CANCOLLIDER]->material.kSpecular.Set(0.9f, 0.9f, 0.9f);
		//meshList[GEO_CANCOLLIDER]->material.kShininess = 5.0f;
		//RenderMesh(meshList[GEO_CANCOLLIDER], true);
		//modelStack.PopMatrix();
	}
	
}

void SceneCanTopple::RenderBarrels(int barrelStartingX, int barrelStartingZ)
{
	modelStack.PushMatrix();  // Render Player / Steve
	modelStack.Translate(barrelStartingX, 0, barrelStartingZ);
	modelStack.Scale(1, 1, 1);
	modelStack.Rotate(0, 0, 1, 0);
	meshList[GEO_BARREL]->material.kAmbient.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_BARREL]->material.kDiffuse.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_BARREL]->material.kSpecular.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_BARREL]->material.kShininess = 5.0f;
	RenderMesh(meshList[GEO_BARREL], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();  // Render Player / Steve
	modelStack.Translate(barrelStartingX - 2, 0, barrelStartingZ - 4);
	modelStack.Scale(1, 1, 1);
	modelStack.Rotate(0, 0, 1, 0);
	meshList[GEO_BARREL]->material.kAmbient.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_BARREL]->material.kDiffuse.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_BARREL]->material.kSpecular.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_BARREL]->material.kShininess = 5.0f;
	RenderMesh(meshList[GEO_BARREL], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();  // Render Player / Steve
	modelStack.Translate(barrelStartingX + 2, 0, barrelStartingZ - 4);
	modelStack.Scale(1, 1, 1);
	modelStack.Rotate(0, 0, 1, 0);
	meshList[GEO_BARREL]->material.kAmbient.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_BARREL]->material.kDiffuse.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_BARREL]->material.kSpecular.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_BARREL]->material.kShininess = 5.0f;
	RenderMesh(meshList[GEO_BARREL], true);
	modelStack.PopMatrix();

	//modelStack.PushMatrix();  // Render Player / Steve
	//modelStack.Translate(barrelStartingX, 6, barrelStartingZ - 2);
	//modelStack.Scale(0.5f, 0.5f, 0.5f);
	//modelStack.Rotate(0, 0, 1, 0);
	//meshList[GEO_BARREL]->material.kAmbient.Set(0.3f, 0.3f, 0.3f);
	//meshList[GEO_BARREL]->material.kDiffuse.Set(0.7f, 0.7f, 0.7f);
	//meshList[GEO_BARREL]->material.kSpecular.Set(0.9f, 0.9f, 0.9f);
	//meshList[GEO_BARREL]->material.kShininess = 5.0f;
	//RenderMesh(meshList[GEO_BARREL], true);
	//modelStack.PopMatrix();
}

void SceneCanTopple::CreateCanStack(int canStartingX, int canStartingZ, int stackIdx)
{
	for (int i = 0; i < 5; i++)
	{
		m_can[stackIdx * 12 + i] = new GameObject(GameObject::GO_CAN);
		m_can[stackIdx * 12 + i]->pos = glm::vec3(canStartingX + (i * 1.2f) - 2.f, 6.6f ,canStartingZ);
		m_can[stackIdx * 12 + i]->scale = glm::vec3(1.f, 1.5f, 1);
		m_can[stackIdx * 12 + i]->vel = glm::vec3(0.f, 0.f, 0.f);
		m_can[stackIdx * 12 + i]->force = glm::vec3(0.f, 0.f, 0.f);
		m_can[stackIdx * 12 + i]->active = true;
		m_can[stackIdx * 12 + i]->collidingWithTable = false;
		m_can[stackIdx * 12 + i]->collidingWithTable = false;
		m_can[stackIdx * 12 + i]->mass = 3;
	}
	for (int i = 0; i < 4; i++)
	{
		m_can[stackIdx * 12 + i + 5] = new GameObject(GameObject::GO_CAN);
		m_can[stackIdx * 12 + i + 5]->pos = glm::vec3(canStartingX + (i * 1.2f) - 1.6f, 8.1f, canStartingZ);
		m_can[stackIdx * 12 + i + 5]->scale = glm::vec3(1.f, 2.f, 1);
		m_can[stackIdx * 12 + i + 5]->vel = glm::vec3(0.f, 0.f, 0.f);
		m_can[stackIdx * 12 + i + 5]->force = glm::vec3(0.f, 0.f, 0.f);
		m_can[stackIdx * 12 + i + 5]->active = true;
		m_can[stackIdx * 12 + i + 5]->collidingWithTable = false;
		m_can[stackIdx * 12 + i + 5]->touched = false;
		m_can[stackIdx * 12 + i + 5]->mass = 3;
	}
	for (int i = 0; i < 3; i++)
	{
		m_can[stackIdx * 12 + i + 9] = new GameObject(GameObject::GO_CAN);
		m_can[stackIdx * 12 + i + 9]->pos = glm::vec3(canStartingX + (i * 1.2f)- 1.f, 9.6f, canStartingZ);
		m_can[stackIdx * 12 + i + 9]->scale = glm::vec3(1, 2.f, 1);
		m_can[stackIdx * 12 + i + 9]->vel = glm::vec3(0.f, 0.f, 0.f);
		m_can[stackIdx * 12 + i + 9]->force = glm::vec3(0.f, 0.f, 0.f);
		m_can[stackIdx * 12 + i + 9]->active = true;
		m_can[stackIdx * 12 + i + 9]->collidingWithTable = false;
		m_can[stackIdx * 12 + 9]->touched = false;
		m_can[stackIdx * 12 + i + 9]->mass = 3;
	}
}