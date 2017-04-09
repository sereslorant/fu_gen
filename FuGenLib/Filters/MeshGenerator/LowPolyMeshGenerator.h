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
public:
	const float DELTA_UV = 0.15;
	//
	unsigned int SegmentWidth;
	unsigned int SegmentHeight;
	//
	void Generate(TreeHypergraph *tree_hypergraph,MultiMesh &result);

	LowPolyMeshGenerator(unsigned int segment_width,unsigned int segment_height)
		:SegmentWidth(segment_width),SegmentHeight(segment_height)
	{}

	~LowPolyMeshGenerator()
	{}
};

#endif // LOW_POLY_MESH_CREATOR
