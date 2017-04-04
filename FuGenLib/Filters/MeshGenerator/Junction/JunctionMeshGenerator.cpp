
#include "JunctionMeshGenerator.h"

#include <iostream>

void SetTexCoord(MyMesh &half_edge,MyMesh::FaceHalfedgeIter E,bool from_other,bool to_other,float delta_uv)
{
	auto &FromData	= half_edge.data(half_edge.from_vertex_handle(E));
	auto &ToData	= half_edge.data(half_edge.to_vertex_handle(E));
	//
	vec4 FromTexCoord = from_other? FromData.OtherTexCoord : FromData.TexCoord;
	vec4 ToTexCoord = to_other? ToData.OtherTexCoord : ToData.TexCoord;
	//
	E++;
	auto &ThirdData = half_edge.data(half_edge.to_vertex_handle(E));
	ThirdData.TexCoord	= (FromTexCoord + ToTexCoord)*(1.0f/2.0f) + vec4(delta_uv,delta_uv);
}

void JunctionMeshGenerator::ParametrizeHalfedge()
{
	for(MyMesh::FaceIter F = JunctionMesh.faces_begin();F != JunctionMesh.faces_end();F++)
	{
		bool Found = false;
		//
		for(MyMesh::FaceHalfedgeIter E = JunctionMesh.fh_iter(F);E.is_valid();E++)
		{
			auto &FromData	= JunctionMesh.data(JunctionMesh.from_vertex_handle(E));
			auto &ToData	= JunctionMesh.data(JunctionMesh.to_vertex_handle(E));
			//
			/*
			 * TODO Csúnya kódduplikálást ki kéne irtani.
			 */
			if(FromData.SegmentId == ToData.SegmentId)
			{
				SetTexCoord(JunctionMesh,E,false,false,DeltaUV);
				//
				Found = true;
				break;
			}
			else if(FromData.OtherSegmentId == ToData.SegmentId)
			{
				SetTexCoord(JunctionMesh,E,true,false,DeltaUV);
				//
				Found = true;
				break;
			}
			else if(FromData.SegmentId == ToData.OtherSegmentId)
			{
				SetTexCoord(JunctionMesh,E,false,true,DeltaUV);
				//
				Found = true;
				break;
			}
			else if(FromData.OtherSegmentId == ToData.OtherSegmentId)
			{
				SetTexCoord(JunctionMesh,E,true,true,DeltaUV);
				//
				Found = true;
				break;
			}
		}
		//
		/*
		if(!Found)
		{
			//std::cout << "Epic bug" << std::endl;
			std::cout << "Epic bug\n";
			//
			for(MyMesh::FaceHalfedgeIter E = JunctionMesh.fh_iter(F);E.is_valid();E++)
			{
				auto &FromData	= JunctionMesh.data(JunctionMesh.from_vertex_handle(E));
				//
				std::cout << FromData.SegmentId << " ";
			}
			//
			std::cout << std::endl;
			//
			for(MyMesh::FaceHalfedgeIter E = JunctionMesh.fh_iter(F);E.is_valid();E++)
			{
				auto &FromData	= JunctionMesh.data(JunctionMesh.from_vertex_handle(E));
				//
				std::cout << FromData.OtherSegmentId << " ";
			}
		}
		*/
	}
}