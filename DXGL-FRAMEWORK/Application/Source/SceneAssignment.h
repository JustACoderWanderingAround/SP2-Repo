#ifndef SCENE_ASSIGNMENT_H
#define SCENE_ASSIGNMENT_H
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
class SceneAssignment : public Scene
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
		GEO_TOUCHSCREEN1,
		GEO_TOUCHSCREEN2,
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
		GEO_DIRTBALL,

		GEO_GENERAL_FLOOR_1,
		GEO_GENERAL_WALL_1,
		GEO_GENERAL_WALL_2,
		GEO_GENERAL_FLOOR_2,
		GEO_GENERAL_FLOOR_5,
		GEO_SECONDARY_WALL_1,

		GEO_PLAYER,

		GEO_CROSSHAIR,

		GEO_CLEANER,

		GEO_ARROW,

		GEO_UI,
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

	SceneAssignment();
	~SceneAssignment();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	void RenderSkybox();
	virtual void Exit();

private:
	void HandleKeyPress();
	void RenderMesh(Mesh* mesh, bool enableLight);
	void RenderMeshOnScreen(Mesh* mesh, float x, float y, float sizex, float sizey);
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderZaku();
	void RenderLight(int lightIndex);
	void RenderControlRoom();
	unsigned m_vertexArrayID;
	Mesh* meshList[NUM_GEOMETRY];

	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];
	GameObject m_player;
	GameObject zakuCleaner;
	std::vector<GameObject*> dirtBalls;
	std::vector<GameObject*> interactables;
	CameraFPS mainFPSCam;
	CameraFPS zakuCam;
	CameraFPS configCam;
	std::vector<CameraFPS> cameraArray;
	//AltAzCamera zakuCam;
	int projType = 1; // fix to 0 for orthographic, 1 for projection
	MatrixStack modelStack, viewStack, projectionStack;
	glm::vec3 door1pos, door2pos;
	static const int NUM_LIGHTS = 5;
	Light light[NUM_LIGHTS];
	bool enableLight;
	float initCamY;
	bool boosting;
	glm::vec3 zakuPos;
	int cameraNum;
	int currInteractable;
	int roomY;
	bool showUI;
	bool doorOpen;
	bool lowered;
	bool secured;
	int strapAngle;
	glm::vec3 zakuCleanerPos;
};

#endif