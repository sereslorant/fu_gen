
#include "QhQuickhull.h"

#include <vector>
#include <list>

#include <iostream>

#include <chrono>


/*
 * Quickhull: http://thomasdiewald.com/blog/?p=1888
 */

enum EAxis
{
	AXIS_X,
	AXIS_Y,
	AXIS_Z,
};

struct QhExtremeVertedId
{
	unsigned int MinX = 0;
	unsigned int MaxX = 0;
	unsigned int MinY = 0;
	unsigned int MaxY = 0;
	unsigned int MinZ = 0;
	unsigned int MaxZ = 0;
	
	unsigned int GetMin(EAxis Axis)
	{
		switch(Axis)
		{
		case AXIS_X:
			return MinX;
		case AXIS_Y:
			return MinY;
		case AXIS_Z:
			return MinZ;
		}
	}
	
	unsigned int GetMax(EAxis Axis)
	{
		switch(Axis)
		{
		case AXIS_X:
			return MaxX;
		case AXIS_Y:
			return MaxY;
		case AXIS_Z:
			return MaxZ;
		}
	}
	
	void GetRemainingExtremeVertices(EAxis Axis,unsigned int remaining_extreme_vertices[])
	{
		switch(Axis)
		{
		case AXIS_X:
			remaining_extreme_vertices[0] = MaxY;
			remaining_extreme_vertices[1] = MinY;
			remaining_extreme_vertices[2] = MaxZ;
			remaining_extreme_vertices[3] = MinZ;
			break;
		case AXIS_Y:
			remaining_extreme_vertices[0] = MaxX;
			remaining_extreme_vertices[1] = MinX;
			remaining_extreme_vertices[2] = MaxZ;
			remaining_extreme_vertices[3] = MinZ;
			break;
		case AXIS_Z:
			remaining_extreme_vertices[0] = MaxY;
			remaining_extreme_vertices[1] = MinY;
			remaining_extreme_vertices[2] = MaxX;
			remaining_extreme_vertices[3] = MinX;
			break;
		}
	}
};

void QhFindExtremeVertices(vec4 vertices[],unsigned int num_vertices,QhExtremeVertedId &ExtremeVertexId)
{
	for(unsigned int i=0;i < num_vertices;i++)
	{
		if(vertices[i][0] > vertices[ExtremeVertexId.MinX][0])
			{ExtremeVertexId.MinX = i;}
		if(vertices[i][0] < vertices[ExtremeVertexId.MaxX][0])
			{ExtremeVertexId.MaxX = i;}

		if(vertices[i][1] > vertices[ExtremeVertexId.MinY][1])
			{ExtremeVertexId.MinY = i;}
		if(vertices[i][1] < vertices[ExtremeVertexId.MaxY][1])
			{ExtremeVertexId.MaxY = i;}

		if(vertices[i][2] > vertices[ExtremeVertexId.MinZ][2])
			{ExtremeVertexId.MinZ = i;}
		if(vertices[i][2] < vertices[ExtremeVertexId.MaxZ][2])
			{ExtremeVertexId.MaxZ = i;}
	}
}

EAxis QhGetMaxExtremeAxis(vec4 vertices[],unsigned int num_vertices,QhExtremeVertedId &ExtremeVertexId)
{
	float DistX = vertices[ExtremeVertexId.MaxX][0]-vertices[ExtremeVertexId.MinX][0];
	float DistY = vertices[ExtremeVertexId.MaxY][1]-vertices[ExtremeVertexId.MinY][1];
	float DistZ = vertices[ExtremeVertexId.MaxZ][2]-vertices[ExtremeVertexId.MinZ][2];

	EAxis Puszcsy = AXIS_X;
	if(DistY > DistX)
		{Puszcsy = AXIS_Y;}

	if(Puszcsy == AXIS_Y)
	{
		if(DistZ > DistY)
			{Puszcsy = AXIS_Z;}
	}
	else
	{
		if(DistZ > DistX)
			{Puszcsy = AXIS_Z;}
	}
	
	return Puszcsy;
}

