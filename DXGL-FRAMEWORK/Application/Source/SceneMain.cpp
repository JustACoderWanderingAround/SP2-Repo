#include "SceneMain.h"
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

#define time_scale 5

SceneMain::SceneMain()
{
	srand(rand());
	srand(rand() % rand());
	srand(rand() % rand() % rand());
}

SceneMain::~SceneMain()
{
	/*for (std::vector<GameObject*>::iterator iter = interactables.begin(); iter != interactables.end(); iter++) {
		if (!(*iter == nullptr)) {
			delete* iter;
		}
	}*/
}

void SceneMain::Init()
{

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

	// Init VBO here
	for (int i = 0; i < NUM_GEOMETRY; ++i)
	{
		meshList[i] = nullptr;
	}

	{
		meshList[GEO_AXES] = MeshBuilder::GenerateAxes("Axes", 10000.f, 10000.f, 10000.f);
		meshList[GEO_SPHERE] = MeshBuilder::GenerateSphere("ball", Color(1.f, 0.f, 0.f), 1.f, 16, 16);
		meshList[GEO_CUBE] = MeshBuilder::GenerateCube("Arm", Color(1, 0, 0), 1.f);
		meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
		meshList[GEO_TEXT]->textureID = LoadTGA("Image//ComicSans.tga");
		meshList[GEO_TEXT_BG] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1), 5);
		meshList[GEO_TEXT_BG]->textureID = LoadTGA("Image//scroll.tga");
		meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("shop UI", Color(0.5, 0.5, 0.5), 1);
		meshList[GEO_INVENTORY] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1), 1);
		meshList[GEO_INVENTORY]->textureID = LoadTGA("Image//inventory.tga");
		meshList[GEO_BLACK_BG] = MeshBuilder::GenerateQuad("shop UI", Color(0, 0, 0), 1);

		meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1), 100);
		meshList[GEO_LEFT]->textureID = LoadTGA("Image//skyboxleft.tga");
		meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("right", Color(1, 1, 1), 100);
		meshList[GEO_RIGHT]->textureID = LoadTGA("Image//skyboxright.tga");
		meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1), 100);
		meshList[GEO_FRONT]->textureID = LoadTGA("Image//skyboxfront.tga");
		meshList[GEO_BACK] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1), 100);
		meshList[GEO_BACK]->textureID = LoadTGA("Image//skyboxback.tga");
		meshList[GEO_TOP] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1), 100);
		meshList[GEO_TOP]->textureID = LoadTGA("Image//skyboxtop.tga");
		meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1), 100);
		meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//skyboxbottom.tga");

		meshList[GEO_TENT] = MeshBuilder::GenerateOBJ("purple tent", "OBJ//tent.obj");
		meshList[GEO_TENT]->textureID = LoadTGA("Image//tent.tga");

		meshList[GEO_FENCE] = MeshBuilder::GenerateOBJMTL("fence", "OBJ//fence01.obj",
			"OBJ//fence01.mtl");
		meshList[GEO_CRATE] = MeshBuilder::GenerateOBJMTL("fence", "OBJ//crate.obj",
			"OBJ//crate.mtl");
		meshList[GEO_CRATE]->textureID = LoadTGA("Image//crate.tga");
		meshList[GEO_ROAD] = MeshBuilder::GenerateQuad("road", Color(1, 1, 1), 10);
		meshList[GEO_ROAD]->textureID = LoadTGA("Image//road.tga");
		meshList[GEO_ARCH] = MeshBuilder::GenerateOBJMTL("arch", "OBJ//arch.obj",
			"OBJ//arch.mtl");
		meshList[GEO_ARCH]->textureID = LoadTGA("Image//arch.tga");
		meshList[GEO_SIDEWALK] = MeshBuilder::GenerateQuad("sidewalk", Color(1, 1, 1), 10);
		meshList[GEO_SIDEWALK]->textureID = LoadTGA("Image//brickfloor.tga");
		meshList[GEO_BLUE_TENT] = MeshBuilder::GenerateOBJ("blue tent", "OBJ//tent.obj");
		meshList[GEO_BLUE_TENT]->textureID = LoadTGA("Image//bluetent.tga");
		meshList[GEO_RED_TENT] = MeshBuilder::GenerateOBJ("red tent", "OBJ//tent.obj");
		meshList[GEO_RED_TENT]->textureID = LoadTGA("Image//redtent1.tga");
		meshList[GEO_GREEN_TENT] = MeshBuilder::GenerateOBJ("green tent", "OBJ//tent.obj");
		meshList[GEO_GREEN_TENT]->textureID = LoadTGA("Image//greentent.tga");
		meshList[GEO_MARKET] = MeshBuilder::GenerateOBJMTL("arch", "OBJ//markettent.obj",
			"OBJ//markettent.mtl");
		meshList[GEO_MARKET]->textureID = LoadTGA("Image//markettent.tga");
		meshList[GEO_CANDY_STORE] = MeshBuilder::GenerateOBJMTL("arch", "OBJ//cottoncandystall.obj",
			"OBJ//cottoncandystall.mtl");
		meshList[GEO_CANDY_STORE]->textureID = LoadTGA("Image//cottoncandystall.tga");
		meshList[GEO_CANDY_SIGN] = MeshBuilder::GenerateQuad("sign", Color(1, 1, 1), 1);
		meshList[GEO_CANDY_SIGN]->textureID = LoadTGA("Image//cottoncandysign.tga");
		meshList[GEO_PINBALL] = MeshBuilder::GenerateOBJMTL("pinball", "OBJ//pinball.obj",
			"OBJ//pinball.mtl");
		meshList[GEO_PINBALL]->textureID = LoadTGA("Image//pinball.tga");
		meshList[GEO_GROCERY_TENT] = MeshBuilder::GenerateOBJMTL("grocery tent", "OBJ//grocerytent.obj",
			"OBJ//grocerytent.mtl");
		meshList[GEO_GROCERY_TENT]->textureID = LoadTGA("Image//grocerytent.tga");
		meshList[GEO_APPLE] = MeshBuilder::GenerateOBJMTL("apple", "OBJ//apple.obj",
			"OBJ//apple.mtl");
		meshList[GEO_APPLE]->textureID = LoadTGA("Image//apple.tga");
		meshList[GEO_TABLE] = MeshBuilder::GenerateOBJ("table", "OBJ//table.obj");
		meshList[GEO_TABLE]->textureID = LoadTGA("Image//table.tga");
		meshList[GEO_DOORMAN] = MeshBuilder::GenerateOBJ("doorman", "OBJ//doorman.obj");
		meshList[GEO_DOORMAN]->textureID = LoadTGA("Image//doorman.tga");
		meshList[GEO_MOSIN] = MeshBuilder::GenerateOBJMTL("arch", "OBJ//mosin.obj",
			"OBJ//mosin.mtl");
		meshList[GEO_MOSIN]->textureID = LoadTGA("Image//mosin.tga");
		meshList[GEO_CANS] = MeshBuilder::GenerateOBJ("cans", "OBJ//sodacan.obj");
		meshList[GEO_CANS]->textureID = LoadTGA("Image//sodacan.tga");
		meshList[GEO_FERRIS_WHEEL] = MeshBuilder::GenerateOBJMTL("ferris wheel", "OBJ//ferriswheel1.obj",
			"OBJ//ferriswheel1.mtl");
		meshList[GEO_FERRIS_WHEEL]->textureID = LoadTGA("Image//ferriswheel.tga");
		meshList[GEO_WALL] = MeshBuilder::GenerateCube("wall", Color(48 / 255, 48 / 255, 48 / 255), 1.f);
		meshList[GEO_CAROUSEL] = MeshBuilder::GenerateOBJMTL("ferris wheel", "OBJ//carousel.obj",
			"OBJ//carousel.mtl");
		meshList[GEO_CAROUSEL]->textureID = LoadTGA("Image//carousel.tga");
		meshList[GEO_WOODEN_SIGN] = MeshBuilder::GenerateOBJMTL("wooden sign", "OBJ//woodensign.obj",
			"OBJ//woodensign.mtl");
		meshList[GEO_WOODEN_SIGN]->textureID = LoadTGA("Image//woodensign1.tga");
		meshList[GEO_LAMP_POST] = MeshBuilder::GenerateOBJMTL("lamp post", "OBJ//lamppost.obj",
			"OBJ//lamppost.mtl");
		meshList[GEO_LAMP_POST]->textureID = LoadTGA("Image//lamppost.tga");
		meshList[GEO_RUBIKS_CUBE] = MeshBuilder::GenerateOBJMTL("lamp post", "OBJ//rubikscube.obj",
			"OBJ//rubikscube.mtl");
		meshList[GEO_RUBIKS_CUBE]->textureID = LoadTGA("Image//rubikscube.tga");
		meshList[GEO_POTION] = MeshBuilder::GenerateOBJMTL("potion", "OBJ//potion.obj",
			"OBJ//potion.mtl");
		meshList[GEO_POTION]->textureID = LoadTGA("Image//potion.tga");

		meshList[GEO_ZAKU] = MeshBuilder::GenerateQuad("zaku", Color(1, 1, 1), 1);
		meshList[GEO_ZAKU]->textureID = LoadTGA("Image//zaku.tga");

		meshList[GEO_BALL] = MeshBuilder::GenerateQuad("ball pic", Color(1, 1, 1), 1);
		meshList[GEO_BALL]->textureID = LoadTGA("Image//ball.tga");

		meshList[GEO_RUBIK_PNG] = MeshBuilder::GenerateQuad("rubik pic", Color(1, 1, 1), 1);
		meshList[GEO_RUBIK_PNG]->textureID = LoadTGA("Image//rubikspng.tga");

		meshList[GEO_POTION_PNG] = MeshBuilder::GenerateQuad("potion pic", Color(1, 1, 1), 1);
		meshList[GEO_POTION_PNG]->textureID = LoadTGA("Image//potionpng.tga");

		meshList[GEO_COTTON_CANDY] = MeshBuilder::GenerateQuad("cotton candy pic", Color(1, 1, 1), 1);
		meshList[GEO_COTTON_CANDY]->textureID = LoadTGA("Image//cottoncandy.tga");

		meshList[GEO_MENU] = MeshBuilder::GenerateQuad("Menu", Color(1, 1, 1), 5);
		meshList[GEO_MENU]->textureID = LoadTGA("Image//MainMenu.tga");

		meshList[GEO_HM_RULES] = MeshBuilder::GenerateQuad("rules", Color(1, 1, 1), 1);
		meshList[GEO_HM_RULES]->textureID = LoadTGA("Image//hmrules.tga");

		meshList[GEO_PB_RULES] = MeshBuilder::GenerateQuad("PBrules", Color(1, 1, 1), 1);
		meshList[GEO_PB_RULES]->textureID = LoadTGA("Image//PinballRules.tga");
	}

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

	glm::mat4 projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 1000.0f);
	projectionStack.LoadMatrix(projection);

	glUniform1i(m_parameters[U_NUMLIGHTS], NUM_LIGHTS);
	// light params
	{
		light[0].position = glm::vec3(5, 10, 0);
		light[0].color.Set(1, 1, 1);
		light[0].type = Light::LIGHT_POINT;
		light[0].power = 1.f;
		light[0].kC = 0.01f;
		light[0].kL = 0.01f;
		light[0].kQ = 0.001f;
		light[0].cosCutoff = 45.f;
		light[0].cosInner = 30.f;
		light[0].exponent = 3.f;
		light[0].spotDirection = glm::vec3(0, 1, 0);

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

	enableLight = true;
	nearHitMan = false;
	nearToppled = false;
	nearPinball = false;
	nearShop = false;
	nearFerrisWheel = false;
	nearMarket = false;
	nearCottonStore = false;
	nearGrocery = false;
	nearHitMenSign = false;
	shopUI = false;
	shopItems = 0;
	ivt = false;
	notEnoughCoins = false;
	endScreen = false;
	HMsign = false;
	PBsign = false;

	mainFPSCam.Init(glm::vec3(0, -7, -40), glm::vec3(0, -12, 0), glm::vec3(0.f, 1, 0.f));

	m_player = new GameObject(GameObject::GO_BALL);
	m_player->pos = glm::vec3(mainFPSCam.position.x, mainFPSCam.position.y, mainFPSCam.position.z);
	m_player->scale = glm::vec3(1, 1, 1);
	m_player->vel = glm::vec3(0, 0, 0);
	m_player->mass = 1;
	m_player->momentOfInertia = m_player->mass * m_player->scale.x * m_player->scale.x;
	m_player->anglularVelocity = 0;

	m_player->torque = glm::vec3(0, 0, 0);
	m_player->multiplier = 1.0f / m_player->mass;

	stallCanBeToppled = new GameObject(GameObject::GO_CUBE);
	stallCanBeToppled->pos = glm::vec3(10.5, -7, -22.5);
	stallCanBeToppled->scale = glm::vec3(8.6, 7, 9);
	stallCanBeToppled->active = false;

	stallPinball = new GameObject(GameObject::GO_CUBE);
	stallPinball->pos = glm::vec3(-10.5, -7, -22.5);
	stallPinball->scale = glm::vec3(8.6, 7, 9);
	stallPinball->active = false;

	stallHitMan = new GameObject(GameObject::GO_CUBE);
	stallHitMan->pos = glm::vec3(-10.5, -7, 0);
	stallHitMan->scale = glm::vec3(8.6, 7, 9);
	stallHitMan->active = false;

	stallShop = new GameObject(GameObject::GO_CUBE);
	stallShop->pos = glm::vec3(10.5, -7, -5);
	stallShop->scale = glm::vec3(8.6, 7, 18);
	stallShop->active = false;

	// initalising fence game object
	for (int i = 0; i < MAX_FENCE; i++)
	{
		fences[i] = new GameObject(GameObject::GO_CUBE);
		fences[i]->active = false;
		if (i > 3 && i < 8)
		{
			fences[i]->pos = glm::vec3(45 - (i + 2) * 10, -8.5, -30);
			fences[i]->scale = glm::vec3(10, 3, 0.75);
		}
		else if (i >= 8 && i < 11)
		{
			fences[i]->pos = glm::vec3(30 - (i - 8) * 10, -8.5, 5);
			fences[i]->scale = glm::vec3(10, 3, 0.75);

		}
		else if (i >= 11 && i < 14)
		{

			fences[i]->pos = glm::vec3(30 - (i - 7) * 10, -8.5, 5);
			fences[i]->scale = glm::vec3(10, 3, 0.75);
			fences[i]->active = false;
		}
		else if (i >= 14 && i < 21)
		{
			fences[i]->pos = glm::vec3(30 - (i - 14) * 10, -8.5, 45);
			fences[i]->scale = glm::vec3(10, 3, 0.75);
		}
		else if (i >= 21 && i < 23)
		{
			fences[i]->pos = glm::vec3(20 + (i - 21) * 10, -8.5, 25);
			fences[i]->scale = glm::vec3(10, 3, 0.75);
		}
		else if (i >= 23 && i < 27)
		{
			fences[i]->pos = glm::vec3(35, -8.5, 10 + (i - 23) * 10);
			fences[i]->scale = glm::vec3(0.75, 3, 10);
		}
		else if (i >= 27 && i < 31)
		{
			fences[i]->pos = glm::vec3(-35, -8.5, 10 + (i - 27) * 10);
			fences[i]->scale = glm::vec3(0.75, 3, 10);
		}
		else if (i >= 31)
		{
			fences[i]->pos = glm::vec3(15, -8.5, 10 + (i - 31) * 10);
			fences[i]->scale = glm::vec3(0.75, 3, 10);
		}
		else { // i <= 3
			fences[i]->pos = glm::vec3(45 - i * 10, -8.5, -30);
			fences[i]->scale = glm::vec3(10, 3, 0.75);

		}

	}

	// game object for ferris wheel
	objs[0] = new GameObject(GameObject::GO_CUBE);
	objs[0]->pos = glm::vec3(-30, -8, 25);
	objs[0]->scale = glm::vec3(7, 5, 19);

	// game object for market
	objs[1] = new GameObject(GameObject::GO_CUBE);
	objs[1]->pos = glm::vec3(0, -8.5, 39);
	objs[1]->scale = glm::vec3(25, 5, 10);

	// game object for market
	objs[2] = new GameObject(GameObject::GO_CUBE);
	objs[2]->pos = glm::vec3(7, -8.5, 7);
	objs[2]->scale = glm::vec3(2.5, 5, 2);

	// game object for grocery
	objs[3] = new GameObject(GameObject::GO_CUBE);
	objs[3]->pos = glm::vec3(24, -8.5, 40);
	objs[3]->scale = glm::vec3(12, 5, 6);

	// game object for hitmen sign
	objs[4] = new GameObject(GameObject::GO_CUBE);
	objs[4]->pos = glm::vec3(-4.5, -8.5, -5);
	objs[4]->scale = glm::vec3(3, 10, 4);

	// game object for Pinball sign
	objs[5] = new GameObject(GameObject::GO_CUBE);
	objs[5]->pos = glm::vec3(-4.5, -8.5, -17);
	objs[5]->scale = glm::vec3(3, 10, 4);

	inventory = new Inventory();

	costOfZaku = 10;
	costOfBall = 5;
	costOfRubik = 15;
	costOfPotion = 30;

}



