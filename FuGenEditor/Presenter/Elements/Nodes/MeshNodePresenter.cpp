
#include "../ConnectionVisitor.h"

#include "MeshNodePresenter.h"

const std::string MeshNodePresenter::MeshNodeName = "LowPolyMesh";

void MeshNodePresenter::Refresh()
{
	//std::cout << "Refreshing mesh" << std::endl;
	//
	if(Hypergraph != nullptr)
	{
		auto OldMesh = Mesh;
		//
		MeshGenerator.Generate(Hypergraph->GetHypergraph(),Mesh);
		//
		MeshPresenter.OnChanged(Mesh);
		//
		if(OldMesh != nullptr)
			{delete OldMesh;}
	}
}

void MeshNodePresenter::Visit(TreeSkeletonPresenter &skeleton_presenter)
{}

void MeshNodePresenter::Visit(TreeHypergraphPresenter &hypergraph_presenter)
{
	Hypergraph = &hypergraph_presenter;
}

void MeshNodePresenter::Visit(TreeMeshPresenter &mesh_presenter)
{}

TreeDataPresenter &MeshNodePresenter::GetDataPresenter()
{
	return MeshPresenter;
}

const std::string &MeshNodePresenter::GetName()
{
	return MeshNodeName;
}

bool MeshNodePresenter::IsConnectable(IPipelineNodeModel *other_model)
{
	NodePresenter *OtherNode = (NodePresenter *)other_model->GetUserData();
	ConnectionVisitor Visitor(ConnectionVisitor::TREE_HYPERGRAPH);
	OtherNode->GetDataPresenter().Accept(Visitor);
	return Visitor.IsConnectable();
}

bool MeshNodePresenter::ConnectInput(TreeDataPresenter &input_data_presenter)
{
	TreeHypergraphPresenter *PreviousHypergraph = Hypergraph;
	//
	input_data_presenter.Accept(*this);
	//
	bool ConnectionSuccessful = Hypergraph != PreviousHypergraph;
	if(ConnectionSuccessful && PreviousHypergraph != nullptr)
	{
		PreviousHypergraph->RemoveListener(&DataListener);
	}
	Hypergraph->AddListener(&DataListener);
	Refresh();
	//
	return ConnectionSuccessful;
}

void MeshNodePresenter::SetSegmentWidth(unsigned int segment_width)
{
	MeshGenerator.SetSegmentWidth(segment_width);
	Refresh();
}

unsigned int MeshNodePresenter::GetSegmentWidth()
{
	return MeshGenerator.GetSegmentWidth();
}

void MeshNodePresenter::SetSegmentHeight(unsigned int segment_height)
{
	MeshGenerator.SetSegmentHeight(segment_height);
	Refresh();
}

unsigned int MeshNodePresenter::GetSegmentHeight()
{
	return MeshGenerator.GetSegmentHeight();
}

MeshNodePresenter::MeshNodePresenter(FuGenGLView *gl_view)
{
	if(gl_view != nullptr)
	{
		MeshPresenter.SetShaderProgram(
			&(gl_view->GetEdgeVisualizer().GetMeshShaderProgram())
		);
	}
	//
	Refresh();
}

MeshNodePresenter::~MeshNodePresenter()
{
	delete Mesh;
}