unsigned int QhFindFurthestFromLine(vec4 vertices[],const vec4 &line_point,const vec4 &line_dir,unsigned int extreme_vertex_ids[4])
{
	unsigned int MaxId = 0;
	float MaxLength = 0;
	for(unsigned int i=0;i < 4;i++)
	{
		vec4 p = vertices[extreme_vertex_ids[i]] - line_point;
		p = p - dot(p,line_dir)*line_dir;
		//
		float Length = length(p);
		if(Length > MaxLength)
		{
			MaxId = extreme_vertex_ids[i];
			MaxLength = Length;
		}
	}
	//
	return MaxId;
}

void QhEraseFurthestFromLine(unsigned int extreme_verex_ids[4],unsigned int furthest_id)
{
	unsigned int j=0;
	for(int i=0;i < 4;i++)
	{
		if(i == furthest_id)
			{continue;}
		extreme_verex_ids[j] = extreme_verex_ids[i];
		j++;
	}
}

vec4 QhGetNormal(const vec4 &v0,const vec4 &v1,const vec4 &v2)
{
	vec4 Cross = cross(v1 - v0,v2 - v0);
	Cross = normalize(Cross);
	//
	return Cross;
}

unsigned int QhFindFurthestFromTriangle(vec4 vertices[],unsigned int extreme_triangle[3],unsigned int extreme_verex_ids[3])
{
	vec4 Cross = QhGetNormal(vertices[extreme_triangle[0]],vertices[extreme_triangle[1]],vertices[extreme_triangle[2]]);
	//
	unsigned int MaxId = 0;
	float MaxSignedLength;
	float MaxLength = 0.0;
	for(unsigned int i=0;i < 3;i++)
	{
		float SignedLength = dot(vertices[extreme_verex_ids[i]] - vertices[extreme_triangle[0]],Cross);
		float Length = std::abs(SignedLength);
		if(Length > MaxLength)
		{
			MaxId = extreme_verex_ids[i];
			MaxSignedLength = SignedLength;
			MaxLength = Length;
		}
	}
	//
	if(!(MaxSignedLength < 0.0))
	{
		unsigned int Tmp = extreme_triangle[1];
		extreme_triangle[1] = extreme_triangle[2];
		extreme_triangle[2] = Tmp;
	}
	//
	return MaxId;
}

/*
 * Building initial Half-Edge
 */

void QhCreateVertices(QhVertex *vertices[4],unsigned int selected_points[4],QhMesh &convex_hull_mesh)
{
	convex_hull_mesh.Vertices.emplace_back(selected_points[0]);
	vertices[0] = &convex_hull_mesh.Vertices.back();
	convex_hull_mesh.Vertices.emplace_back(selected_points[1]);
	vertices[1] = &convex_hull_mesh.Vertices.back();
	convex_hull_mesh.Vertices.emplace_back(selected_points[2]);
	vertices[2] = &convex_hull_mesh.Vertices.back();
	convex_hull_mesh.Vertices.emplace_back(selected_points[3]);
	vertices[3] = &convex_hull_mesh.Vertices.back();
}

void QhCreateBaseTriangle(QhVertex *vertices[4],QhHalfEdge *tri0_borders[3],QhFace *triangles[4],QhMesh &convex_hull_mesh)
{
	convex_hull_mesh.HalfEdges.emplace_back();
	tri0_borders[0] = &convex_hull_mesh.HalfEdges.back();
	tri0_borders[0]->BeginVertex = vertices[0];
	vertices[0]->OneEmanatingEdge = tri0_borders[0];
	convex_hull_mesh.HalfEdges.emplace_back();
	tri0_borders[1] = &convex_hull_mesh.HalfEdges.back();
	tri0_borders[1]->BeginVertex = vertices[1];
	vertices[1]->OneEmanatingEdge = tri0_borders[1];
	convex_hull_mesh.HalfEdges.emplace_back();
	tri0_borders[2] = &convex_hull_mesh.HalfEdges.back();
	tri0_borders[2]->BeginVertex = vertices[2];
	vertices[2]->OneEmanatingEdge = tri0_borders[2];
	//
	convex_hull_mesh.Faces.emplace_back();
	triangles[0] = &convex_hull_mesh.Faces.back();
	//
	QhSetBorderLinks(tri0_borders,triangles[0]);
}

