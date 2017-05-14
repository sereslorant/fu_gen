
#include "../ConnectionVisitor.h"

#include "HypergraphNodePresenter.h"

const std::string HypergraphNodePresenter::HypergraphNodeName = "Hypergraph";

void HypergraphNodePresenter::Refresh()
{
	if(Skeleton != nullptr)
	{
		auto OldHypergraph = Hypergraph;
		//
		HypergraphGenerator.Draw(Skeleton->GetSkeleton(),Hypergraph);
		//
		HypergraphPresenter.OnChanged(Hypergraph);
		//
		if(OldHypergraph != nullptr)
			{delete OldHypergraph;}
	}
}

void HypergraphNodePresenter::Visit(TreeSkeletonPresenter &skeleton_presenter)
{
	Skeleton = &skeleton_presenter;
}

void HypergraphNodePresenter::Visit(TreeHypergraphPresenter &hypergraph_presenter)
{}

void HypergraphNodePresenter::Visit(TreeMeshPresenter &mesh_presenter)
{}

TreeDataPresenter &HypergraphNodePresenter::GetDataPresenter()
{
	return HypergraphPresenter;
}

const std::string &HypergraphNodePresenter::GetName()
{
	return HypergraphNodeName;
}

bool HypergraphNodePresenter::IsConnectable(IPipelineNodeModel *other_model)
{
	NodePresenter *OtherNode = (NodePresenter *)other_model->GetUserData();
	ConnectionVisitor Visitor(ConnectionVisitor::TREE_SKELETON);
	OtherNode->GetDataPresenter().Accept(Visitor);
	return Visitor.IsConnectable();
}

bool HypergraphNodePresenter::ConnectInput(TreeDataPresenter &input_data_presenter)
{
	//TreeNode *PreviousSkeleton = Skeleton;
	TreeSkeletonPresenter *PreviousSkeleton = Skeleton;
	//
	input_data_presenter.Accept(*this);
	//
	bool ConnectionSuccessful = Skeleton != PreviousSkeleton;
	if(ConnectionSuccessful && PreviousSkeleton != nullptr)
	{
		PreviousSkeleton->RemoveListener(&DataListener);
	}
	Skeleton->AddListener(&DataListener);
	Refresh();
	//
	return ConnectionSuccessful;
}

void HypergraphNodePresenter::SetRadius(float radius)
{
	HypergraphGenerator.SetRadius(radius);
	Refresh();
}

float HypergraphNodePresenter::GetRadius()
{
	return HypergraphGenerator.GetRadius();
}

void HypergraphNodePresenter::SetRadiusDecay(float radius_decay)
{
	HypergraphGenerator.SetRadiusDecay(radius_decay);
	Refresh();
}

float HypergraphNodePresenter::GetRadiusDecay()
{
	return HypergraphGenerator.GetRadiusDecay();
}

void HypergraphNodePresenter::SetParentWeight(float parent_weight)
{
	HypergraphGenerator.SetParentWeight(parent_weight);
	Refresh();
}

float HypergraphNodePresenter::GetParentWeight()
{
	return HypergraphGenerator.GetParentWeight();
}

void HypergraphNodePresenter::SetInitSpeed(float init_speed)
{
	HypergraphGenerator.SetInitSpeed(init_speed);
	Refresh();
}

float HypergraphNodePresenter::GetInitSpeed()
{
	return HypergraphGenerator.GetInitSpeed();
}

void HypergraphNodePresenter::SetEndSpeed(float end_speed)
{
	HypergraphGenerator.SetEndSpeed(end_speed);
	Refresh();
}

float HypergraphNodePresenter::GetEndSpeed()
{
	return HypergraphGenerator.GetEndSpeed();
}

HypergraphNodePresenter::HypergraphNodePresenter(FuGenGLView *gl_view)
	:HypergraphGenerator(0.0,0.0,0.0,0.0,0.0)
{
	if(gl_view != nullptr)
	{
		HypergraphPresenter.SetShaderProgram(
			&(gl_view->GetEdgeVisualizer().GetHypergraphShaderProgram())
		);
	}
	//
	Refresh();
}

HypergraphNodePresenter::~HypergraphNodePresenter()
{
	delete Hypergraph;
}
