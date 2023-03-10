#ifndef SCENE_HITMEN_H
#define SCENE_HITMEN_H
#define NUM_CAMERA 2
#include "Scene.h"
#include "Mesh.h"
#include "AltAzCamera.h"
#include "MatrixStack.h"
#include "Light.h"
#include "CameraFPS.h"
#include <vector>
#include "GameObject.h"
#define NUM_INTERACTABLES 1
#define NUM_DIRTBALLS 5
#define NUM_DOORMEN 15
#define NUM_SHELLS 20
#define NUM_AMMO 15
class SceneHitMen : public Scene
{
public:
	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_SPHERE,
		GEO_LEFT,
		GEO_RIGHT,
		GEO_FRONT,
		GEO_BACK,
		GEO_TOP,
		GEO_BOTTOM,
		GEO_CIRCLE,
		GEO_TORUS,
		GEO_CUBE,
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

		GEO_GREY_FLOOR,
		GEO_GUN,
		GEO_TENT,
		GEO_DOORMAN,
		GEO_TABLE,
		GEO_UI,
		GEO_TEXT,
		NUM_GEOMETRY,
	};
	enum class BULLET_TYPE {
		BULLET_SINGLE,
		BULLET_SHOTGUN,
		NUM_BULLETS,
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
	BULLET_TYPE bulletType;
	SceneHitMen();
	~SceneHitMen();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	void RenderSkybox();
	virtual void Exit();
	int score;

private:
	void HandleKeyPress();
	void RenderMesh(Mesh* mesh, bool enableLight);
	void RenderMeshOnScreen(Mesh* mesh, float x, float y, float sizex, float sizey);
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderLight(int lightIndex);
	unsigned m_vertexArrayID;
	Mesh* meshList[NUM_GEOMETRY];

	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];
	GameObject m_player;
	GameObject m_bullet;
	GameObject m_floor;
	GameObject* m_grapeShot[NUM_SHELLS];
	std::vector<GameObject*> m_ammo;
	//std::vector<GameObject*> m_shotGunShell;
	float gunHori;
	float gunVerti;
	std::vector<GameObject*> doorMen;
	std::vector<glm::vec3> doorMenInitPos;
	GameObject m_table1;
	GameObject m_table2;
	GameObject m_table3;
	/*std::vector<GameObject*>*/

	CameraFPS mainFPSCam;
	CameraFPS gunCam;
	CameraFPS configCam;

	std::vector<CameraFPS> cameraArray;
	//AltAzCamera zakuCam;
	int projType = 1; // fix to 0 for orthographic, 1 for projection
	MatrixStack modelStack, viewStack, projectionStack;
	static const int NUM_LIGHTS = 5;
	Light light[NUM_LIGHTS];
	bool enableLight;
	float initCamY;
	glm::vec3 zakuPos;
	int cameraNum;
	int ammo;
	int time;
	double ballTimer;
	float horiView;
	float vertiView;
	bool showUI;
	double elapsedTime;
	double gameTimer;
	double reloadTimer;
	bool reloading;
	int totalAmmo;
	int currBullet;
	bool gameOver;
};

#endif