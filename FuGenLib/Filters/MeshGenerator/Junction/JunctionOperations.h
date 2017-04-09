#ifndef JUNCTION_OPERATIONS_H
#define JUNCTION_OPERATIONS_H

#include <Data/MultiMesh.h>

class JunctionOperations
{
private:
	MyMesh &JunctionMesh;
	//
public:
	//
	void DeleteTriangles();
	void CollapseEdges();
	//
	JunctionOperations(MyMesh &junction_mesh)
		:JunctionMesh(junction_mesh)
	{}
	//
	~JunctionOperations(){}
	/*
	 * End of class
	 */
};

#endif // JUNCTION_OPERATIONS_H