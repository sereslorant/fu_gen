#ifndef QUICKHULL_H
#define QUICKHULL_H

#include <glmath.hpp>

/*
 * http://www.flipcode.com/archives/The_Half-Edge_Data_Structure.shtml
 */
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

struct VertexData
{
	vec4 Vertex;
	//
	vec4 TexCoord;
	int SegmentId = -1;
	unsigned int SampleId;
	//
	//int OtherSegmentId = -1;
	//unsigned int OtherSampleId = 0;
	//
	bool Added = false;
};

extern unsigned int QuickhullNumSteps;

void Quickhull(VertexData vertices[],unsigned int num_vertices,MyMesh &convex_hull);

#endif // QUICKHULL_H
