
#include "PipelinePresenter.h"

IPipelineEdgeModel *PipelinePresenter::SpawnEdge(IPipelineNodeModel &begin_model,IPipelineNodeModel &end_model)
{
	NodePresenter *BeginNode = (NodePresenter *)begin_model.GetUserData();
	EdgePresenter *NewPresenter = new EdgePresenter(&Visualizer,BeginNode->GetDataPresenter());
	PipelineEdges.push_back(NewPresenter);
	return NewPresenter;
}

void PipelinePresenter::AddListener(IPipelineListener *new_listener)
{
	Listeners.push_back(new_listener);
}

TurtleNodePresenter *PipelinePresenter::AddTurtleNode()
{
	TurtleNodePresenter *NewTurtleNode = new TurtleNodePresenter(GLView);
	//
	NewTurtleNode->SetAxiom("A");
	//
	constexpr double PI = 3.14159265359;
	NewTurtleNode->SetDeltaAngle(PI/2.0*0.25);
	NewTurtleNode->SetDeltaDistance(1.0);
	//
	NewTurtleNode->AddProduction('A',"[&FL!A]/////’[&FL!A]///////’[&FL!A]");
	NewTurtleNode->AddProduction('F',"S ///// F");
	NewTurtleNode->AddProduction('S',"F L");
	NewTurtleNode->AddProduction('L',"[’’’^^{.-f.+f.+f.-|-f.+f.+f.}]");
	//
	NewTurtleNode->SetRecursionDepth(5);
	//
	NewTurtleNode->GetDataPresenter().AddListener(&viewRefresher);
	//
	PipelineNodes.push_back(NewTurtleNode);
	for(IPipelineListener *Listener : Listeners) {Listener->TurtleNodeAdded(NewTurtleNode);}
	return NewTurtleNode;
}

HypergraphNodePresenter *PipelinePresenter::AddHypergraphNode()
{
	HypergraphNodePresenter *NewHypergraphNode = new HypergraphNodePresenter(GLView);
	//
	NewHypergraphNode->SetRadius(0.125);
	NewHypergraphNode->SetRadiusDecay(0.75);
	NewHypergraphNode->SetParentWeight(0.0);
	NewHypergraphNode->SetInitSpeed(0.0);
	NewHypergraphNode->SetEndSpeed(0.0);
	//
	NewHypergraphNode->GetDataPresenter().AddListener(&viewRefresher);
	//
	PipelineNodes.push_back(NewHypergraphNode);
	for(IPipelineListener *Listener : Listeners) {Listener->HypergraphNodeAdded(NewHypergraphNode);}
	return NewHypergraphNode;
}

MeshNodePresenter *PipelinePresenter::AddMeshNode()
{
	MeshNodePresenter *NewMeshNode = new MeshNodePresenter(GLView);
	//
	NewMeshNode->SetSegmentWidth(4);
	NewMeshNode->SetSegmentHeight(10);
	//
	NewMeshNode->GetDataPresenter().AddListener(&viewRefresher);
	//
	PipelineNodes.push_back(NewMeshNode);
	for(IPipelineListener *Listener : Listeners) {Listener->MeshNodeAdded(NewMeshNode);}
	return NewMeshNode;
}

AppNodePresenter *PipelinePresenter::AddAppNode()
{
	AppNodePresenter *NewAppNode = new AppNodePresenter;
	PipelineNodes.push_back(NewAppNode);
	//for(IPipelineListener *Listener : Listeners) {Listener->AppNodeAdded(NewAppNode);}
	return NewAppNode;
}

PipelinePresenter::~PipelinePresenter()
{
	for(NodePresenter *Node : PipelineNodes)
	{
		delete Node;
	}
	
	for(EdgePresenter *Edge : PipelineEdges)
	{
		delete Edge;
	}
}
