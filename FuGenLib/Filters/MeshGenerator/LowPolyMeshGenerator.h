#ifndef LOW_POLY_MESH_CREATOR
#define LOW_POLY_MESH_CREATOR

#include "../../Data/TreeHypergraph.h"
#include "../../Data/MultiMesh.h"

#include "../../Multithreading/Worker.h"

/*
 * Május 3 - 4
 */
class LowPolyMeshGenerator
{
private:
	// */
	void GenerateSegments(std::vector<Job *> &generate_segment_jobs,JobQueue &jobQueue,TreeHypergraph *tree_hypergraph,MultiMesh &result);
	//
	void GenerateJunctions(std::vector<Job *> &generate_segment_jobs,JobQueue &jobQueue,TreeHypergraph *tree_hypergraph,MultiMesh &result);
	//
	void GenerateSingleThreaded(TreeHypergraph *tree_hypergraph,MultiMesh &result);
	//
	void GenerateMultiThreaded(TreeHypergraph *tree_hypergraph,MultiMesh &result);
	//
	const float DELTA_UV = 0.15;
	//
	unsigned int SegmentWidth;
	unsigned int SegmentHeight;
	//
public:
	//
	void SetSegmentWidth(unsigned int segment_width)
	{
		SegmentWidth = segment_width;
	}
	//
	void SetSegmentHeight(unsigned int segment_height)
	{
		SegmentHeight = segment_height;
	}
	//
	unsigned int GetSegmentWidth()
	{
		return SegmentWidth;
	}
	//
	unsigned int GetSegmentHeight()
	{
		return SegmentHeight;
	}
	//
	void Generate(TreeHypergraph *tree_hypergraph,MultiMesh* &result);
	//
	LowPolyMeshGenerator(unsigned int segment_width = 6,unsigned int segment_height = 6)
		:SegmentWidth(segment_width),SegmentHeight(segment_height)
	{}

	~LowPolyMeshGenerator()
	{}
};

#endif // LOW_POLY_MESH_CREATOR
