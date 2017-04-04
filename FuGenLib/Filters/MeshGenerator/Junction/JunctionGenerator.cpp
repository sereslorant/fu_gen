
#include "JunctionGenerator.h"

#include "../../../Const.h"
#include "../../../Utils/GeneralizedCylinder.h"

void JunctionGenerator::SampleSegmentBoundary(const TreeHypergraph::Branch &branch,float t,unsigned int sample_id_begin,VertexData destination[])
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

void JunctionGenerator::SampleJunction()
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
	Quickhull(&Vertices[0],Vertices.size(),JunctionMesh);
}
