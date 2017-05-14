#ifndef HYPERGRAPH_NODE_PRESENTER_H
#define HYPERGRAPH_NODE_PRESENTER_H

#include "../NodePresenter.h"

#include "../../Data/TreeSkeletonPresenter.h"
#include "../../Data/TreeHypergraphPresenter.h"

#include <Filters/HypergraphGenerator/GenerateHypergraph.h>

#include <View/EdgeVisualizer/FuGenGLView.h>

class HypergraphNodePresenter : public NodePresenter, private ITreeDataVisitor
{
private:
	//TreeNode *Skeleton = nullptr;
	TreeSkeletonPresenter *Skeleton = nullptr;
	//
	GenerateHypergraph HypergraphGenerator;
	//
	TreeHypergraph *Hypergraph = nullptr;
	TreeHypergraphPresenter HypergraphPresenter;
	//
	static const std::string HypergraphNodeName;
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
	void SetRadius(float radius);
	//
	float GetRadius();
	//
	void SetRadiusDecay(float radius_decay);
	//
	float GetRadiusDecay();
	//
	void SetParentWeight(float parent_weight);
	//
	float GetParentWeight();
	//
	void SetInitSpeed(float init_speed);
	//
	float GetInitSpeed();
	//
	void SetEndSpeed(float end_speed);
	//
	float GetEndSpeed();
	//
	HypergraphNodePresenter(FuGenGLView *gl_view);
	//
	virtual ~HypergraphNodePresenter() override;
};

#endif // HYPERGRAPH_NODE_PRESENTER_H