void QhCreateRemainingTriangles(QhVertex *vertices[4],QhHalfEdge *tri0_borders[3],QhFace *triangles[4],QhMesh &convex_hull_mesh)
{
	QhHalfEdge *Tri1Borders[3];
	convex_hull_mesh.HalfEdges.emplace_back();
	Tri1Borders[0] = &convex_hull_mesh.HalfEdges.back();
	Tri1Borders[0]->BeginVertex = vertices[1];
	convex_hull_mesh.HalfEdges.emplace_back();
	Tri1Borders[1] = &convex_hull_mesh.HalfEdges.back();
	Tri1Borders[1]->BeginVertex = vertices[0];
	convex_hull_mesh.HalfEdges.emplace_back();
	Tri1Borders[2] = &convex_hull_mesh.HalfEdges.back();
	Tri1Borders[2]->BeginVertex = vertices[3];
	vertices[3]->OneEmanatingEdge = Tri1Borders[2];
	//
	//Tri1Borders[0]->Pair = tri0_borders[0];
	//tri0_borders[0]->Pair = Tri1Borders[0];
	//
	convex_hull_mesh.Faces.emplace_back();
	triangles[1] = &convex_hull_mesh.Faces.back();
	QhSetBorderLinks(Tri1Borders,triangles[1]);
	//
	QhHalfEdge *Tri2Borders[3];
	convex_hull_mesh.HalfEdges.emplace_back();
	Tri2Borders[0] = &convex_hull_mesh.HalfEdges.back();
	Tri2Borders[0]->BeginVertex = vertices[3];
	convex_hull_mesh.HalfEdges.emplace_back();
	Tri2Borders[1] = &convex_hull_mesh.HalfEdges.back();
	Tri2Borders[1]->BeginVertex = vertices[0];
	convex_hull_mesh.HalfEdges.emplace_back();
	Tri2Borders[2] = &convex_hull_mesh.HalfEdges.back();
	Tri2Borders[2]->BeginVertex = vertices[2];
	//
	//Tri1Borders[1]->Pair = Tri2Borders[0];
	//Tri2Borders[0]->Pair = Tri1Borders[1];
	//
	//tri0_borders[2]->Pair = Tri2Borders[1];
	//Tri2Borders[1]->Pair = tri0_borders[2];
	//
	convex_hull_mesh.Faces.emplace_back();
	triangles[2] = &convex_hull_mesh.Faces.back();
	QhSetBorderLinks(Tri2Borders,triangles[2]);
	//
	QhHalfEdge *Tri3Borders[3];
	convex_hull_mesh.HalfEdges.emplace_back();
	Tri3Borders[0] = &convex_hull_mesh.HalfEdges.back();
	Tri3Borders[0]->BeginVertex = vertices[3];
	convex_hull_mesh.HalfEdges.emplace_back();
	Tri3Borders[1] = &convex_hull_mesh.HalfEdges.back();
	Tri3Borders[1]->BeginVertex = vertices[2];
	convex_hull_mesh.HalfEdges.emplace_back();
	Tri3Borders[2] = &convex_hull_mesh.HalfEdges.back();
	Tri3Borders[2]->BeginVertex = vertices[1];
	//
	//Tri3Borders[0]->Pair = Tri2Borders[2];
	//Tri2Borders[2]->Pair = Tri3Borders[0];
	//
	//Tri3Borders[1]->Pair = tri0_borders[1];
	//tri0_borders[1]->Pair = Tri3Borders[1];
	//
	//Tri3Borders[2]->Pair = Tri1Borders[2];
	//Tri1Borders[2]->Pair = Tri3Borders[2];
	//
	convex_hull_mesh.Faces.emplace_back();
	triangles[3] = &convex_hull_mesh.Faces.back();
	QhSetBorderLinks(Tri3Borders,triangles[3]);
}

