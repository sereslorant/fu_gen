#ifndef MESH_NODE_PRESENTER_H
#define MESH_NODE_PRESENTER_H

#include "../NodePresenter.h"

#include "../../Data/TreeHypergraphPresenter.h"
#include "../../Data/TreeMeshPresenter.h"

#include <Filters/MeshGenerator/LowPolyMeshGenerator.h>

#include <View/EdgeVisualizer/FuGenGLView.h>

class MeshNodePresenter : public NodePresenter, private ITreeDataVisitor
{
private:
	//TreeHypergraph *Hypergraph = nullptr;
	TreeHypergraphPresenter *Hypergraph = nullptr;
	//
	LowPolyMeshGenerator MeshGenerator;
	//
	MultiMesh *Mesh = nullptr;
	TreeMeshPresenter MeshPresenter;
	//
	static const std::string MeshNodeName;
	//
	virtual void Refresh() override;
	//
public:
	//
	virtual void Visit(TreeSkeletonPresenter &skeleton_presenter) override;
	//
	virtual void Visit(TreeHypergraphPresenter &hypergraph_presenter) override;
	//
	virtual void Visit(TreeMeshPresenter &mesh_presenter) override;
	//
	virtual TreeDataPresenter &GetDataPresenter() override;
	//
	virtual const std::string &GetName() override;
	//
	virtual bool IsConnectable(IPipelineNodeModel *other_model) override;
	//
	virtual bool ConnectInput(TreeDataPresenter &input_data_presenter) override;
	//
	void SetSegmentWidth(unsigned int segment_width);
	//
	unsigned int GetSegmentWidth();
	//
	void SetSegmentHeight(unsigned int segment_height);
	//
	unsigned int GetSegmentHeight();
	//
	MeshNodePresenter(FuGenGLView *gl_view);
	//
	virtual ~MeshNodePresenter() override;
};

#endif // MESH_NODE_PRESENTER_H