void SceneMain::Update(double dt)
{
	HandleKeyPress();

	//std::cout << "Pos: " << cameraArray[0].position.x << ", " << cameraArray[0].position.y << ", " << cameraArray[0].position.z << std::endl;


	m_player->pos = glm::vec3(mainFPSCam.position.x, mainFPSCam.position.y, mainFPSCam.position.z);
	
	coins = Player::GetInstance()->coins;
	Player::GetInstance()->setPos(m_player->pos);

	// check for collision btween player and stalls
	//canbetoppled
	if (stallCanBeToppled->CheckCSCollision(m_player))
	{
		nearToppled = true;
		if (mainFPSCam.position.x >= 6.5 && mainFPSCam.position.x < 7
			&& mainFPSCam.position.z >= -27.5 && mainFPSCam.position.z <= -18.5)
		{
			mainFPSCam.position.x = 6.499;
		}
		else if (mainFPSCam.position.x >= 14 && mainFPSCam.position.x < 15.1
			&& mainFPSCam.position.z >= -27.5 && mainFPSCam.position.z <= -18.5)
		{
			mainFPSCam.position.x = 15.099;
		}
		else if (mainFPSCam.position.z <= -17.6 && mainFPSCam.position.z >= -18
			&& mainFPSCam.position.x >= 6.5 && mainFPSCam.position.x <= 15)
		{
			mainFPSCam.position.z = -17.599;
		}
		else if (mainFPSCam.position.z <= -26 && mainFPSCam.position.z >= -27.5
			&& mainFPSCam.position.x >= 6.5 && mainFPSCam.position.x <= 15)
		{
			mainFPSCam.position.z = -27.499;
		}



	}
	// htimen
	else if (stallHitMan->CheckCSCollision(m_player))
	{
		nearHitMan = true;
		if (mainFPSCam.position.x <= -6.6 && mainFPSCam.position.x > -7
			&& mainFPSCam.position.z >= -5 && mainFPSCam.position.z <= 4)
		{
			mainFPSCam.position.x = -6.599;
		}
		else if (mainFPSCam.position.x <= -14 && mainFPSCam.position.x > -15.1
			&& mainFPSCam.position.z >= -5 && mainFPSCam.position.z <= 4)
		{
			mainFPSCam.position.x = -15.099;
		}

		else if (mainFPSCam.position.z <= 4.9 && mainFPSCam.position.z >= 3
			&& mainFPSCam.position.x <= -6.5 && mainFPSCam.position.x >= -15)
		{
			mainFPSCam.position.z = 4.999;
		}
		else if (mainFPSCam.position.z <= -3 && mainFPSCam.position.z >= -4.9
			&& mainFPSCam.position.x <= -6.5 && mainFPSCam.position.x >= -15)
		{
			mainFPSCam.position.z = -4.909;
		}
	}
	//pinball
	else if (stallPinball->CheckCSCollision(m_player))
	{
		nearPinball = true;
		if (mainFPSCam.position.x <= -6.5 && mainFPSCam.position.x > -7
			&& mainFPSCam.position.z >= -27.5 && mainFPSCam.position.z <= -18.5)
		{
			mainFPSCam.position.x = -6.499;
		}
		else if (mainFPSCam.position.x <= -14 && mainFPSCam.position.x > -15.1
			&& mainFPSCam.position.z >= -27.5 && mainFPSCam.position.z <= -18.5)
		{
			mainFPSCam.position.x = -15.199;
		}
		else if (mainFPSCam.position.z <= -17.6 && mainFPSCam.position.z >= -18
			&& mainFPSCam.position.x <= -6.5 && mainFPSCam.position.x >= -15)
		{
			mainFPSCam.position.z = -17.599;
		}
		else if (mainFPSCam.position.z <= -26 && mainFPSCam.position.z >= -27.5
			&& mainFPSCam.position.x <= -6.5 && mainFPSCam.position.x >= -15)
		{
			mainFPSCam.position.z = -27.599;
		}
	}
	else if (stallShop->CheckCSCollision(m_player))
	{
		nearShop = true;

		if (mainFPSCam.position.x >= 6.5 && mainFPSCam.position.x < 7
			&& mainFPSCam.position.z >= -14 && mainFPSCam.position.z <= 4)
		{
			mainFPSCam.position.x = 6.499;
		}
		else if (mainFPSCam.position.x > 14 && mainFPSCam.position.x <= 15
			&& mainFPSCam.position.z >= -14 && mainFPSCam.position.z <= 4)
		{
			mainFPSCam.position.x = 15.099;
		}
		else if (mainFPSCam.position.z > 3 && mainFPSCam.position.z <= 4.5
			&& mainFPSCam.position.x >= 6.5 && mainFPSCam.position.x <= 15)
		{
			mainFPSCam.position.z = 4.599;
		}
		else if (mainFPSCam.position.z <= -13 && mainFPSCam.position.z >= -14.9
			&& mainFPSCam.position.x >= 6.5 && mainFPSCam.position.x <= 15)
		{
			mainFPSCam.position.z = -14.999;
		}
	}
	else
	{
		nearToppled = false;
		nearHitMan = false;
		nearPinball = false;
		nearShop = false;
	}

	// checking collision for fences
	for (int i = 0; i < MAX_FENCE; i++)
	{
		if (fences[i]->CheckCSCollision(m_player))
		{
			if (i >= 23)
			{
				if (mainFPSCam.position.x <= (fences[i]->pos.x + fences[i]->scale.x / 2)
					&& mainFPSCam.position.x > fences[i]->pos.x
					&& mainFPSCam.position.z >= (fences[i]->pos.z - fences[i]->scale.z / 2)
					&& mainFPSCam.position.z <= (fences[i]->pos.z + fences[i]->scale.z / 2))
				{
					mainFPSCam.position.x = (fences[i]->pos.x + fences[i]->scale.x / 2) + 0.01;
				}
				else if (mainFPSCam.position.x >= (fences[i]->pos.x - fences[i]->scale.x / 2)
					&& mainFPSCam.position.x < fences[i]->pos.x
					&& mainFPSCam.position.z >= (fences[i]->pos.z - fences[i]->scale.z / 2)
					&& mainFPSCam.position.z <= (fences[i]->pos.z + fences[i]->scale.z / 2))
				{
					mainFPSCam.position.x = (fences[i]->pos.x - fences[i]->scale.x / 2) - 0.01;
				}
			}
			else
			{
				if (mainFPSCam.position.z >= (fences[i]->pos.z - fences[i]->scale.z / 2)
					&& mainFPSCam.position.z < fences[i]->pos.z
					&& mainFPSCam.position.x <= (fences[i]->pos.x + fences[i]->scale.x / 2)
					&& mainFPSCam.position.x >= (fences[i]->pos.x - fences[i]->scale.x / 2))
				{
					mainFPSCam.position.z = (fences[i]->pos.z - fences[i]->scale.z / 2) - 0.01;
				}
				else if (mainFPSCam.position.z <= (fences[i]->pos.z + fences[i]->scale.z / 2)
					&& mainFPSCam.position.z > fences[i]->pos.z
					&& mainFPSCam.position.x <= (fences[i]->pos.x + fences[i]->scale.x / 2)
					&& mainFPSCam.position.x >= (fences[i]->pos.x - fences[i]->scale.x / 2))
				{
					mainFPSCam.position.z = (fences[i]->pos.z + fences[i]->scale.z / 2) + 0.01;
				}
			}

		}
	}

	// checking collision for FerrisWheel
	if (objs[0]->CheckCSCollision(m_player))
	{
		nearFerrisWheel = true;
		if (mainFPSCam.position.x >= -33.5 && mainFPSCam.position.x < -32
			&& mainFPSCam.position.z > 15.5 && mainFPSCam.position.z < 34.5)
		{
			mainFPSCam.position.x = -33.599;
		}
		else if (mainFPSCam.position.x > -28 && mainFPSCam.position.x <= -26.5
			&& mainFPSCam.position.z > 15.5 && mainFPSCam.position.z < 34.5)
		{
			mainFPSCam.position.x = -26.499;
		}
		else if (mainFPSCam.position.z >= 15.5 && mainFPSCam.position.z < 17
			&& mainFPSCam.position.x > -33.5 && mainFPSCam.position.x < -26.5)
		{
			mainFPSCam.position.z = 15.499;
		}
		else if (mainFPSCam.position.z > 33 && mainFPSCam.position.z < 34.5
			&& mainFPSCam.position.x > -33.5 && mainFPSCam.position.x < -26.5)
		{
			mainFPSCam.position.z = 34.599;
		}
	}
	else if (objs[1]->CheckCSCollision(m_player)) // checking collision for Marketplace
	{
		nearMarket = true;
		if (mainFPSCam.position.x > 11 && mainFPSCam.position.x <= 12.5
			&& mainFPSCam.position.z > 34 && mainFPSCam.position.z < 44)
		{
			mainFPSCam.position.x = 12.599;
		}
		else if (mainFPSCam.position.x >= -12.5 && mainFPSCam.position.x <= -11
			&& mainFPSCam.position.z > 34 && mainFPSCam.position.z < 44)
		{
			mainFPSCam.position.x = -12.599;
		}
		else if (mainFPSCam.position.z >= 34 && mainFPSCam.position.z < 36
			&& mainFPSCam.position.x > -12.5 && mainFPSCam.position.x < 12.5)
		{
			mainFPSCam.position.z = 33.99;
		}
		else if (mainFPSCam.position.z > 42 && mainFPSCam.position.z <= 44
			&& mainFPSCam.position.x > -12.5 && mainFPSCam.position.x < 12.5)
		{
			mainFPSCam.position.z = 44.99;
		}
	}
	else if (objs[2]->CheckCSCollision(m_player)) // checking collision for CottonCandy Store
	{
		nearCottonStore = true;
		if (mainFPSCam.position.x > 7.5 && mainFPSCam.position.x <= 8.25
			&& mainFPSCam.position.z > 5 && mainFPSCam.position.z < 9)
		{
			mainFPSCam.position.x = 8.2599;
		}
		else if (mainFPSCam.position.x >= 5.75 && mainFPSCam.position.x <= 6.5
			&& mainFPSCam.position.z > 5 && mainFPSCam.position.z < 9)
		{
			mainFPSCam.position.x = 5.7599;
		}
		else if (mainFPSCam.position.z >= 5 && mainFPSCam.position.z < 6
			&& mainFPSCam.position.x > 5.75 && mainFPSCam.position.x < 8.25)
		{
			mainFPSCam.position.z = 4.99;
		}
		else if (mainFPSCam.position.z > 8 && mainFPSCam.position.z <= 9
			&& mainFPSCam.position.x > 5.75 && mainFPSCam.position.x < 8.25)
		{
			mainFPSCam.position.z = 9.099;
		}
	}
	else if (objs[3]->CheckCSCollision(m_player)) // checking collision for Grocery Stall
	{
		nearGrocery = true;
		if (mainFPSCam.position.x > 29 && mainFPSCam.position.x <= 30
			&& mainFPSCam.position.z < 42.5 && mainFPSCam.position.z > 37.5)
		{
			mainFPSCam.position.x = 30.01;
		}
		else if (mainFPSCam.position.x >= 18 && mainFPSCam.position.x <= 19
			&& mainFPSCam.position.z > 42.5 && mainFPSCam.position.z > 37.5)
		{
			mainFPSCam.position.x = 17.99;
		}
		else if (mainFPSCam.position.z >= 37.5 && mainFPSCam.position.z < 39
			&& mainFPSCam.position.x > 18 && mainFPSCam.position.x < 30)
		{
			mainFPSCam.position.z = 37.499;
		}
		else if (mainFPSCam.position.z > 41 && mainFPSCam.position.z <= 42.5
			&& mainFPSCam.position.x > 18 && mainFPSCam.position.x < 30)
		{
			mainFPSCam.position.z = 42.501;
		}
	}
	else if (objs[4]->CheckCSCollision(m_player)) // checking collision for Hitman Help Sign
	{
		nearHitMenSign = true;
		if (mainFPSCam.position.x <= -4 && mainFPSCam.position.x > -4.5
			&& mainFPSCam.position.z > -9 && mainFPSCam.position.z < -1)
		{
			mainFPSCam.position.x = -3.999;
		}
		else if (mainFPSCam.position.x >= -6 && mainFPSCam.position.x < -5
			&& mainFPSCam.position.z > -9 && mainFPSCam.position.z < -1)
		{
			mainFPSCam.position.x = -6.01;
		}
	}
	else if (objs[5]->CheckCSCollision(m_player)) // checking collision for Pinball Help Sign
	{
		nearPinballSign = true;
		if (mainFPSCam.position.x <= -4 && mainFPSCam.position.x > -4.5
			&& mainFPSCam.position.z > -19 && mainFPSCam.position.z < -11)
		{
			mainFPSCam.position.x = -3.999;
		}
		else if (mainFPSCam.position.x >= -6 && mainFPSCam.position.x < -5
			&& mainFPSCam.position.z > -19 && mainFPSCam.position.z < -11)
		{
			mainFPSCam.position.x = -6.01;
		}
	}
	else
	{
		nearFerrisWheel = false;
		nearMarket = false;
		nearCottonStore = false;
		nearGrocery = false;
		nearHitMenSign = false;
		nearPinballSign = false;
	}

	if (mainFPSCam.position.x >= 49)
	{
		mainFPSCam.position.x = 48.99;
	}
	else if (mainFPSCam.position.x <= -49)
	{
		mainFPSCam.position.x = -48.99;
	}
	else if (mainFPSCam.position.z >= 49)
	{
		mainFPSCam.position.z = 48.99;
	}
	else if (mainFPSCam.position.z <= -49)
	{
		mainFPSCam.position.z = -48.99;
	}

	if (Application::getGameStart())
	{
		mainFPSCam.Update(dt);
		m_player->fixedUpdate(static_cast<float>(dt));
	}
	
	if (Application::getGameStart() == false && KeyboardController::GetInstance()->IsKeyPressed('F'))
	{
		Application::setGameStart(true);
	}
	if (nearHitMan && KeyboardController::GetInstance()->IsKeyPressed('F')) {
		SceneManager::GetInstance()->LoadScene(SceneManager::SCENE_NUM::SCENE_HITMEN);
	}
	if (nearToppled && KeyboardController::GetInstance()->IsKeyPressed('F')) {
		SceneManager::GetInstance()->LoadScene(SceneManager::SCENE_NUM::SCENE_CANTOPPLE);
	}
	if (nearPinball && KeyboardController::GetInstance()->IsKeyPressed('F')) {
		SceneManager::GetInstance()->LoadScene(SceneManager::SCENE_NUM::SCENE_PINBALL);
	}

	if (Application::getCutScene())
	{
		mainFPSCam.Update(dt);
		m_player->fixedUpdate(static_cast<float>(dt));
	}

	if (Application::getGameStart() && Application::getCutScene() == false && KeyboardController::GetInstance()->IsKeyPressed('C'))
	{
		Application::setCutScene(true);
	}

}