void QhQuickhullInit(vec4 vertices[],unsigned int num_vertices,std::vector<bool> &vertex_added,QhMesh &convex_hull_mesh)
{
	QhExtremeVertedId ExtremeVertexId;
	QhFindExtremeVertices(vertices,num_vertices,ExtremeVertexId);
	//
	EAxis MaxExtremeAxis = QhGetMaxExtremeAxis(vertices,num_vertices,ExtremeVertexId);
	//
	unsigned int SelectedPoints[4];
	SelectedPoints[0] = ExtremeVertexId.GetMax(MaxExtremeAxis);
	SelectedPoints[1] = ExtremeVertexId.GetMin(MaxExtremeAxis);
	//
	unsigned int RemainingExtremeVertices[4];
	ExtremeVertexId.GetRemainingExtremeVertices(MaxExtremeAxis,RemainingExtremeVertices);
	//
	vec4 BaselinePoint	= vertices[SelectedPoints[0]];
	vec4 BaselineDir	= normalize(vertices[SelectedPoints[1]] - vertices[SelectedPoints[0]]);
	//
	SelectedPoints[2] = QhFindFurthestFromLine(vertices,BaselinePoint,BaselineDir,RemainingExtremeVertices);
	QhEraseFurthestFromLine(RemainingExtremeVertices,SelectedPoints[2]);
	//
	SelectedPoints[3] = QhFindFurthestFromTriangle(vertices,SelectedPoints,RemainingExtremeVertices);
	//
	vertex_added[SelectedPoints[0]] = true;
	vertex_added[SelectedPoints[1]] = true;
	vertex_added[SelectedPoints[2]] = true;
	vertex_added[SelectedPoints[3]] = true;
	//
	//convex_hull.push_back({SelectedPoints[0],SelectedPoints[1],SelectedPoints[2]});
	//convex_hull.push_back({SelectedPoints[0],SelectedPoints[3],SelectedPoints[1]});
	//convex_hull.push_back({SelectedPoints[1],SelectedPoints[3],SelectedPoints[2]});
	//convex_hull.push_back({SelectedPoints[2],SelectedPoints[3],SelectedPoints[0]});
	//
	//convex_hull.push_back({SelectedPoints[0],SelectedPoints[2],SelectedPoints[1]});
	//convex_hull.push_back({SelectedPoints[0],SelectedPoints[1],SelectedPoints[3]});
	//convex_hull.push_back({SelectedPoints[1],SelectedPoints[2],SelectedPoints[3]});
	//convex_hull.push_back({SelectedPoints[2],SelectedPoints[0],SelectedPoints[3]});
	//
	QhVertex *Vertices[4];
	QhFace *Triangles[4];
	QhHalfEdge *Borders[3];
	QhCreateVertices(Vertices,SelectedPoints,convex_hull_mesh);
	QhCreateBaseTriangle(Vertices,Borders,Triangles,convex_hull_mesh);
	QhCreateRemainingTriangles(Vertices,Borders,Triangles,convex_hull_mesh);
	
	std::list<QhFace *> NewTriangles = {Triangles[0],Triangles[1],Triangles[2],Triangles[3]};
	QhConnectTriangleHalfedges(NewTriangles);
}

vec4 QhGetNormal(vec4 vertices[],const QhFace &face)
{
	unsigned int VertexIds[3];
	QhGetTriangleIds(face,VertexIds);
	
	return -1.0 * QhGetNormal(vertices[VertexIds[0]],vertices[VertexIds[1]],vertices[VertexIds[2]]);
}

constexpr float EPSILON = 1e-4;

unsigned int QhFindFurthestFromTriangle(vec4 vertices[],unsigned int num_vertices,std::vector<bool> &vertex_added,const vec4 &triangle_point,const vec4 &triangle_normal)
{
	bool VertexFound = false;

	//auto Before = std::chrono::steady_clock::now();
	unsigned int MaxId = 0;
	float MaxLength = 0.0;
	for(unsigned int i=0;i < num_vertices;i++)
	{
		if(vertex_added[i])
			{continue;}
		
		float Length = dot(triangle_normal,triangle_point - vertices[i]);

		if(Length > MaxLength)
		{
			MaxId = i;
			MaxLength = Length;

			VertexFound = true;
		}
	}
	//auto After = std::chrono::steady_clock::now();
	//auto Difference = After - Before;
	//std::cout << "Find vertex time: " << std::chrono::duration<double,std::micro>(Difference).count() << "\n";
	
	if(!VertexFound)
	{
		return num_vertices;
	}
	
	return MaxId;
}

