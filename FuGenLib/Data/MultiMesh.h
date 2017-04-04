#ifndef MULTI_MESH_H
#define MULTI_MESH_H

#include <glmath.hpp>

struct Triangle
{
	unsigned int VertexId[3] = {0,0,0};
	unsigned int TexCoordId[3] = {0,0,0};
};

#include <vector>

template<class T_VertexData>
struct Mesh
{
	std::vector<T_VertexData> Vertices;
	std::vector<vec4> TexCoords;
	//
	std::vector<Triangle> Triangles;
	//
	Mesh(unsigned int num_vertices = 0,unsigned int num_texcoords = 0,unsigned int num_triangles = 0)
		:Vertices(num_vertices),TexCoords(num_texcoords),Triangles(num_triangles)
	{}
	//
	~Mesh()
	{}
};

#include "../Utils/Quickhull.h"

#include <list>

struct MultiMesh
{
	std::vector<Mesh<vec4> > Segments;
	std::list<MyMesh> JunctionMeshes;
	//
	MultiMesh()
	{}
	//
	~MultiMesh()
	{}
};

#endif // MULTI_MESH_H