void SceneMain::Render()
{
	// Clear color buffer every frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Load view matrix stack and set it with camera position, target position and up direction
	viewStack.LoadIdentity(); {
		viewStack.LookAt(
			mainFPSCam.position.x, mainFPSCam.position.y, mainFPSCam.position.z,
			mainFPSCam.target.x, mainFPSCam.target.y, mainFPSCam.target.z,
			mainFPSCam.up.x, mainFPSCam.up.y, mainFPSCam.up.z
		);
		// Load identity matrix into the model stack
	} modelStack.LoadIdentity();

	for (int i = 0; i < NUM_LIGHTS; i++) {

		RenderLight(i);

	}
	for (int i = 0; i < NUM_LIGHTS; i++) {
		modelStack.PushMatrix(); {
			modelStack.Translate(light[i].position.x, light[i].position.y, light[i].position.z);
		} modelStack.PopMatrix();
	}
	/*modelStack.PushMatrix(); {
		RenderMesh(meshList[GEO_AXES], false);
	} modelStack.PopMatrix();*/

	RenderSkybox();


	// front fence
	for (int i = 0; i < 10; i++)
	{
		if (i != 4 && i != 5)
		{
			modelStack.PushMatrix();
			{
				modelStack.Translate(45 - i * 10, -8.25, -30);
				modelStack.Scale(0.02, 0.02, 0.02);
				meshList[GEO_FENCE]->material.kAmbient.Set(0.23f, 0.23f, 0.23f);
				meshList[GEO_FENCE]->material.kDiffuse.Set(0.27f, 0.27f, 0.27f);
				meshList[GEO_FENCE]->material.kSpecular.Set(0.77f, 0.77f, 0.77f);
				meshList[GEO_FENCE]->material.kShininess = 4.45f;
				RenderMesh(meshList[GEO_FENCE], enableLight);
			}
			modelStack.PopMatrix();
		}

		modelStack.PushMatrix();
		{
			modelStack.Translate(45 - i * 10, -9.99, -40);
			modelStack.Rotate(90, -1, 0, 0);
			meshList[GEO_ROAD]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
			meshList[GEO_ROAD]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
			meshList[GEO_ROAD]->material.kSpecular.Set(0.9f, 0.9f, 0.9f);
			meshList[GEO_ROAD]->material.kShininess = 1.f;
			RenderMesh(meshList[GEO_ROAD], enableLight);
		}
		modelStack.PopMatrix();
	}

	for (int i = 0; i < 2; i++)
	{
		modelStack.PushMatrix();
		{
			modelStack.Translate(15, -8.25, 10 + i * 10);
			modelStack.Rotate(90, 0, 1, 0);
			modelStack.Scale(0.02, 0.02, 0.02);
			meshList[GEO_FENCE]->material.kAmbient.Set(0.23f, 0.23f, 0.23f);
			meshList[GEO_FENCE]->material.kDiffuse.Set(0.27f, 0.27f, 0.27f);
			meshList[GEO_FENCE]->material.kSpecular.Set(0.77f, 0.77f, 0.77f);
			meshList[GEO_FENCE]->material.kShininess = 4.45f;
			RenderMesh(meshList[GEO_FENCE], enableLight);
		}
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		{
			modelStack.Translate(20 + i * 10, -8.25, 25);
			modelStack.Scale(0.02, 0.02, 0.02);
			meshList[GEO_FENCE]->material.kAmbient.Set(0.23f, 0.23f, 0.23f);
			meshList[GEO_FENCE]->material.kDiffuse.Set(0.27f, 0.27f, 0.27f);
			meshList[GEO_FENCE]->material.kSpecular.Set(0.77f, 0.77f, 0.77f);
			meshList[GEO_FENCE]->material.kShininess = 4.45f;
			RenderMesh(meshList[GEO_FENCE], enableLight);
		}
		modelStack.PopMatrix();
	}


	//for (int i = 0; i < MAX_FENCE; i++)
	//{
	//	modelStack.PushMatrix();
	//	{
	//		modelStack.Translate(fences[i]->pos.x, fences[i]->pos.y, fences[i]->pos.z);
	//		modelStack.Scale(fences[i]->scale.x, fences[i]->scale.y, fences[i]->scale.z);
	//		RenderMesh(meshList[GEO_CUBE], enableLight);
	//	}
	//	modelStack.PopMatrix();
	//}


	modelStack.PushMatrix();
	{
		modelStack.Translate(0, -11, -30);
		modelStack.Rotate(-90, 0, 1, 0);
		modelStack.Scale(0.05, 0.05, 0.1);
		RenderMesh(meshList[GEO_ARCH], enableLight);
	}
	modelStack.PopMatrix();

	// crates
	{
		modelStack.PushMatrix();
		{
			modelStack.Translate(12, -9, -25);
			meshList[GEO_CRATE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
			meshList[GEO_CRATE]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
			meshList[GEO_CRATE]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
			meshList[GEO_CRATE]->material.kShininess = 0.5f;
			RenderMesh(meshList[GEO_CRATE], enableLight);
		}
		modelStack.PopMatrix();
		modelStack.PushMatrix();
		{
			modelStack.Translate(-7.5, -9, -21);
			meshList[GEO_CRATE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
			meshList[GEO_CRATE]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
			meshList[GEO_CRATE]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
			meshList[GEO_CRATE]->material.kShininess = 0.5f;
			RenderMesh(meshList[GEO_CRATE], enableLight);
		}
		modelStack.PopMatrix();
	}


	// purple tent (pinball)
	modelStack.PushMatrix();
	{
		modelStack.Translate(-10, -10, -22.5);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Scale(0.5, 0.5, 0.75);
		modelStack.PushMatrix();
		{
			modelStack.Translate(-9, 2.5, -0.5);
			modelStack.Scale(0.75, 5, 9);
			meshList[GEO_WALL]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
			meshList[GEO_WALL]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
			meshList[GEO_WALL]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
			meshList[GEO_WALL]->material.kShininess = 1.f;
			RenderMesh(meshList[GEO_WALL], enableLight);
		}
		modelStack.PopMatrix();
		modelStack.PushMatrix();
		{
			modelStack.Translate(9, 2.5, -0.5);
			modelStack.Scale(0.75, 5, 9);
			meshList[GEO_WALL]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
			meshList[GEO_WALL]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
			meshList[GEO_WALL]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
			meshList[GEO_WALL]->material.kShininess = 1.f;
			RenderMesh(meshList[GEO_WALL], enableLight);
		}
		modelStack.PopMatrix();
		meshList[GEO_TENT]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_TENT]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_TENT]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_TENT]->material.kShininess = 1.f;
		RenderMesh(meshList[GEO_TENT], enableLight);
	}
	modelStack.PopMatrix();


	// blue tent (toppled)
	modelStack.PushMatrix();
	{
		modelStack.Translate(10, -10, -22.5);
		modelStack.Rotate(-90, 0, 1, 0);
		modelStack.Scale(0.5, 0.5, 0.75);
		modelStack.PushMatrix();
		{
			modelStack.Translate(-9, 2.5, -2.5);
			modelStack.Scale(0.75, 5, 7);
			meshList[GEO_WALL]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
			meshList[GEO_WALL]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
			meshList[GEO_WALL]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
			meshList[GEO_WALL]->material.kShininess = 1.f;
			RenderMesh(meshList[GEO_WALL], enableLight);
		}
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		{
			modelStack.Translate(9, 2.5, -2.5);
			modelStack.Scale(0.75, 5, 7);
			meshList[GEO_WALL]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
			meshList[GEO_WALL]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
			meshList[GEO_WALL]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
			meshList[GEO_WALL]->material.kShininess = 1.f;
			RenderMesh(meshList[GEO_WALL], enableLight);
		}
		modelStack.PopMatrix();
		meshList[GEO_BLUE_TENT]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_BLUE_TENT]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_BLUE_TENT]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_BLUE_TENT]->material.kShininess = 1.f;
		RenderMesh(meshList[GEO_BLUE_TENT], enableLight);
	}
	modelStack.PopMatrix();

	// red tent (hitmen)
	modelStack.PushMatrix();
	{
		modelStack.Translate(-10, -10, 0);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Scale(0.5, 0.5, 0.75);
		modelStack.PushMatrix();
		{
			modelStack.Translate(-9, 2.5, -1.5);
			modelStack.Scale(0.75, 5, 8);
			meshList[GEO_WALL]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
			meshList[GEO_WALL]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
			meshList[GEO_WALL]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
			meshList[GEO_WALL]->material.kShininess = 1.f;
			RenderMesh(meshList[GEO_WALL], enableLight);
		}
		modelStack.PopMatrix();
		modelStack.PushMatrix();
		{
			modelStack.Translate(9, 2.5, -1.5);
			modelStack.Scale(0.75, 5, 8);
			meshList[GEO_WALL]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
			meshList[GEO_WALL]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
			meshList[GEO_WALL]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
			meshList[GEO_WALL]->material.kShininess = 1.f;
			RenderMesh(meshList[GEO_WALL], enableLight);
		}
		modelStack.PopMatrix();
		meshList[GEO_RED_TENT]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_RED_TENT]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_RED_TENT]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_RED_TENT]->material.kShininess = 1.f;
		RenderMesh(meshList[GEO_RED_TENT], enableLight);
	}
	modelStack.PopMatrix();

	// green tent (shop)
	modelStack.PushMatrix();
	{
		modelStack.Translate(10, -10, -5);
		modelStack.Rotate(-90, 0, 1, 0);
		modelStack.Scale(1, 0.5, 0.75);
		modelStack.PushMatrix();
		{
			modelStack.Translate(-9, 2.5, -0.5);
			modelStack.Scale(0.5, 5, 9);
			meshList[GEO_WALL]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
			meshList[GEO_WALL]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
			meshList[GEO_WALL]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
			meshList[GEO_WALL]->material.kShininess = 1.f;
			RenderMesh(meshList[GEO_WALL], enableLight);
		}
		modelStack.PopMatrix();
		modelStack.PushMatrix();
		{
			modelStack.Translate(9, 2.5, -0.5);
			modelStack.Scale(0.5, 5, 9);
			meshList[GEO_WALL]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
			meshList[GEO_WALL]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
			meshList[GEO_WALL]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
			meshList[GEO_WALL]->material.kShininess = 1.f;
			RenderMesh(meshList[GEO_WALL], enableLight);
		}
		modelStack.PopMatrix();
		meshList[GEO_GREEN_TENT]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_GREEN_TENT]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_GREEN_TENT]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_GREEN_TENT]->material.kShininess = 1.f;
		RenderMesh(meshList[GEO_GREEN_TENT], enableLight);
	}
	modelStack.PopMatrix();




	for (int i = 0; i < 7; i++)
	{
		if (i != 3)
		{
			modelStack.PushMatrix();
			{
				modelStack.Translate(30 - i * 10, -8.25, 5);
				modelStack.Scale(0.02, 0.02, 0.02);
				meshList[GEO_FENCE]->material.kAmbient.Set(0.23f, 0.23f, 0.23f);
				meshList[GEO_FENCE]->material.kDiffuse.Set(0.27f, 0.27f, 0.27f);
				meshList[GEO_FENCE]->material.kSpecular.Set(0.77f, 0.77f, 0.77f);
				meshList[GEO_FENCE]->material.kShininess = 4.45f;
				RenderMesh(meshList[GEO_FENCE], enableLight);
			}
			modelStack.PopMatrix();
		}

		modelStack.PushMatrix();
		{
			modelStack.Translate(30 - i * 10, -8.25, 45);
			modelStack.Scale(0.02, 0.02, 0.02);
			meshList[GEO_FENCE]->material.kAmbient.Set(0.23f, 0.23f, 0.23f);
			meshList[GEO_FENCE]->material.kDiffuse.Set(0.27f, 0.27f, 0.27f);
			meshList[GEO_FENCE]->material.kSpecular.Set(0.77f, 0.77f, 0.77f);
			meshList[GEO_FENCE]->material.kShininess = 4.45f;
			RenderMesh(meshList[GEO_FENCE], enableLight);
		}
		modelStack.PopMatrix();
	}

	for (int i = 0; i < 4; i++)
	{
		modelStack.PushMatrix();
		{
			modelStack.Translate(35, -8.25, 10 + i * 10);
			modelStack.Rotate(90, 0, 1, 0);
			modelStack.Scale(0.02, 0.02, 0.02);
			meshList[GEO_FENCE]->material.kAmbient.Set(0.23f, 0.23f, 0.23f);
			meshList[GEO_FENCE]->material.kDiffuse.Set(0.27f, 0.27f, 0.27f);
			meshList[GEO_FENCE]->material.kSpecular.Set(0.77f, 0.77f, 0.77f);
			meshList[GEO_FENCE]->material.kShininess = 4.45f;
			RenderMesh(meshList[GEO_FENCE], enableLight);
		}
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		{
			modelStack.Translate(-35, -8.25, 10 + i * 10);
			modelStack.Rotate(90, 0, 1, 0);
			modelStack.Scale(0.02, 0.02, 0.02);
			meshList[GEO_FENCE]->material.kAmbient.Set(0.23f, 0.23f, 0.23f);
			meshList[GEO_FENCE]->material.kDiffuse.Set(0.27f, 0.27f, 0.27f);
			meshList[GEO_FENCE]->material.kSpecular.Set(0.77f, 0.77f, 0.77f);
			meshList[GEO_FENCE]->material.kShininess = 4.45f;
			RenderMesh(meshList[GEO_FENCE], enableLight);
		}
		modelStack.PopMatrix();
	}



	for (int i = 0; i < 4; i++)
	{
		modelStack.PushMatrix();
		{
			modelStack.Translate(0, -9.99, -30 + i * 10);
			modelStack.Rotate(90, -1, 0, 0);
			meshList[GEO_SIDEWALK]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
			meshList[GEO_SIDEWALK]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
			meshList[GEO_SIDEWALK]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
			meshList[GEO_SIDEWALK]->material.kShininess = 1.f;
			RenderMesh(meshList[GEO_SIDEWALK], enableLight);
		}
		modelStack.PopMatrix();

	}

	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			modelStack.PushMatrix();
			{
				modelStack.Translate(-30 + i * 10, -9.99, 10 + j * 10);
				modelStack.Rotate(90, -1, 0, 0);
				meshList[GEO_SIDEWALK]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
				meshList[GEO_SIDEWALK]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
				meshList[GEO_SIDEWALK]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
				meshList[GEO_SIDEWALK]->material.kShininess = 1.f;
				RenderMesh(meshList[GEO_SIDEWALK], enableLight);
			}
			modelStack.PopMatrix();
		}
	}

	modelStack.PushMatrix();
	{
		modelStack.Translate(0, -8.5, 40);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Scale(100, 100, 100);
		meshList[GEO_MARKET]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_MARKET]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_MARKET]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_MARKET]->material.kShininess = 1.f;
		RenderMesh(meshList[GEO_MARKET], enableLight);
	}
	modelStack.PopMatrix();


	//modelStack.PushMatrix();
	//{
	//	modelStack.Translate(objs[1]->pos.x, objs[1]->pos.y, objs[1]->pos.z);
	//	modelStack.Scale(objs[1]->scale.x, objs[1]->scale.y, objs[1]->scale.z);
	//	RenderMesh(meshList[GEO_CUBE], enableLight);
	//}
	//modelStack.PopMatrix();

	modelStack.PushMatrix();
	{
		modelStack.Translate(7, -7.9, 7.55);
		modelStack.Scale(1, 0.75, 1);
		meshList[GEO_CANDY_SIGN]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_CANDY_SIGN]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_CANDY_SIGN]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_CANDY_SIGN]->material.kShininess = 1.f;
		RenderMesh(meshList[GEO_CANDY_SIGN], enableLight);
	}
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	{
		modelStack.Translate(7, -10, 7);
		modelStack.Scale(0.25, 0.3, 0.25);
		meshList[GEO_CANDY_STORE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_CANDY_STORE]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_CANDY_STORE]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_CANDY_STORE]->material.kShininess = 1.f;
		RenderMesh(meshList[GEO_CANDY_STORE], enableLight);
	}
	modelStack.PopMatrix();

	//modelStack.PushMatrix();
	//{
	//	modelStack.Translate(objs[2]->pos.x, objs[2]->pos.y, objs[2]->pos.z);
	//	modelStack.Scale(objs[2]->scale.x, objs[2]->scale.y, objs[2]->scale.z);
	//	RenderMesh(meshList[GEO_CUBE], enableLight);
	//}
	//modelStack.PopMatrix();

	modelStack.PushMatrix();
	{
		modelStack.Translate(-9, -10, -24);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Scale(0.5, 0.5, 0.5);
		meshList[GEO_PINBALL]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_PINBALL]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_PINBALL]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_PINBALL]->material.kShininess = 1.f;
		RenderMesh(meshList[GEO_PINBALL], enableLight);
	}
	modelStack.PopMatrix();


	modelStack.PushMatrix();
	{
		modelStack.Translate(25, -10, 40);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Scale(4, 4, 4);
		meshList[GEO_GROCERY_TENT]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_GROCERY_TENT]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_GROCERY_TENT]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_GROCERY_TENT]->material.kShininess = 1.f;
		RenderMesh(meshList[GEO_GROCERY_TENT], enableLight);
	}
	modelStack.PopMatrix();

	//modelStack.PushMatrix();
	//{
	//	modelStack.Translate(objs[3]->pos.x, objs[3]->pos.y, objs[3]->pos.z);
	//	modelStack.Scale(objs[3]->scale.x, objs[3]->scale.y, objs[3]->scale.z);
	//	RenderMesh(meshList[GEO_CUBE], enableLight);
	//}
	//modelStack.PopMatrix();


	for (int i = 0; i < 5; i++)
	{
		if (i != 2)
		{
			modelStack.PushMatrix();
			{
				modelStack.Translate(27 - 1 * i, -9, 40);
				meshList[GEO_APPLE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
				meshList[GEO_APPLE]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
				meshList[GEO_APPLE]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
				meshList[GEO_APPLE]->material.kShininess = 1.f;
				RenderMesh(meshList[GEO_APPLE], enableLight);
			}
			modelStack.PopMatrix();
		}

	}

	modelStack.PushMatrix();
	{
		modelStack.Translate(8, -10, -22.5);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Scale(4, 2, 2);
		meshList[GEO_TABLE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_TABLE]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_TABLE]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_TABLE]->material.kShininess = 1.f;
		RenderMesh(meshList[GEO_TABLE], enableLight);
	}
	modelStack.PopMatrix();


	modelStack.PushMatrix();
	{
		modelStack.Translate(9, -10, -5);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Scale(7, 2, 3);
		meshList[GEO_TABLE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_TABLE]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_TABLE]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_TABLE]->material.kShininess = 1.f;
		RenderMesh(meshList[GEO_TABLE], enableLight);
	}
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	{
		modelStack.Translate(11.5, -10, -5);
		modelStack.Rotate(-90, 0, 1, 0);
		modelStack.Scale(0.75, 0.75, 0.75);
		meshList[GEO_DOORMAN]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_DOORMAN]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_DOORMAN]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_DOORMAN]->material.kShininess = 1.f;
		RenderMesh(meshList[GEO_DOORMAN], enableLight);
	}
	modelStack.PopMatrix();

	// cans
	for (int j = 0; j < 2; j++)
	{
		for (int i = 0; i < 5; i++)
		{
			modelStack.PushMatrix();
			{
				modelStack.Translate(8.5 - j, -8, -25 + i * 0.5 + (j * 3));
				modelStack.Scale(0.5, 0.5, 0.5);
				meshList[GEO_CANS]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
				meshList[GEO_CANS]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
				meshList[GEO_CANS]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
				meshList[GEO_CANS]->material.kShininess = 1.f;
				RenderMesh(meshList[GEO_CANS], enableLight);
			}
			modelStack.PopMatrix();
			if (i != 0)
			{
				modelStack.PushMatrix();
				{
					modelStack.Translate(8.5 - j, -7.25, -25.25 + i * 0.5 + (j * 3));
					modelStack.Scale(0.5, 0.5, 0.5);
					meshList[GEO_CANS]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
					meshList[GEO_CANS]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
					meshList[GEO_CANS]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
					meshList[GEO_CANS]->material.kShininess = 1.f;
					RenderMesh(meshList[GEO_CANS], enableLight);
				}
				modelStack.PopMatrix();
				if (i != 1)
				{
					modelStack.PushMatrix();
					{
						modelStack.Translate(8.5 - j, -6.5, -25.5 + i * 0.5 + (j * 3));
						modelStack.Scale(0.5, 0.5, 0.5);
						meshList[GEO_CANS]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
						meshList[GEO_CANS]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
						meshList[GEO_CANS]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
						meshList[GEO_CANS]->material.kShininess = 1.f;
						RenderMesh(meshList[GEO_CANS], enableLight);
					}
					modelStack.PopMatrix();
				}
			}

		}
	}

	modelStack.PushMatrix();
	{
		modelStack.Translate(-7.5, -10, 0);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Scale(4, 2, 1);
		meshList[GEO_TABLE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_TABLE]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_TABLE]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_TABLE]->material.kShininess = 1.f;
		RenderMesh(meshList[GEO_TABLE], enableLight);
	}
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	{
		modelStack.Translate(-12.5, -10, 0);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Scale(4, 3, 1.5);
		meshList[GEO_TABLE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_TABLE]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_TABLE]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_TABLE]->material.kShininess = 1.f;
		RenderMesh(meshList[GEO_TABLE], enableLight);
	}
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	{
		modelStack.Translate(-12.7, -7.1, 0);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Scale(4, 1, 1);
		meshList[GEO_TABLE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_TABLE]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_TABLE]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_TABLE]->material.kShininess = 1.f;
		RenderMesh(meshList[GEO_TABLE], enableLight);
	}
	modelStack.PopMatrix();

	for (int i = 0; i < 8; i++)
	{
		modelStack.PushMatrix();
		{
			modelStack.Translate(-11.75, -7.05, 3.5 - i * 1);
			modelStack.Rotate(90, 0, 1, 0);
			modelStack.Scale(0.25, 0.25, 0.25);
			meshList[GEO_DOORMAN]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
			meshList[GEO_DOORMAN]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
			meshList[GEO_DOORMAN]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
			meshList[GEO_DOORMAN]->material.kShininess = 1.f;
			RenderMesh(meshList[GEO_DOORMAN], enableLight);
		}
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		{
			modelStack.Translate(-12.5, -6.1, 3.5 - i * 1);
			modelStack.Rotate(90, 0, 1, 0);
			modelStack.Scale(0.25, 0.25, 0.25);
			meshList[GEO_DOORMAN]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
			meshList[GEO_DOORMAN]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
			meshList[GEO_DOORMAN]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
			meshList[GEO_DOORMAN]->material.kShininess = 1.f;
			RenderMesh(meshList[GEO_DOORMAN], enableLight);
		}
		modelStack.PopMatrix();
	}

	modelStack.PushMatrix();
	{
		modelStack.Translate(-7.5, -8, 0);
		modelStack.Rotate(90, 0, 0, 1);
		//modelStack.Rotate(90, 1, 0, 0);
		modelStack.Scale(0.25, 0.25, 0.25);
		meshList[GEO_MOSIN]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_MOSIN]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_MOSIN]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_MOSIN]->material.kShininess = 1.f;
		RenderMesh(meshList[GEO_MOSIN], enableLight);
	}
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	{
		modelStack.Translate(-30, 3.5, 25);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Scale(5, 5, 5);
		meshList[GEO_FERRIS_WHEEL]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_FERRIS_WHEEL]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_FERRIS_WHEEL]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_FERRIS_WHEEL]->material.kShininess = 1.f;
		RenderMesh(meshList[GEO_FERRIS_WHEEL], enableLight);
	}
	modelStack.PopMatrix();

	//modelStack.PushMatrix();
	//{
	//	modelStack.Translate(objs[0]->pos.x, objs[0]->pos.y, objs[0]->pos.z);
	//	modelStack.Scale(objs[0]->scale.x, objs[0]->scale.y, objs[0]->scale.z);
	//	RenderMesh(meshList[GEO_CUBE], enableLight);
	//}
	//modelStack.PopMatrix();

	modelStack.PushMatrix();
	{
		modelStack.Translate(25, -10, 15);
		modelStack.Scale(7, 7, 7);
		meshList[GEO_CAROUSEL]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_CAROUSEL]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_CAROUSEL]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_CAROUSEL]->material.kShininess = 1.f;
		RenderMesh(meshList[GEO_CAROUSEL], enableLight);
	}
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	{
		modelStack.Translate(-6, -12, -5);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Scale(2, 3, 2);
		meshList[GEO_WOODEN_SIGN]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_WOODEN_SIGN]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_WOODEN_SIGN]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_WOODEN_SIGN]->material.kShininess = 1.f;
		RenderMesh(meshList[GEO_WOODEN_SIGN], enableLight);
	}
	modelStack.PopMatrix();

	//pinball
	modelStack.PushMatrix();
	{
		modelStack.Translate(-6, -12, -17);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Scale(2, 3, 2);
		meshList[GEO_WOODEN_SIGN]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_WOODEN_SIGN]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_WOODEN_SIGN]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_WOODEN_SIGN]->material.kShininess = 1.f;
		RenderMesh(meshList[GEO_WOODEN_SIGN], enableLight);
	}
	modelStack.PopMatrix();
	//modelStack.PushMatrix();
	//{
	//	modelStack.Translate(objs[4]->pos.x, objs[4]->pos.y, objs[4]->pos.z);
	//	modelStack.Scale(objs[4]->scale.x, objs[4]->scale.y, objs[4]->scale.z);
	//	RenderMesh(meshList[GEO_CUBE], enableLight);
	//}
	//modelStack.PopMatrix();

	modelStack.PushMatrix();
	{
		modelStack.Translate(9, -7, -7.5);
		modelStack.Rotate(-90, 0, 1, 0);
		modelStack.Scale(0.1, 0.1, 0.1);
		RenderZaku();
	}
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	{
		modelStack.Translate(9, -8, -10);
		modelStack.Scale(0.1, 0.1, 0.1);
		RenderMesh(meshList[GEO_RUBIKS_CUBE], enableLight);
	}
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	{
		modelStack.Translate(9, -7.5, -2.5);
		modelStack.Scale(0.5, 0.5, 0.5);
		RenderMesh(meshList[GEO_SPHERE], enableLight);
	}
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	{
		modelStack.Translate(9, -8, 0);
		modelStack.Scale(3, 3, 3);
		RenderMesh(meshList[GEO_POTION], enableLight);
	}
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	{
		modelStack.Translate(-5.73, -5.8, -5);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Scale(2.5, 2.5, 2.5);
		RenderMesh(meshList[GEO_HM_RULES], enableLight);
	}
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	{
		modelStack.Translate(-5.73, -5.8, -17);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Scale(2.5, 2.5, 2.5);
		RenderMesh(meshList[GEO_PB_RULES], enableLight);
	}
	modelStack.PopMatrix();


	//render text
	{

		

		if (nearToppled == true)
		{
			RenderMeshOnScreen(meshList[GEO_TEXT_BG], 400, 100, 200, 15);
			RenderTextOnScreen(meshList[GEO_TEXT], " Play 'I Can Be Toppled'? - [F]", Color(0, 0, 0), 25, 0, 100);
		}
		else if (nearHitMan == true)
		{
			RenderMeshOnScreen(meshList[GEO_TEXT_BG], 400, 100, 200, 15);
			RenderTextOnScreen(meshList[GEO_TEXT], " Play 'HitMen'? - [F]", Color(0, 0, 0), 25, 0, 100);
		}
		else if (nearPinball == true)
		{
			RenderMeshOnScreen(meshList[GEO_TEXT_BG], 400, 100, 200, 15);
			RenderTextOnScreen(meshList[GEO_TEXT], " Play 'Pinball'? - [F]", Color(0, 0, 0), 25, 0, 100);
		}
		else if (nearShop == true)
		{
			RenderMeshOnScreen(meshList[GEO_TEXT_BG], 400, 100, 200, 15);
			RenderTextOnScreen(meshList[GEO_TEXT], " Buy from shop? - [F]", Color(0, 0, 0), 25, 0, 100);
		}
		else if (nearFerrisWheel == true)
		{
			RenderMeshOnScreen(meshList[GEO_TEXT_BG], 400, 100, 200, 15);
			RenderTextOnScreen(meshList[GEO_TEXT], "Ferris Wheel is under maintenance.", Color(0, 0, 0), 25, 0, 100);
		}
		else if (nearMarket == true)
		{
			RenderMeshOnScreen(meshList[GEO_TEXT_BG], 400, 100, 200, 15);
			RenderTextOnScreen(meshList[GEO_TEXT], "Sold out!!", Color(0, 0, 0), 25, 0, 100);
		}
		else if (nearCottonStore == true)
		{
			RenderMeshOnScreen(meshList[GEO_TEXT_BG], 400, 100, 200, 15);
			RenderTextOnScreen(meshList[GEO_TEXT], "Get a Cotton Candy? - [F]", Color(0, 0, 0), 25, 0, 100);
		}
		else if (nearGrocery == true)
		{
			RenderMeshOnScreen(meshList[GEO_TEXT_BG], 400, 100, 200, 15);
			RenderTextOnScreen(meshList[GEO_TEXT], "Get an Apple? - [F]", Color(0, 0, 0), 25, 0, 100);
		}
		else if (nearHitMenSign == true)
		{
			RenderMeshOnScreen(meshList[GEO_TEXT_BG], 400, 100, 200, 15);
			RenderTextOnScreen(meshList[GEO_TEXT], "Read 'HitMen' rules - [F]", Color(0, 0, 0), 25, 0, 100);
		}
		else if (nearPinballSign == true)
		{
			RenderMeshOnScreen(meshList[GEO_TEXT_BG], 400, 100, 200, 15);
			RenderTextOnScreen(meshList[GEO_TEXT], "Read 'Pinball' rules - [F]", Color(0, 0, 0), 25, 0, 100);
		}

	}

	// render rules
	

	// render shop UI
	if (nearShop == true && shopUI == true)
	{
		RenderMeshOnScreen(meshList[GEO_QUAD], 400, 300, 770, 600);
		RenderTextOnScreen(meshList[GEO_TEXT], "Press [X] or walk away to exit.", Color(0, 0, 0), 25, 20, 50);
		if (shopItems == 0)
		{
			RenderMeshOnScreen(meshList[GEO_ZAKU], 400, 300, 150, 200);
			RenderTextOnScreen(meshList[GEO_TEXT], "Purchase 'Zaku Toy'? - [B] ", Color(0, 0, 0), 25, 100, 150);
			RenderTextOnScreen(meshList[GEO_TEXT], "Press Right to see next item", Color(0, 0, 0), 25, 50, 500);
			RenderTextOnScreen(meshList[GEO_TEXT], "Cost: ", Color(0, 0, 0), 25, 125, 100);
			RenderTextOnScreen(meshList[GEO_TEXT], std::to_string(costOfZaku), Color(0, 0, 0), 25, 300, 100);
		}
		else if (shopItems == 1)
		{
			RenderMeshOnScreen(meshList[GEO_BALL], 400, 300, 150, 150);
			RenderTextOnScreen(meshList[GEO_TEXT], "Purchase 'Ball'? - [B]", Color(0, 0, 0), 25, 125, 150);
			RenderTextOnScreen(meshList[GEO_TEXT], "Cost: ", Color(0, 0, 0), 25, 125, 100);
			RenderTextOnScreen(meshList[GEO_TEXT], std::to_string(costOfBall), Color(0, 0, 0), 25, 300, 100);
			RenderTextOnScreen(meshList[GEO_TEXT], "Press Left to see previous item", Color(0, 0, 0), 25, 20, 500);
			RenderTextOnScreen(meshList[GEO_TEXT], "Press Right to see next item", Color(0, 0, 0), 25, 50, 450);
		}
		else if (shopItems == 2)
		{
			RenderMeshOnScreen(meshList[GEO_RUBIK_PNG], 400, 300, 150, 150);
			RenderTextOnScreen(meshList[GEO_TEXT], "Purchase 'Rubik's Cube'? - [B]", Color(0, 0, 0), 25, 50, 150);
			RenderTextOnScreen(meshList[GEO_TEXT], "Press Left to see previous item", Color(0, 0, 0), 25, 20, 500);
			RenderTextOnScreen(meshList[GEO_TEXT], "Press Right to see next item", Color(0, 0, 0), 25, 50, 450);
			RenderTextOnScreen(meshList[GEO_TEXT], "Cost: ", Color(0, 0, 0), 25, 125, 100);
			RenderTextOnScreen(meshList[GEO_TEXT], std::to_string(costOfRubik), Color(0, 0, 0), 25, 300, 100);
		}
		else if (shopItems == 3)
		{

			RenderMeshOnScreen(meshList[GEO_POTION_PNG], 400, 300, 150, 150);
			RenderTextOnScreen(meshList[GEO_TEXT], "Purchase 'Potion of Change'?", Color(0, 0, 0), 25, 25, 150);
			RenderTextOnScreen(meshList[GEO_TEXT], "- [B] ", Color(0, 0, 0), 25, 350, 100);
			RenderTextOnScreen(meshList[GEO_TEXT], "Press Left to see previous item", Color(0, 0, 0), 25, 20, 500);
			RenderTextOnScreen(meshList[GEO_TEXT], "Press Right to see next item", Color(0, 0, 0), 25, 50, 450);
			RenderTextOnScreen(meshList[GEO_TEXT], "Cost: ", Color(0, 0, 0), 25, 125, 100);
			RenderTextOnScreen(meshList[GEO_TEXT], std::to_string(costOfPotion), Color(0, 0, 0), 25, 300, 100);
		}
		else
		{
			// skip
		}

		if (notEnoughCoins == true)
		{
			RenderMeshOnScreen(meshList[GEO_TEXT_BG], 400, 100, 200, 15);
			RenderTextOnScreen(meshList[GEO_TEXT], "Not Enough Coins.", Color(0, 0, 0), 25, 0, 100);
		}
	}

	// render inventory 
	if (ivt == true)
	{
		// x & y = 120 difference
		RenderMeshOnScreen(meshList[GEO_INVENTORY], 400, 300, 600, 600);
		// starting 160, 540
		Item* print;
		int x, y;
		x = 0; 
		y = 0;
		print = inventory->headptr;
		while (print != nullptr)
		{
			if (print->getName() == "Zaku Toy")
			{
				RenderMeshOnScreen(meshList[GEO_ZAKU], 160 + x, 540 - y, 100, 100);
				
			}
			else if (print->getName() == "Ball")
			{
				RenderMeshOnScreen(meshList[GEO_BALL], 160 + x, 540 - y, 100, 100);
			}
			else if (print->getName() == "Rubik's Cube")
			{
				RenderMeshOnScreen(meshList[GEO_RUBIK_PNG], 160 + x, 540 - y, 100, 100);
			}
			else if (print->getName() == "Potion of Change")
			{
				RenderMeshOnScreen(meshList[GEO_POTION_PNG], 160 + x, 540 - y, 100, 100);
			}
			else if (print->getName() == "Cotton Candy")
			{
				RenderMeshOnScreen(meshList[GEO_COTTON_CANDY], 160 + x, 540 - y, 100, 100);
			}
			else if (print->getName() == "Apple")
			{
				RenderMeshOnScreen(meshList[GEO_APPLE], 160 + x, 490 - y, 100, 100);
			}
			RenderTextOnScreen(meshList[GEO_TEXT], std::to_string(print->getAmt()), Color(1, 1, 1), 20, 160 + x, 470 - y);
			if (x < 480 && y < 540)
			{
				x += 120;
			}
			else
			{
				y += 120;
				if (x >= 480)
				{
					x = 0;
				}
				else
				{
					x += 120;
				}
			}
			//std::cout << print->getName() << print->getAmt() << std::endl;
			
			print = print->getNextItem();
		}
		print = nullptr;
		
		RenderTextOnScreen(meshList[GEO_TEXT], "Press [I] to exit.", Color(1, 1, 1), 25, 10, 100);
	}

	RenderMeshOnScreen(meshList[GEO_BLACK_BG], 150, 560, 300, 50);
	RenderTextOnScreen(meshList[GEO_TEXT], " Coins: ", Color(1, 1, 1), 25, 0, 550);
	RenderTextOnScreen(meshList[GEO_TEXT], std::to_string(coins), Color(1, 1, 1), 25, 200, 550);

	if (HMsign == true)
	{
		RenderMeshOnScreen(meshList[GEO_HM_RULES], 400, 300, 600, 600);
		RenderTextOnScreen(meshList[GEO_TEXT], "Press [X] to exit.", Color(0, 0, 0), 25, 20, 50);
	}

	if (PBsign == true)
	{
		RenderMeshOnScreen(meshList[GEO_PB_RULES], 400, 300, 650, 600);
		RenderTextOnScreen(meshList[GEO_TEXT], "Press [X] to exit.", Color(0, 0, 0), 25, 20, 50);
	}

	if (endScreen == true)
	{
		RenderMeshOnScreen(meshList[GEO_BLACK_BG], 400, 300, 1000, 800);
		RenderTextOnScreen(meshList[GEO_TEXT], "You have turn back to a human!", Color(1, 1, 1), 25, 0, 300);
	}
	
	if (Application::getCutScene() == false && Application::getGameStart())
	{
		RenderCutscene();
	}
	
	if (Application::getGameStart() == false)
	{
		RenderMeshOnScreen(meshList[GEO_MENU], 400, 300, 160, 120);
	}
}


