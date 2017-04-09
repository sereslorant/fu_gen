#ifndef QUICKHULL_H
#define QUICKHULL_H

#include <Data/MultiMesh.h>

struct VertexData
{
	vec4 Vertex;
	//
	vec4 TexCoord;
	int SegmentId = -1;
	unsigned int SampleId;
	//
	bool Added = false;
};

void Quickhull(VertexData vertices[],unsigned int num_vertices,MyMesh &convex_hull);

#endif // QUICKHULL_H
