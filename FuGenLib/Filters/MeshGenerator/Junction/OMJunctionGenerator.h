#ifndef OM_JUNCTION_GENERATOR_H
#define OM_JUNCTION_GENERATOR_H

#include "JunctionGenerator.h"

#include "Quickhull/OMQuickhull.h"

class OMJunctionGenerator : public JunctionGenerator
{
private:
	//
	//void SampleSegmentBoundary(const TreeHypergraph::Branch &branch,float t,unsigned int sample_id_begin,VertexData destination[]);
	//
public:
	//
	virtual void SampleJunction() override;
	//
	OMJunctionGenerator(MyMesh &junction_mesh,const TreeHypergraph::Junction &junction,unsigned int segment_width,unsigned int segment_height)
		:JunctionGenerator(junction_mesh,junction,segment_width,segment_height)
	{}
	//
	~OMJunctionGenerator()
	{}
	/*
	 * End of class
	 */
};

#endif // OM_JUNCTION_GENERATOR_H