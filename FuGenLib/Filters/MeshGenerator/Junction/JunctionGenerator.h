#ifndef JUNCTION_GENERATOR_H
#define JUNCTION_GENERATOR_H

#include "../../../Data/TreeHypergraph.h"
#include "../../../Utils/Quickhull.h"

class JunctionGenerator
{
private:
	MyMesh &JunctionMesh;
	const TreeHypergraph::Junction &Junction;
	//
	unsigned int SegmentWidth;
	unsigned int SegmentHeight;
	//
	void SampleSegmentBoundary(const TreeHypergraph::Branch &branch,float t,unsigned int sample_id_begin,VertexData destination[]);
	//
public:
	//
	void SampleJunction();
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