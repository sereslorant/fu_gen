
#include "Quickhull.h"

#include <list>
#include <iostream>

struct VertexHandleArrayElement
{
	//bool Valid = false;

	unsigned int Index;
	MyMesh::VertexHandle Handle;
};

struct Triangle
{
	unsigned int V[3] = {0,0,0};
};

unsigned int QuickhullFindMaxFromLine(VertexData vertices[],const vec4 &line_point,const vec4 &line_dir,unsigned int ids[],unsigned int num_ids)
{
	unsigned int MaxId = 0;
	float MaxLen = 0;
	for(unsigned int i=0;i < num_ids;i++)
	{
		vec4 p;
		p = vertices[ids[i]].Vertex - line_point;
		p -= dot(p,line_dir)*line_dir;

		float Length = length(p);
		if(Length > MaxLen)
		{
			MaxLen = Length;
			MaxId = i;
		}
	}

	return MaxId;
}

void QuickhullEraseMaxId(unsigned int ids[],unsigned int num_ids,unsigned int max_id)
{
	unsigned int j=0;
	for(int i=0;i < num_ids;i++)
	{
		if(i == max_id){continue;}
		ids[j] = ids[i];
		j++;
	}
}

vec4 GetNormal(VertexData vertices[],const Triangle &triangle)
{
	vec4 Cross = cross(vertices[triangle.V[1]].Vertex - vertices[triangle.V[0]].Vertex,vertices[triangle.V[2]].Vertex - vertices[triangle.V[0]].Vertex);
	Cross = normalize(Cross);

	return Cross;
}

vec4 GetNormal(MyMesh &convex_hull,MyMesh::FaceHandle &triangle)
{
    MyMesh::Point Normal = convex_hull.calc_face_normal(triangle);

    return -1.0f*vec4(Normal[0],Normal[1],Normal[2]);
}

unsigned int QuickhullFindMaxFromTriangle(VertexData vertices[],const Triangle &triangle,unsigned int ids[],unsigned int num_ids)
{
	vec4 Cross = GetNormal(vertices,triangle);

	unsigned int MaxId = 0;
	float MaxLength = 0.0;
	for(unsigned int i=0;i < num_ids;i++)
	{
		float Length = dot(vertices[ids[i]].Vertex - vertices[triangle.V[0]].Vertex,Cross);
		if(Length > MaxLength)
		{
			MaxId = i;
			MaxLength = Length;
		}
	}

	return ids[MaxId];
}

