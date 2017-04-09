
#include "JunctionOperations.h"

#include <list>

//#include <chrono>
//#include <iostream>

void JunctionOperations::DeleteTriangles()
{
	//auto Before = std::chrono::steady_clock::now();
	//
	std::list<MyMesh::FaceIter> DeletableTriangles;
	//
	for(MyMesh::FaceIter F = JunctionMesh.faces_begin();F != JunctionMesh.faces_end();F++)
	{
		bool VertexFound = false;
		//
		for(MyMesh::FaceVertexIter V_I = JunctionMesh.fv_iter(*F);V_I.is_valid();V_I++)
		{
			auto Data_I = JunctionMesh.data(V_I);
			MyMesh::FaceVertexIter V_J = V_I;
			V_J++;
			for(;V_J.is_valid();V_J++)
			{
				auto Data_J = JunctionMesh.data(V_J);
				if(Data_I.SegmentId != Data_J.SegmentId)
				{
					VertexFound = true;
					break;
				}
			}
			//
			if(VertexFound)
			{
				break;
			}
		}
		//
		if(!VertexFound)
		{
			DeletableTriangles.push_back(F);
		}
	}
	//
	for(auto I : DeletableTriangles)
	{
		JunctionMesh.delete_face(I,true);
	}
	//
	JunctionMesh.garbage_collection();
	//
	//auto After = std::chrono::steady_clock::now();
	//auto Difference = After - Before;
	//std::cout << "Delete triangles time: " << std::chrono::duration<double,std::milli>(Difference).count() << std::endl;
}

void JunctionOperations::CollapseEdges()
{
	//auto Before = std::chrono::steady_clock::now();
	//
	for(MyMesh::VertexIter I = JunctionMesh.vertices_begin();I != JunctionMesh.vertices_end();I++)
	{
		auto &I_Data = JunctionMesh.data(I);
		I_Data.Collapsed = false;
	}
	//
	std::list<MyMesh::VertexOHalfedgeIter> EdgesToCollapse;
	unsigned int i=0;
	//
	for(MyMesh::VertexIter I = JunctionMesh.vertices_begin();I != JunctionMesh.vertices_end();I++)
	{
		auto &I_Data = JunctionMesh.data(I);
		if(I_Data.Collapsed)
			{continue;}
		//
		bool FoundOne = false;
		MyMesh::VertexOHalfedgeIter MinIter;
		float MinLength;
		//
		for(MyMesh::VertexOHalfedgeIter J = JunctionMesh.voh_iter(I);J.is_valid();J++)
		{
			MyMesh::VertexHandle J_V = JunctionMesh.to_vertex_handle(J);
			auto &J_Data = JunctionMesh.data(J_V);
			//
			if(J_Data.Collapsed)
				{continue;}
			//
			if(I_Data.SegmentId != J_Data.SegmentId)
			{
				MyMesh::Point I_Point = JunctionMesh.point(*I);
				MyMesh::Point J_Point = JunctionMesh.point(J_V);
				//
				vec4 I_Vec(I_Point[0],I_Point[1],I_Point[2]);
				vec4 J_Vec(J_Point[0],J_Point[1],J_Point[2]);
				//
				float Length = length(I_Vec - J_Vec);
				//
				if(FoundOne)
				{
					if(Length < MinLength)
					{
						//
						MinIter = J;
						MinLength = Length;
					}
				}
				else
				{
					//
					MinIter = J;
					MinLength = Length;
					//
					FoundOne = true;
				}
			}
		}
		//
		if(FoundOne)
		{
			MyMesh::VertexHandle J_V = JunctionMesh.to_vertex_handle(MinIter);
			auto &J_Data = JunctionMesh.data(J_V);
			//
			I_Data.OtherTexCoord	= J_Data.TexCoord;
			I_Data.OtherSegmentId	= J_Data.SegmentId;
			I_Data.OtherSampleId	= J_Data.SampleId;
			//
			I_Data.Collapsed = true;
			//
			J_Data.OtherTexCoord	= I_Data.TexCoord;
			J_Data.OtherSegmentId	= I_Data.SegmentId;
			J_Data.OtherSampleId	= I_Data.SampleId;
			//
			J_Data.Collapsed = true;
			//
			MyMesh::Point I_Point = JunctionMesh.point(*I);
			MyMesh::Point J_Point = JunctionMesh.point(J_V);
			MyMesh::Point Average = (1.0/2.0)*(I_Point + J_Point);
			//
			JunctionMesh.set_point(*I,	Average);
			JunctionMesh.set_point(J_V,Average);
			//
			EdgesToCollapse.push_back(MinIter);
			i++;
		}
	}
	//
	for(auto &Edge : EdgesToCollapse)
	{
		JunctionMesh.collapse(*Edge);
	}
	//
	JunctionMesh.garbage_collection();
	//
	//auto After = std::chrono::steady_clock::now();
	//auto Difference = After - Before;
	//std::cout << "Collapse edges time: " << std::chrono::duration<double,std::milli>(Difference).count() << std::endl;
}
