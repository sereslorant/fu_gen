#ifndef MULTI_MESH_H
#define MULTI_MESH_H

#include <glmath.hpp>

#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>

struct MyMeshTraits : public OpenMesh::DefaultTraits
{
	VertexAttributes(OpenMesh::Attributes::Status);
	FaceAttributes(OpenMesh::Attributes::Status);
	EdgeAttributes(OpenMesh::Attributes::Status);
	//
	VertexTraits
	{
	public:
		vec4 TexCoord;
		int SegmentId = -1;
		unsigned int SampleId;
		//
		vec4 OtherTexCoord;
		int OtherSegmentId = -1;
		unsigned int OtherSampleId = 0;
		//
		bool Collapsed = false;
	};
};

typedef OpenMesh::TriMesh_ArrayKernelT<MyMeshTraits> MyMesh;

#include <vector>

template<class T_VertexData>
struct Mesh
{
	std::vector<T_VertexData> Vertices;
	std::vector<vec4> TexCoords;
	//
	struct Triangle
	{
		unsigned int VertexId[3] = {0,0,0};
		unsigned int TexCoordId[3] = {0,0,0};
	};
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