void QuickhullInit(VertexData vertices[],unsigned int num_vertices,std::vector<VertexHandleArrayElement> &vertex_handles,MyMesh &convex_hull)
{
	unsigned int MinX = 0;
	unsigned int MaxX = 0;
	unsigned int MinY = 0;
	unsigned int MaxY = 0;
	unsigned int MinZ = 0;
	unsigned int MaxZ = 0;

	for(unsigned int i=0;i < num_vertices;i++)
	{
		if(vertices[i].Vertex[0] > vertices[MinX].Vertex[0]){MinX = i;}
		if(vertices[i].Vertex[0] < vertices[MaxX].Vertex[0]){MaxX = i;}

		if(vertices[i].Vertex[1] > vertices[MinY].Vertex[1]){MinY = i;}
		if(vertices[i].Vertex[1] < vertices[MaxY].Vertex[1]){MaxY = i;}

		if(vertices[i].Vertex[2] > vertices[MinZ].Vertex[2]){MinZ = i;}
		if(vertices[i].Vertex[2] < vertices[MaxZ].Vertex[2]){MaxZ = i;}
	}

	float DistX = vertices[MaxX].Vertex[0]-vertices[MinX].Vertex[0];
	float DistY = vertices[MaxY].Vertex[1]-vertices[MinY].Vertex[1];
	float DistZ = vertices[MaxZ].Vertex[2]-vertices[MinZ].Vertex[2];

	unsigned int Puszcsy = 0;
	if(DistY > DistX){Puszcsy = 1;}

	if(Puszcsy == 1)
	{
		if(DistZ > DistY){Puszcsy = 2;}
	}
	else
	{
		if(DistZ > DistX){Puszcsy = 2;}
	}

	vec4 BaselinePoint;
	vec4 BaselineDir;

	unsigned int SelectedPoints[4];

	Triangle Tri[4];
	if(Puszcsy == 0)
	{
		BaselinePoint = vertices[MaxX].Vertex;
		BaselineDir = normalize(vertices[MaxX].Vertex - vertices[MinX].Vertex);

		SelectedPoints[0] = MaxX;
		SelectedPoints[1] = MinX;

		unsigned int Ids[4] = {MaxY,MinY,MaxZ,MinZ};
		unsigned int MaxId = QuickhullFindMaxFromLine(vertices,BaselinePoint,BaselineDir,Ids,4);

		SelectedPoints[2] = Ids[MaxId];

		QuickhullEraseMaxId(Ids,4,MaxId);

		Tri[0].V[0] = SelectedPoints[0];
		Tri[0].V[1] = SelectedPoints[1];
		Tri[0].V[2] = SelectedPoints[2];

		unsigned int Final = QuickhullFindMaxFromTriangle(vertices,Tri[0],Ids,3);
		SelectedPoints[3] = Final;
	}
	else if(Puszcsy == 1)
	{
		BaselinePoint = vertices[MaxY].Vertex ;
		BaselineDir = normalize(vertices[MaxY].Vertex  - vertices[MinY].Vertex );

		SelectedPoints[0] = MaxY;
		SelectedPoints[1] = MinY;

		unsigned int Ids[4] = {MaxX,MinX,MaxZ,MinZ};
		unsigned int MaxId = QuickhullFindMaxFromLine(vertices,BaselinePoint,BaselineDir,Ids,4);

		SelectedPoints[2] = Ids[MaxId];

		QuickhullEraseMaxId(Ids,4,MaxId);

		Tri[0].V[0] = SelectedPoints[0];
		Tri[0].V[1] = SelectedPoints[1];
		Tri[0].V[2] = SelectedPoints[2];

		unsigned int Final = QuickhullFindMaxFromTriangle(vertices,Tri[0],Ids,3);
		SelectedPoints[3] = Final;
	}
	else
	{
		BaselinePoint = vertices[MaxZ].Vertex ;
		BaselineDir = normalize(vertices[MaxZ].Vertex  - vertices[MinZ].Vertex );

		SelectedPoints[0] = MaxZ;
		SelectedPoints[1] = MinZ;

		unsigned int Ids[4] = {MaxY,MinY,MaxX,MinX};
		unsigned int MaxId = QuickhullFindMaxFromLine(vertices,BaselinePoint,BaselineDir,Ids,4);

		SelectedPoints[2] = Ids[MaxId];

		QuickhullEraseMaxId(Ids,4,MaxId);

		Tri[0].V[0] = SelectedPoints[0];
		Tri[0].V[1] = SelectedPoints[1];
		Tri[0].V[2] = SelectedPoints[2];

		unsigned int Final = QuickhullFindMaxFromTriangle(vertices,Tri[0],Ids,3);
		SelectedPoints[3] = Final;
	}

	for(int i=0;i < 4;i++)
	{
		const vec4 &Vertex = vertices[SelectedPoints[i]].Vertex;
		/*
		 * Na, EZ az egyik hely, ahol be kell állítani a vertex attribútumokat.
		 */
		MyMesh::VertexHandle Handle = convex_hull.add_vertex(MyMesh::Point(Vertex[0],Vertex[1],Vertex[2]));
		vertex_handles[SelectedPoints[i]].Handle = Handle;
		vertex_handles[SelectedPoints[i]].Index = SelectedPoints[i];

		auto &Data = convex_hull.data(Handle);
		Data.SegmentId	= vertices[SelectedPoints[i]].SegmentId;
		Data.SampleId	= vertices[SelectedPoints[i]].SampleId;
		Data.TexCoord	= vertices[SelectedPoints[i]].TexCoord;
		vertices[SelectedPoints[i]].Added = true;
	}

	/*
	 * Figyelni kell az óramutató irányával megegyezőségre!
	 */
	std::vector<MyMesh::VertexHandle> Face;

	Face.clear();
	Face.push_back(vertex_handles[SelectedPoints[0]].Handle);
	Face.push_back(vertex_handles[SelectedPoints[2]].Handle);
	Face.push_back(vertex_handles[SelectedPoints[1]].Handle);
	convex_hull.add_face(Face);

	Face.clear();
	Face.push_back(vertex_handles[SelectedPoints[0]].Handle);
	Face.push_back(vertex_handles[SelectedPoints[1]].Handle);
	Face.push_back(vertex_handles[SelectedPoints[3]].Handle);
	convex_hull.add_face(Face);

	Face.clear();
	Face.push_back(vertex_handles[SelectedPoints[1]].Handle);
	Face.push_back(vertex_handles[SelectedPoints[2]].Handle);
	Face.push_back(vertex_handles[SelectedPoints[3]].Handle);
	convex_hull.add_face(Face);

	Face.clear();
	Face.push_back(vertex_handles[SelectedPoints[2]].Handle);
	Face.push_back(vertex_handles[SelectedPoints[0]].Handle);
	Face.push_back(vertex_handles[SelectedPoints[3]].Handle);
	convex_hull.add_face(Face);
}

//unsigned int QuickhullNumSteps = 0;

//unsigned int NumSteps = 0;


#include <Multithreading/Worker.h>

#include <chrono>