bool QhIsVisible(vec4 vertices[],unsigned int max_id,QhFace &triangle)
{
	//std::cout << "Check triangle visible " << &triangle << std::endl;
	vec4 OneVertex = vertices[triangle.OneBorderingEdge->BeginVertex->VertexId];

	vec4 Normal = QhGetNormal(vertices,triangle);
	vec4 NormalizedDir = normalize(OneVertex - vertices[max_id]);
	float Dot = dot(Normal,NormalizedDir);

	if(Dot > EPSILON)
	{
		return true;
	}
	
	return false;
}

void QhDeleteVisibleTriangles(vec4 vertices[],QhVertex &new_vertex,QhFace &one_visible,std::list<QhFace *> &new_triangles,QhMesh &convex_hull/*,unsigned int recursion_depth = 1*/)
{
	//std::cout << "Current visible face: " << &one_visible << std::endl;
	//std::cout << "Recursion depth: " << recursion_depth << std::endl;
	QhHalfEdge *AdjacentEdges[3];
	QhGetAdjacentHalfEdges(one_visible,AdjacentEdges);
	QhHalfEdge *BorderingEdges[3];
	QhGetBorderingHalfEdges(one_visible,BorderingEdges);
	//
	//convex_hull.Faces.remove(one_visible);
	one_visible.Delete();
	//
	for(int i=0;i < 3;i++)
	{
		if(AdjacentEdges[i]->IsDeleted())
		{continue;}
		
		if(!(AdjacentEdges[i]->BorderedFace->IsDeleted()) && QhIsVisible(vertices,new_vertex.VertexId,*AdjacentEdges[i]->BorderedFace))
		{
			AdjacentEdges[i]->Delete();
			AdjacentEdges[i]->Pair->Delete();
			QhDeleteVisibleTriangles(vertices,new_vertex,*AdjacentEdges[i]->BorderedFace,new_triangles,convex_hull/*,recursion_depth + 1*/);
		}
		else
		{
			QhHalfEdge *NewTriangleEdges[3];
			NewTriangleEdges[0] = BorderingEdges[i];
			convex_hull.HalfEdges.emplace_back();
			NewTriangleEdges[1] = &convex_hull.HalfEdges.back();
			NewTriangleEdges[1]->BeginVertex = BorderingEdges[i]->NextHalfEdge->BeginVertex;
			convex_hull.HalfEdges.emplace_back();
			NewTriangleEdges[2] = &convex_hull.HalfEdges.back();
			NewTriangleEdges[2]->BeginVertex = &new_vertex;
			//
			convex_hull.Faces.emplace_back();
			QhFace *NewTriangle = &convex_hull.Faces.back();
			QhSetBorderLinks(NewTriangleEdges,NewTriangle);
			//
			new_triangles.push_back(NewTriangle);
		}
	}
}

#define STACK_IMPL

