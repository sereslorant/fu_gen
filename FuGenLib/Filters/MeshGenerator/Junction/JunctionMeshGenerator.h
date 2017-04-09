#ifndef JUNCTION_MESH_GENERATOR_H
#define JUNCTION_MESH_GENERATOR_H

#include <Data/MultiMesh.h>

class JunctionMeshGenerator
{
private:
	MyMesh &JunctionMesh;
	float DeltaUV;
	//
public:
	//
	void ParametrizeHalfedge();
	//
	JunctionMeshGenerator(MyMesh &junction_mesh,float delta_uv)
		:JunctionMesh(junction_mesh),DeltaUV(delta_uv)
	{}
	//
	~JunctionMeshGenerator()
	{}
	/*
	 * End of class
	 */
};

#endif // JUNCTION_MESH_GENERATOR_H