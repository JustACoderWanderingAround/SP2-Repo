#ifndef MESH_BUILDER_H
#define MESH_BUILDER_H

#include "Mesh.h"
#include "Vertex.h"
#include "glm/gtc/constants.hpp"
#include "LoadOBJ.h"

/******************************************************************************/
/*!
		Class MeshBuilder:
\brief	Provides methods to generate mesh of different shapes
*/
/******************************************************************************/
class MeshBuilder
{
public:
	static Mesh* GenerateAxes(const std::string &meshName, float lengthX, float lengthY, float lengthZ);
	static Mesh* GenerateCube(const std::string& meshName, Color color, float length = 1.f);
	static Mesh* GenerateQuad(const std::string& meshName, Color color, float length = 1.f, bool repeated = false);
	static Mesh* GenerateCircle(const std::string& meshName, Color color, float radius = 1.0f, int numSlice = 360);
	static Mesh* GenerateSphere(const std::string& meshName, Color color, float radius = 1.0f, int numSlice = 360, int numStack = 360);
	static Mesh* GenerateDome(const std::string& meshName, Color color, float radius = 1.0f, int numStack = 360, int numSlice = 360);
	static Mesh* GenerateTorus(const std::string& meshName, Color color, float innerrad = 1.0f, float outerrad = 1.0f,int numSlice = 360, int numStack = 360);
	static Mesh* GenerateCylinder(const std::string& meshName, Color color, unsigned height, unsigned sliceCount, float radius = 1.f);
	static Mesh* GenerateOBJ(const std::string& meshName, const std::string& file_path);
	static Mesh* GenerateOBJMTL(const std::string& meshName, const std::string& file_path, const std::string& mtl_path);
	static Mesh* GenerateText(const std::string& meshName, unsigned numRow, unsigned numCol);
};

#endif