bool QhQuickhullIterate(vec4 vertices[],unsigned int num_vertices,std::vector<bool> &vertex_added,QhFace &triangle,QhMesh &convex_hull
#ifdef STACK_IMPL
						,std::list<QhFace *> &triangle_stack
#endif
)
{
	//auto Before = std::chrono::steady_clock::now();
	
	vec4 TrianglePoint = vertices[triangle.OneBorderingEdge->BeginVertex->VertexId];
	vec4 TriangleNormal = QhGetNormal(vertices,triangle);
	
	//auto After = std::chrono::steady_clock::now();
	//auto Difference = After - Before;
	//std::cout << "Prepare triangle time: " << std::chrono::duration<double,std::micro>(Difference).count() << "\n";
	
	//auto Before = std::chrono::steady_clock::now();
	
	unsigned int MaxId = QhFindFurthestFromTriangle(vertices,num_vertices,vertex_added,TrianglePoint,TriangleNormal);
	if(MaxId == num_vertices)
	{
		return false;
	}
	
	//auto After = std::chrono::steady_clock::now();
	//auto Difference = After - Before;
	//std::cout << "Find farthest time: " << std::chrono::duration<double,std::micro>(Difference).count() << "\n";

	//std::cout << "Farthest vertex: " << vertices[MaxId][0] << ";" << vertices[MaxId][1] << ";" << vertices[MaxId][2] << "\n";
	
	//Before = std::chrono::steady_clock::now();
	convex_hull.Vertices.emplace_back(MaxId);
	QhVertex &NewVertex = convex_hull.Vertices.back();
	vertex_added[MaxId] = true;
	
	std::list<QhFace *> NewTriangles;
	
	//std::cout << "Deleting triangles" << std::endl;
	
	//auto Before = std::chrono::steady_clock::now();
	
	//Before = std::chrono::steady_clock::now();
	
	QhDeleteVisibleTriangles(vertices,NewVertex,triangle,NewTriangles,convex_hull);
	
	
	//After = std::chrono::steady_clock::now();
	//Difference = After - Before;
	//std::cout << "Delete triangles time: " << std::chrono::duration<double,std::micro>(Difference).count() << "\n";
	
	//std::cout << "Amount of generated triangles: " << NewTriangles.size() << std::endl;
	
	//Before = std::chrono::steady_clock::now();
	
	QhConnectTriangleHalfedges(NewTriangles);
#ifdef STACK_IMPL
	triangle_stack.splice(triangle_stack.end(),NewTriangles);
#endif
	//After = std::chrono::steady_clock::now();
	//Difference = After - Before;
	//std::cout << "Connect triangles time: " << std::chrono::duration<double,std::micro>(Difference).count() << "\n";
	
	//std::cout << "Collecting garbage" << std::endl;
	
	//auto Before = std::chrono::steady_clock::now();
#ifndef STACK_IMPL
	convex_hull.DeleteDeletedFaces();
#endif
	//auto After = std::chrono::steady_clock::now();
	//auto Difference = After - Before;
	//std::cout << "Garbage collection time: " << std::chrono::duration<double,std::micro>(Difference).count() << "\n";
	
	return true;
}

unsigned int MaxIterations = 0;


void QhQuickhull(vec4 vertices[],unsigned int num_vertices,QhMesh &result)
{
	//std::cout << "\n\nQuickhull begin:" << std::endl;
	std::vector<bool> VertexAdded(num_vertices);
	QhQuickhullInit(vertices,num_vertices,VertexAdded,result);
	//
	//unsigned int NumIterations = 0;
	//
	#ifdef STACK_IMPL
	////////////////////////////////////////////////////////////////////////////////
	std::list<QhFace *> TriangleStack;
	for(QhFace &Triangle : result.Faces)
	{TriangleStack.push_back(&Triangle);}
	
	while(TriangleStack.size() != 0)
	{
		//if(NumIterations == MaxIterations)
		//{break;}
		//
		QhFace *T = TriangleStack.front();
		TriangleStack.pop_front();
		//
		//auto Before = std::chrono::steady_clock::now();
		if(!T->IsDeleted())
		{
			QhQuickhullIterate(vertices,num_vertices,VertexAdded,*T,result,TriangleStack);
		}
		//auto After = std::chrono::steady_clock::now();
		//auto Difference = After - Before;
		//std::cout << "One iteration time: " << std::chrono::duration<double,std::micro>(Difference).count() << std::endl;
		//
		//NumIterations++;
		//std::cout << "NumIterations: " << NumIterations << std::endl;
	}
	//
	result.DeleteDeletedFaces();
	////////////////////////////////////////////////////////////////////////////////
	#else
	////////////////////////////////////////////////////////////////////////////////
	bool Restart = true;
	while(Restart)
	{
		//if(NumIterations == MaxIterations)
		//{break;}
		//
		Restart = false;
		auto T_begin = result.Faces.begin();
		//
		//auto Before = std::chrono::steady_clock::now();
		for(auto T = T_begin;T != result.Faces.end();T++)
		{
			if(T->IsDeleted())
			{
				continue;
			}
			//
			if(QhQuickhullIterate(vertices,num_vertices,VertexAdded,*T,result))
			{
				Restart = true;
				//Restart = false;
				break;
			}
			//
			T_begin = T;
		}
		//auto After = std::chrono::steady_clock::now();
		//auto Difference = After - Before;
		//std::cout << "One iteration time: " << std::chrono::duration<double,std::micro>(Difference).count() << std::endl;
		//
		//NumIterations++;
		//std::cout << "NumIterations: " << NumIterations << std::endl;
	}
	////////////////////////////////////////////////////////////////////////////////
	#endif
}