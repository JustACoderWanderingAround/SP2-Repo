#include "Scene1.h"
#include "GL\glew.h"
#include "shader.hpp"
#include "Application.h"
#include "MeshBuilder.h"
#include "Mtx44.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_inverse.hpp>
#include <glm\gtc\matrix_access.hpp>
#include <GLFW/glfw3.h>
using namespace std;

#define time_scale 5
#define x_resistant 1

Scene1::Scene1()
{
	m_obj = NULL;
}

Scene1::~Scene1()
{
}

void Scene1::Init()
{
	//Calculating aspect ratio
	m_worldHeight = 500.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	// Set background color to dark blue
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	//Enable depth buffer and depth testing
	glEnable(GL_DEPTH_TEST);

	//Enable back face culling
	glEnable(GL_CULL_FACE);

	//Default to fill mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	// Load the shader programs
	m_programID = LoadShaders("Shader//TransformVertexShader.vertexshader",
		"Shader//SimpleFragmentShader.fragmentshader");
	glUseProgram(m_programID);

	// Get a handle for our "MVP" uniform
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");

	camera.Init(glm::vec3(0, 0, 1), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	// Init VBO here
	for (int i = 0; i < NUM_GEOMETRY; ++i)
	{
		meshList[i] = nullptr;
	}

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("Axes", 10000.f, 10000.f, 10000.f);
	meshList[GEO_BALL] = MeshBuilder::GenerateSphere("Sphere", Color(1.0f, 1.0f, 1.0f), 10, 10, 1.f);

	// alien (spheres)
	meshList[GEO_ALIEN] = MeshBuilder::GenerateSphere("Alien", Color(1.0f, 1.0f, 0.0f), 10, 10, 1.f);

	m_obj = new GameObject(GameObject::GO_BALL);

	// position set to (half width and 10% of the screen height
	m_obj->pos = glm::vec3(m_worldWidth / 2.0f, m_worldHeight / 10.0f, 0.f);
	m_obj->scale = glm::vec3(10.f, 10.f, 1.f);
	m_obj->vel = glm::vec3(0.f, 0.f, 0.f);
	m_obj->active = false;
	m_obj->mass = 1;

	// loop through the array for the aliens
	for (int i = 0; i < MAX_ALIEN; ++i)
	{
		// allocate memory for each alien
		m_alien[i] = new GameObject(GameObject::GO_ALIEN);

		// randomise the position. only appear on the top half of the screen
		m_alien[i]->pos = glm::vec3( (float)(rand() % (int) m_worldWidth),
									(float)(rand() % (int) (m_worldHeight / 2) + (m_worldHeight / 2)),
									0.f);
		// randomise the size of the alien 
		m_alien[i]->scale = glm::vec3(20.f, 20.f, 1.f);
		// set active. 
		m_alien[i]->active = true;
		m_alien[i]->mass = 2;
	}

	// shifted out multiplier as it's a fixed value. can just calculate during init.
	multiplier = 1.0f / m_obj->mass;


	wh = Application::GetWindowHeight();
	ww = Application::GetWindowWidth();
	mousePos = glm::vec3(x * (m_worldWidth / ww), (wh - y) * (m_worldHeight / wh), 0);
}

void Scene1::Update(double dt)
{
	// Check for key press, you can add more for interaction
	Application::GetCursorPos(&x, &y);
	wh = Application::GetWindowHeight();
	ww = Application::GetWindowWidth();
	mousePos = glm::vec3(x * (m_worldWidth / ww), ((wh - y) * m_worldHeight / wh), 0);
	HandleKeyPress();

	m_obj->fixedUpdate(dt);

	// loop aliens
	for (int j = 0; j < MAX_ALIEN; ++j) {
		// check active (if inactive, it's already been shot)
		if (m_alien[j]->active) {
			if (m_alien[j]->CheckSSCollision(m_obj)) {
				m_alien[j]->CollisionResponse(m_obj);
			}

			m_alien[j]->fixedUpdate(dt);
		}
	}
}
void Scene1::Render()
{
	// Clear color buffer every frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Projection matrix : Orthographic Projection

	// Camera matrix
	viewStack.LoadIdentity();
	viewStack.LookAt(
		camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z
	);
	// Model matrix : an identity matrix (model will be at the origin)
	modelStack.LoadIdentity();

	RenderMesh(meshList[GEO_AXES], false);

}

void Scene1::RenderMesh(Mesh* mesh, bool enableLight)
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

void Scene1::Exit()
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

void Scene1::HandleKeyPress() 
{
	if (Application::IsKeyPressed(0x31))
	{
		// Key press to enable culling
		glEnable(GL_CULL_FACE);
	}
	if (Application::IsKeyPressed(0x32))
	{
		// Key press to disable culling
		glDisable(GL_CULL_FACE);
	}
	if (Application::IsKeyPressed(0x33))
	{
		// Key press to enable fill mode for the polygon
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
	}
	if (Application::IsKeyPressed(0x34))
	{
		// Key press to enable wireframe mode for the polygon
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode
	}
	if (!bRButtonState && Application::IsMousePressed(1)) {
		bRButtonState = true;
		m_obj->active = true;
		m_obj->pos = glm::vec3(mousePos.x, mousePos.y, 0);
		m_obj->vel = glm::vec3(0, 0, 0);
	}
	else if (bRButtonState && !Application::IsMousePressed(1)) {
		bRButtonState = false;
		m_obj->active = true;
		m_obj->vel = (m_obj->pos - mousePos);
	}

	// Spacebar button
	if (Application::IsKeyPressed(0x20))
	{
		if (!UPButton) {
		}
		UPButton = true;
	}
	else UPButton = false;

}
