#ifndef QH_JUNCTION_GENERATOR_H
#define QH_JUNCTION_GENERATOR_H

#include "JunctionGenerator.h"

#include "Quickhull/QhQuickhull.h"

#include <Multithreading/Spinlock.h>

extern Spinlock cout_lock;

class QhJunctionGenerator : public JunctionGenerator
{
public:
	//
	virtual void SampleJunction() override
	{
		unsigned int NumVertices = Junction.Children.size()*SegmentWidth;
		//
		if(Junction.Root != nullptr)
			{NumVertices += SegmentWidth;}
		//
		std::vector<VertexData> Vertices(NumVertices);
		//
		unsigned int j=0;
		if(Junction.Root != nullptr)
		{
			SampleSegmentBoundary(*Junction.Root,Junction.Root->t_End,(SegmentHeight - 1)*SegmentWidth,&Vertices[0]);
		}
		//
		unsigned int I = 0;
		if(Junction.Root != nullptr)
			{I = 1;}
		//
		for(TreeHypergraph::Branch *B : Junction.Children)
		{
			SampleSegmentBoundary(*B,B->t_Begin,0,&Vertices[I * SegmentWidth]);
			I++;
		}
		//
		std::vector<vec4> QhVertices(NumVertices);
		//
		unsigned int i=0;
		for(VertexData &Data : Vertices)
		{
			QhVertices[i] = Data.Vertex;
			i++;
		}
		//auto Before = std::chrono::steady_clock::now();
		//
		QhMesh Result;
		QhQuickhull(&QhVertices[0],QhVertices.size(),Result);
		//
		//auto After = std::chrono::steady_clock::now();
		//auto Difference = After - Before;
		//std::cout << "Junction generation time: " << std::chrono::duration<double,std::milli>(Difference).count() << std::endl;
		//
		std::vector<bool> VertexAdded(NumVertices,false);
		std::vector<MyMesh::VertexHandle> VertexHandles(NumVertices);
		//
		//unsigned int TriangleId = 0;
		for(const QhFace &Triangle : Result.Faces)
		{
			if(Triangle.IsDeleted())
			{continue;}
			//
			unsigned int VertexIds[3];
			QhGetTriangleIds(Triangle,VertexIds);
			//
			//unsigned int Tmp = VertexIds[0];
			//VertexIds[0] = VertexIds[1];
			//VertexIds[1] = Tmp;
			//
			std::vector<MyMesh::VertexHandle> Face;
			for(unsigned int i=0;i < 3;i++)
			{
				unsigned int VertexId = VertexIds[i];
				if(!VertexAdded[VertexId])
				{
					vec4 &Vertex = QhVertices[VertexId];
					VertexHandles[VertexId] = JunctionMesh.add_vertex(MyMesh::Point(Vertex[0],Vertex[1],Vertex[2]));
					auto &Data = JunctionMesh.data(VertexHandles[VertexId]);
					Data.SegmentId	= Vertices[VertexId].SegmentId;
					Data.SampleId	= Vertices[VertexId].SampleId;
					Data.TexCoord	= Vertices[VertexId].TexCoord;
					VertexAdded[VertexId] = true;
				}
				Face.push_back(VertexHandles[VertexId]);
			}
			
			//{
				//std::lock_guard<Spinlock> lock_guard(cout_lock);
				//std::cout << "Triangle id: " << TriangleId << std::endl;
				//TriangleId++;
				JunctionMesh.add_face(Face);
			//}
		}
	}
	//
	QhJunctionGenerator(MyMesh &junction_mesh,const TreeHypergraph::Junction &junction,unsigned int segment_width,unsigned int segment_height)
		:JunctionGenerator(junction_mesh,junction,segment_width,segment_height)
	{}
	//
	~QhJunctionGenerator()
	{}
	/*
	 * End of class
	 */
};

#endif // QH_JUNCTION_GENERATOR_H
