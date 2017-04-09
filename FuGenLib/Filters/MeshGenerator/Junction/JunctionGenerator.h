#ifndef JUNCTION_GENERATOR_H
#define JUNCTION_GENERATOR_H

#include <Data/MultiMesh.h>
#include <Data/TreeHypergraph.h>

#include "Quickhull/OMQuickhull.h"

#include <Const.h>
#include <Utils/GeneralizedCylinder.h>

class JunctionGenerator
{
protected:
	MyMesh &JunctionMesh;
	const TreeHypergraph::Junction &Junction;
	//
	unsigned int SegmentWidth;
	unsigned int SegmentHeight;
	//
	void SampleSegmentBoundary(const TreeHypergraph::Branch &branch,float t,unsigned int sample_id_begin,VertexData destination[])
	{
		GeneralizedCylinder BranchCylinder(*branch.Curve,branch.Up,branch.Width);
		float dAngle = 2.0 * PI / SegmentWidth;
		for(unsigned int i=0;i < SegmentWidth;i++)
		{
			float ParamX = t;
			float ParamY = i*dAngle;
			destination[i].Vertex = BranchCylinder.GetPoint(ParamX,ParamY);
			ParamX /= (branch.t_End - branch.t_Begin);
			ParamY /= 2.0*PI;
			destination[i].TexCoord = vec4(ParamX,ParamY);
			destination[i].SegmentId = branch.Id;
			destination[i].SampleId = sample_id_begin + i;
		}
	}
	//
public:
	//
	virtual void SampleJunction() = 0;
	//
	JunctionGenerator(MyMesh &junction_mesh,const TreeHypergraph::Junction &junction,unsigned int segment_width,unsigned int segment_height)
		:JunctionMesh(junction_mesh),Junction(junction),SegmentWidth(segment_width),SegmentHeight(segment_height)
	{}
	//
	~JunctionGenerator()
	{}
	/*
	 * End of class
	 */
};

#endif // JUNCTION_GENERATOR_H