#include <iostream>

Spinlock cout_lock_quickhull;

bool QuickhullIterate(VertexData vertices[],unsigned int num_vertices,std::vector<VertexHandleArrayElement> &vertex_handles,MyMesh::FaceHandle triangle,MyMesh &convex_hull)
{
	float DIST_EPSILON = 1e-2;
	/*
	if(NumSteps == QuickhullNumSteps)
	{
		return false;
	}
	*/

	vec4 Normal = GetNormal(convex_hull,triangle);

	OpenMesh::Vec3f OM_OneVertex = convex_hull.point(convex_hull.fv_iter(triangle));
	vec4 OneVertex(OM_OneVertex[0],OM_OneVertex[1],OM_OneVertex[2]);

	bool VertexFound = false;

	auto Before = std::chrono::steady_clock::now();
	unsigned int MaxId = 0;
	float MaxLength = DIST_EPSILON;
	for(unsigned int i=0;i < num_vertices;i++)
	{
		if(vertices[i].Added)
			{continue;}

		float Length = dot(Normal,OneVertex - vertices[i].Vertex);

		if(Length > MaxLength)
		{
			MaxId = i;
			MaxLength = Length;

			VertexFound = true;
		}
	}
	auto After = std::chrono::steady_clock::now();
	auto Difference = After - Before;
	/*{
		std::lock_guard<Spinlock> Guard(cout_lock_quickhull);
		std::cout << "Find vertex time: " << std::chrono::duration<double,std::micro>(Difference).count() << "\n";
	}*/

	if(VertexFound)
	{
		//NumSteps++;

		float COS_EPSILON = 1e-6;

		std::list<MyMesh::FaceHandle> NegativeTriangles; //Tesztelés során negatívak lettek, bezárt szög >90 fok
		std::list<MyMesh::FaceHandle> VisibleTriangles;
		VisibleTriangles.push_back(triangle);
		
		Before = std::chrono::steady_clock::now();

		for(auto I = VisibleTriangles.begin();I != VisibleTriangles.end();I++)
		{
			std::list<MyMesh::FaceHandle> TrianglesToCheck;

			for(auto T = convex_hull.ff_iter(*I);T.is_valid();T++)
			{
				if(	std::find(VisibleTriangles.begin(),VisibleTriangles.end(),*T) == VisibleTriangles.end()		&&
					std::find(NegativeTriangles.begin(),NegativeTriangles.end(),*T) == NegativeTriangles.end()	&&
					std::find(TrianglesToCheck.begin(),TrianglesToCheck.end(),*T) == TrianglesToCheck.end()
					)
				{
					TrianglesToCheck.push_back(T);
				}
			}

			auto J = TrianglesToCheck.begin();
			while(TrianglesToCheck.size() != 0)
			{
				OpenMesh::Vec3f OM_OneVertex = convex_hull.point(convex_hull.fv_iter(*J));
				vec4 OneVertex(OM_OneVertex[0],OM_OneVertex[1],OM_OneVertex[2]);

				vec4 Normal = GetNormal(convex_hull,*J);
				vec4 NormalizedDir = normalize(OneVertex - vertices[MaxId].Vertex);
				float Dot = dot(Normal,NormalizedDir);

				if(Dot > COS_EPSILON)
				{
					VisibleTriangles.push_back(*J);
				}
				else
				{
					NegativeTriangles.push_back(*J);
				}

				auto K = J;
				J++;
				TrianglesToCheck.erase(K);
			}
		}
		After = std::chrono::steady_clock::now();
		Difference = After - Before;
		/*{
			std::lock_guard<Spinlock> Guard(cout_lock_quickhull);
			std::cout << "Find visible triangle time: " << std::chrono::duration<double,std::micro>(Difference).count() << "\n";
		}*/


		if(VisibleTriangles.size() == 0)
		{
			return false;
		}
		
		Before = std::chrono::steady_clock::now();

		for(auto I : VisibleTriangles)
		{
			convex_hull.delete_face(I,true);
		}
		
		After = std::chrono::steady_clock::now();
		Difference = After - Before;
		/*{
			std::lock_guard<Spinlock> Guard(cout_lock_quickhull);
			std::cout << "Visible triangle delete time: " << std::chrono::duration<double,std::micro>(Difference).count() << "\n";
		}*/
		
		Before = std::chrono::steady_clock::now();
	
		/*
		 * ITT VAN A TETŰ!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		 */
		convex_hull.garbage_collection();
		
		After = std::chrono::steady_clock::now();
		Difference = After - Before;
		/*{
			std::lock_guard<Spinlock> Guard(cout_lock_quickhull);
			std::cout << "Visible triangle GC time: " << std::chrono::duration<double,std::micro>(Difference).count() << "\n";
		}*/
		
		Before = std::chrono::steady_clock::now();

		/*
		 * Ezt a részt egy nap lehetne optimalizálni.
		 * Elég lenne valahogy a törölt háromszögek környékén keresni.
		 */
		MyMesh::HalfedgeHandle BoundaryEdge;
		bool BoundaryFound = false;
		for(auto I = convex_hull.halfedges_begin();I != convex_hull.halfedges_end();I++)
		{
			if(convex_hull.is_boundary(*I))
			{
				BoundaryEdge = *I;
				BoundaryFound = true;
				break;
			}
		}
		
		After = std::chrono::steady_clock::now();
		Difference = After - Before;
		/*{
			std::lock_guard<Spinlock> Guard(cout_lock_quickhull);
			std::cout << "Boundary search time: " << std::chrono::duration<double,std::micro>(Difference).count() << "\n";
		}*/

		if(!BoundaryFound)
		{
			std::cerr << "Error: elfajult alakzat" << std::endl;
			return true;
		}

		/*
		 * Na, ITT kell még módosítani.
		 */
		MyMesh::VertexHandle FarthestHandle = convex_hull.add_vertex(MyMesh::Point(vertices[MaxId].Vertex[0],vertices[MaxId].Vertex[1],vertices[MaxId].Vertex[2]));
		//VertexHandleArrayElement Element;

		vertex_handles[MaxId].Handle = FarthestHandle;
		vertex_handles[MaxId].Index = MaxId;

		auto &Data = convex_hull.data(FarthestHandle);
		Data.SegmentId	= vertices[MaxId].SegmentId;
		Data.SampleId	= vertices[MaxId].SampleId;
		Data.TexCoord	= vertices[MaxId].TexCoord;
		//vertex_handles.push_back(Element);
		//vertices[MaxId].Handle = FarthestHandle;
		
		Before = std::chrono::steady_clock::now();

		std::list<std::vector<MyMesh::VertexHandle> > NewFaces;
		for(MyMesh::HalfedgeLoopIter I = convex_hull.hl_begin(BoundaryEdge);I != convex_hull.hl_end(BoundaryEdge);I++)
		{
			std::vector<MyMesh::VertexHandle> NewFace;

			NewFace.push_back(convex_hull.to_vertex_handle(I));
			NewFace.push_back(FarthestHandle);
			NewFace.push_back(convex_hull.from_vertex_handle(I));

			NewFaces.push_back(NewFace);
		}
		
		
		After = std::chrono::steady_clock::now();
		Difference = After - Before;
		/*{
			std::lock_guard<Spinlock> Guard(cout_lock_quickhull);
			std::cout << "Prepare add face time: " << std::chrono::duration<double,std::micro>(Difference).count() << "\n";
		}*/
		
		Before = std::chrono::steady_clock::now();

		for(auto &NewFace : NewFaces)
		{
			convex_hull.add_face(NewFace);
		}
		
		After = std::chrono::steady_clock::now();
		Difference = After - Before;
		/*{
			std::lock_guard<Spinlock> Guard(cout_lock_quickhull);
			std::cout << "Add face time: " << std::chrono::duration<double,std::micro>(Difference).count() << "\n";
		}*/

		vertices[MaxId].Added = true;
		
		//convex_hull.garbage_collection();
		
		return true;
	}
	else
	{
		return false;
	}
}

