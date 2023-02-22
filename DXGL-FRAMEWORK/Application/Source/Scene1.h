#ifndef SCENE_1_H
#define SCENE_1_H

#include "GameObject.h"
#include "Vector3.h"
#include "Scene.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Camera.h"

#define MAX_ALIEN 5		// maximum aliens to have in the game

class Scene1 : public Scene
{
public:
	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_TEXT,
		GEO_FLOOR,
		GEO_BALL,
		GEO_CUBE,
		GEO_BULLET,
		GEO_BALLER,
		GEO_ALIEN, // to create alien mesh
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
		U_NUMLIGHTS,
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,
		U_LIGHTENABLED,
		U_TEXT_ENABLED,
		U_TEXT_COLOR,
		U_TOTAL,
	};

	Scene1();
	~Scene1();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

private:
	void HandleKeyPress();
	void RenderMesh(Mesh* mesh, bool enableLight);

	unsigned m_vertexArrayID;
	Mesh* meshList[NUM_GEOMETRY];

	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	float m_worldWidth;
	float m_worldHeight;
	GameObject* m_obj;
	GameObject* m_alien[MAX_ALIEN];    // array to store the aliens
	bool bRButtonState;
	Camera camera;

	MatrixStack modelStack;
	MatrixStack viewStack;
	MatrixStack projectionStack;

	//Vector3 gravity;
	bool slowdown;
	bool UPButton;
	float multiplier, distX, distY;
	double x, y, ww, wh;
	glm::vec3 mousePos;
	glm::vec3 A, B, AB, BE, AE;
	float dist;
};

#endif