void SceneMain::RenderMesh(Mesh* mesh, bool enableLight)
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

void SceneMain::RenderMeshOnScreen(Mesh* mesh, float x, float y, float sizex, float sizey)
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

void SceneMain::RenderText(Mesh* mesh, std::string text, Color color)
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

void SceneMain::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
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


void SceneMain::RenderSkybox()
{
	modelStack.PushMatrix();
	{
		modelStack.Translate(0.f, 0.f, -50.f);
		modelStack.Rotate(180, 0.f, 0.f, 1.f);
		modelStack.Scale(1, 0.5, 1);
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
		modelStack.Scale(1, 0.5, 1);
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
		modelStack.Scale(1, 0.5, 1);
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
		modelStack.Scale(1, 0.5, 1);
		meshList[GEO_LEFT]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
		meshList[GEO_LEFT]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
		meshList[GEO_LEFT]->material.kSpecular.Set(0.9f, 0.9f, 0.9f);
		RenderMesh(meshList[GEO_LEFT], false);
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
		RenderMesh(meshList[GEO_TOP], false);
	}
	modelStack.PopMatrix();
}

void SceneMain::RenderZaku()
{
	// Render the zaku
	//overall transform
	modelStack.PushMatrix(); {
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

void SceneMain::RenderCutscene()
{
	RenderMeshOnScreen(meshList[GEO_BLACK_BG], 400, 300, 1000, 800);
	RenderTextOnScreen(meshList[GEO_TEXT], "'NOOOOOOOOOOOOOOOOOOOO', ", Color(1, 1, 1), 25, 100, 500);
	RenderTextOnScreen(meshList[GEO_TEXT], "You screamed as a evil witch", Color(1, 1, 1), 25, 60, 450);
	RenderTextOnScreen(meshList[GEO_TEXT], "turns you into a ball. ", Color(1, 1, 1), 25, 100, 400);

	RenderTextOnScreen(meshList[GEO_TEXT], "'You shall pay for what", Color(1, 1, 1), 25, 100, 300);
	RenderTextOnScreen(meshList[GEO_TEXT], " you did!', the witch said.", Color(1, 1, 1), 25, 70, 250);
	RenderTextOnScreen(meshList[GEO_TEXT], "'Find a way to turn youself back!'", Color(1, 1, 1), 25, 0, 200);

	RenderTextOnScreen(meshList[GEO_TEXT], "Press [C] to skip.", Color(1, 1, 1), 25, 200, 100);

}

void SceneMain::RenderLight(int lightIndex)
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


void SceneMain::Exit()
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

void SceneMain::HandleKeyPress()
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

	if (KeyboardController::GetInstance()->IsKeyPressed(GLFW_KEY_F))
	{
		if (nearShop == true)
		{
			shopUI = true;
		}
		else
		{
			shopUI = false;
		}

		if (nearCottonStore == true)
		{
			inventory->addItem("Cotton Candy");
		}
		else if (nearGrocery == true) 
		{
			inventory->addItem("Apple");
		}
		
		if (nearHitMenSign == true)
		{
			HMsign = true;
		}
		else
		{
			HMsign = false;
		}

		if (nearPinballSign == true)
		{
			PBsign = true;
		}
		else
		{
			PBsign = false;
		}
	}


	if (KeyboardController::GetInstance()->IsKeyPressed(GLFW_KEY_B))
	{
		if (nearShop == true && shopUI == true )
		{
			if (Player::GetInstance()->getCoins() >= costOfZaku && shopItems == 0)
			{
				//notEnoughCoins = false;
				inventory->addItem("Zaku Toy");
				Player::GetInstance()->coins -= costOfZaku;
			}
			else if (Player::GetInstance()->getCoins() >= costOfBall && shopItems == 1)
			{
				notEnoughCoins = false;
				inventory->addItem("Ball");
				Player::GetInstance()->coins -= costOfBall;
			}
			else if (Player::GetInstance()->getCoins() >= costOfRubik && shopItems == 2)
			{
				//notEnoughCoins = false;
				inventory->addItem("Rubik's Cube");
				Player::GetInstance()->coins -= costOfRubik;
			}
			else if (Player::GetInstance()->getCoins() >= costOfPotion && shopItems == 3)
			{
				//notEnoughCoins = false;
				inventory->addItem("Potion of Change");
				Player::GetInstance()->coins -= costOfPotion;
				endScreen = true;
			}
			else
			{
				notEnoughCoins = true;
			}


		}

	}

	if (KeyboardController::GetInstance()->IsKeyPressed(GLFW_KEY_I))
	{
		if (ivt == true)
		{
			ivt = false;
		}
		else
		{
			ivt = true;
		}
	}


	if (KeyboardController::GetInstance()->IsKeyPressed(GLFW_KEY_RIGHT))
	{
		notEnoughCoins = false;
		if (shopItems == 0)
		{
			shopItems = 1;
		}
		else if (shopItems == 1)
		{
			shopItems = 2;
		}
		else if (shopItems == 2)
		{
			shopItems = 3;
		}
	}

	if (KeyboardController::GetInstance()->IsKeyPressed(GLFW_KEY_LEFT))
	{
		notEnoughCoins = false;
		if (shopItems == 1)
		{
			shopItems = 0;
		}
		else if (shopItems == 2)
		{
			shopItems = 1;
		}
		else if (shopItems == 3)
		{
			shopItems = 2;
		}
	}

	if (KeyboardController::GetInstance()->IsKeyPressed(GLFW_KEY_X))
	{
		if (shopUI == true)
		{
			shopUI = false;
		}
		if (HMsign == true)
		{
			HMsign = false;
		}
		if (PBsign == true)
		{
			PBsign = false;
		}

	}
}
