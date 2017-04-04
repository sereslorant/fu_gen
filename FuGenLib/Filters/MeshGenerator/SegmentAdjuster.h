#ifndef SEGMENT_ADJUSTER_H
#define SEGMENT_ADJUSTER_H

#include "../../Utils/Quickhull.h"

class SegmentAdjuster
{
private:
	MyMesh		&JunctionMesh;
	MultiMesh	&Result;
	//
public:
	//
	void AdjustSegments()
	{
		for(MyMesh::VertexIter I = JunctionMesh.vertices_begin();I != JunctionMesh.vertices_end();I++)
		{
			auto &I_Data = JunctionMesh.data(I);
			if(!I_Data.Collapsed)
				{continue;}

			if(I_Data.OtherSegmentId != -1)
			{
				MyMesh::Point I_Point = JunctionMesh.point(*I);
				Result.Segments[I_Data.SegmentId].Vertices[I_Data.SampleId] = vec4(I_Point[0],I_Point[1],I_Point[2]);
				Result.Segments[I_Data.OtherSegmentId].Vertices[I_Data.OtherSampleId] = vec4(I_Point[0],I_Point[1],I_Point[2]);
			}
		}
	}
	//
	SegmentAdjuster(MyMesh &junction_mesh,MultiMesh &result)
		:JunctionMesh(junction_mesh),Result(result)
	{}
	//
	~SegmentAdjuster()
	{}
	/*
	 * End of class
	 */
};

#endif // SEGMENT_ADJUSTER_H
