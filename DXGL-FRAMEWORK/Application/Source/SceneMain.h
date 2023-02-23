#ifndef SCENE_MAIN_H
#define SCENE_MAIN_H
#define NUM_CAMERA 2
#include "Scene.h"
#include "Mesh.h"
#include "AltAzCamera.h"
#include "MatrixStack.h"
#include "Light.h"
#include "CameraFPS.h"
#include <vector>
#include "GameObject.h"
#include "Inventory.h"
#include "Player.h"
#include "SceneHitMen.h"
#include "SceneCanTopple.h"
#include "ScenePinball.h"
#define MAX_FENCE 33
#define MAX_OBJ 5
class SceneMain : public Scene
{
public:
	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_SPHERE,
		GEO_QUAD,
		GEO_LEFT,
		GEO_RIGHT,
		GEO_FRONT,
		GEO_BACK,
		GEO_TOP,
		GEO_BOTTOM,
		GEO_CIRCLE,
		GEO_TORUS,
		GEO_CUBE,
		GEO_FENCE,
		GEO_CRATE,
		GEO_ROAD,
		GEO_ARCH,
		GEO_SIDEWALK,
		GEO_TENT,
		GEO_BLUE_TENT,
		GEO_RED_TENT,
		GEO_GREEN_TENT,
		GEO_MARKET,
		GEO_CANDY_STORE,
		GEO_CANDY_SIGN,
		GEO_PINBALL,
		GEO_GROCERY_TENT,
		GEO_APPLE,
		GEO_TABLE,
		GEO_MOSIN,
		GEO_DOORMAN,
		GEO_CANS,
		GEO_FERRIS_WHEEL,
		GEO_WALL,
		GEO_CAROUSEL,
		GEO_WOODEN_SIGN,
		GEO_LAMP_POST,
		GEO_RUBIKS_CUBE,
		GEO_POTION,
		GEO_ZAKU,
		GEO_INVENTORY,
		GEO_BALL,
		GEO_RUBIK_PNG,
		GEO_POTION_PNG,
		GEO_COTTON_CANDY,
		GEO_BLACK_BG,
		GEO_MENU,

		GEO_SPHERE_BLACK,
		GEO_ZAKU_HEAD,
		GEO_ZAKU_CUBE,
		GEO_ZAKU_CUBE_ALT,
		GEO_ZAKU_SPHERE,
		GEO_GREY_CUBE,
		GEO_ZAKU_CYLINDER,
		GEO_ZAKU_CYLINDER_ALT,
		GEO_GREY_CYLINDER,
		GEO_WOOD_CUBE,
		GEO_AXE_CUBE,
		GEO_FIRE_CUBE,

		GEO_TEXT_BG,
		GEO_TEXT,
		NUM_GEOMETRY,
	};

	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,

		U_LIGHT0_TYPE,
		U_LIGHT0_POSITION,
		U_LIGHT0_COLOR,
		U_LIGHT0_POWER,
		U_LIGHT0_KC,
		U_LIGHT0_KL,
		U_LIGHT0_KQ,
		U_LIGHT0_SPOTDIRECTION,
		U_LIGHT0_COSCUTOFF,
		U_LIGHT0_COSINNER,
		U_LIGHT0_EXPONENT,

		U_LIGHT1_TYPE,
		U_LIGHT1_POSITION,
		U_LIGHT1_COLOR,
		U_LIGHT1_POWER,
		U_LIGHT1_KC,
		U_LIGHT1_KL,
		U_LIGHT1_KQ,
		U_LIGHT1_SPOTDIRECTION,
		U_LIGHT1_COSCUTOFF,
		U_LIGHT1_COSINNER,
		U_LIGHT1_EXPONENT,

		U_LIGHT2_TYPE,
		U_LIGHT2_POSITION,
		U_LIGHT2_COLOR,
		U_LIGHT2_POWER,
		U_LIGHT2_KC,
		U_LIGHT2_KL,
		U_LIGHT2_KQ,
		U_LIGHT2_SPOTDIRECTION,
		U_LIGHT2_COSCUTOFF,
		U_LIGHT2_COSINNER,
		U_LIGHT2_EXPONENT,

		U_LIGHT3_TYPE,
		U_LIGHT3_POSITION,
		U_LIGHT3_COLOR,
		U_LIGHT3_POWER,
		U_LIGHT3_KC,
		U_LIGHT3_KL,
		U_LIGHT3_KQ,
		U_LIGHT3_SPOTDIRECTION,
		U_LIGHT3_COSCUTOFF,
		U_LIGHT3_COSINNER,
		U_LIGHT3_EXPONENT,

		U_LIGHT4_TYPE,
		U_LIGHT4_POSITION,
		U_LIGHT4_COLOR,
		U_LIGHT4_POWER,
		U_LIGHT4_KC,
		U_LIGHT4_KL,
		U_LIGHT4_KQ,
		U_LIGHT4_SPOTDIRECTION,
		U_LIGHT4_COSCUTOFF,
		U_LIGHT4_COSINNER,
		U_LIGHT4_EXPONENT,

		U_NUMLIGHTS,
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,
		U_LIGHTENABLED,
		U_TEXT_ENABLED,
		U_TEXT_COLOR,
		U_TOTAL,
	};

	SceneMain();
	~SceneMain();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	void RenderSkybox();
	virtual void Exit();

	bool nearToppled;
	bool nearPinball;
	bool nearHitMan;
	bool nearShop;
private:
	void HandleKeyPress();
	void RenderMesh(Mesh* mesh, bool enableLight);
	void RenderMeshOnScreen(Mesh* mesh, float x, float y, float sizex, float sizey);
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderLight(int lightIndex);
	void RenderZaku();
	void RenderCutscene();
	unsigned m_vertexArrayID;
	Mesh* meshList[NUM_GEOMETRY];

	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];
	GameObject* m_player;
	GameObject* stallCanBeToppled;
	GameObject* stallPinball;
	GameObject* stallHitMan;
	GameObject* stallShop;
	GameObject* fences[MAX_FENCE];
	GameObject* objs[MAX_OBJ];
	Inventory* inventory;

	CameraFPS mainFPSCam;
	int projType = 1; // fix to 0 for orthographic, 1 for projection
	MatrixStack modelStack, viewStack, projectionStack;
	static const int NUM_LIGHTS = 1;
	Light light[NUM_LIGHTS];
	bool enableLight;

	glm::vec3 oldPlayerPos;

	bool nearFerrisWheel;
	bool nearMarket;
	bool nearCottonStore;
	bool nearGrocery;
	bool nearHitMenSign;
	bool shopUI;
	int shopItems;
	bool ivt;
	
	int costOfZaku, costOfBall, costOfRubik, costOfPotion;
	int coins;
	bool notEnoughCoins;
	bool startCutscene;
	bool endScreen;

};

#endif