/*
 * http://thomasdiewald.com/blog/?p=1888
 */
void Quickhull(VertexData vertices[],unsigned int num_vertices,MyMesh &convex_hull)
{
	std::vector<VertexHandleArrayElement> VertexHandles(num_vertices);

	QuickhullInit(vertices,num_vertices,VertexHandles,convex_hull);

	//NumSteps = 0;

	bool Restart = true;
	while(Restart)
	{
		Restart = false;
		unsigned int i=0;
		auto Before = std::chrono::steady_clock::now();
		MyMesh::FaceIter T_begin = convex_hull.faces_begin();
		for(MyMesh::FaceIter T = T_begin;T != convex_hull.faces_end();T++)
		{
			if(QuickhullIterate(vertices,num_vertices,VertexHandles,*T,convex_hull))
			{
				Restart = true;
				break;
			}
			i++;

			T_begin = T;
		}
		auto After = std::chrono::steady_clock::now();
		auto Difference = After - Before;
		{
			//std::lock_guard<Spinlock> Guard(cout_lock_quickhull);
			//std::cout << "Quickhull iteration time: " << std::chrono::duration<double,std::micro>(Difference).count() << std::endl;
		}
	}

	//unsigned int i=0;
	//for(VertexHandleArrayElement I : VertexHandles)
	//{
	//	vertices[I.Index].Handle = I.VertexHandle;
	//	i++;
	//}

	//std::cout << convex_hull.n_vertices() << " " << num_vertices << std::endl;
}

