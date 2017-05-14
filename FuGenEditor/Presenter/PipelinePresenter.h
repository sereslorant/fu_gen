#ifndef PIPELINE_PRESENTER_H
#define PIPELINE_PRESENTER_H

#include "Data/TreeDataPresenter.h"

#include "Data/TreeSkeletonPresenter.h"
#include "Data/TreeHypergraphPresenter.h"
#include "Data/TreeMeshPresenter.h"

#include "Elements/NodePresenter.h"
#include "Elements/EdgePresenter.h"

#include "Elements/Nodes/TurtleNodePresenter.h"
#include "Elements/Nodes/HypergraphNodePresenter.h"
#include "Elements/Nodes/MeshNodePresenter.h"
#include "Elements/Nodes/AppNodePresenter.h"

class IPipelineListener
{
public:
	//virtual void EdgeAdded(EdgePresenter *new_edge) = 0;
	//
	virtual void TurtleNodeAdded(TurtleNodePresenter *new_node) = 0;
	virtual void HypergraphNodeAdded(HypergraphNodePresenter *new_node) = 0;
	virtual void MeshNodeAdded(MeshNodePresenter *new_node) = 0;
	//
	IPipelineListener()
	{}
	//
	virtual ~IPipelineListener()
	{}
};

#include <View/PipelineEditor/FuGenPipelineEditor.h>

#include "ViewRefresher.h"

class PipelinePresenter : public IPipelineModel
{
private:
	FuGenGLView *GLView;
    PipelineVisualizer Visualizer;
	ViewRefresher viewRefresher;
	//
	std::list<NodePresenter *> PipelineNodes;
	std::list<EdgePresenter *> PipelineEdges;
	//
	std::list<IPipelineListener *> Listeners;
    //
	enum SpawnState
	{
		TURTLE,
		HYPERGRAPH,
		MESH
	};
	//
	SpawnState State = TURTLE;
	//
public:
	//
	void SetSpawnTurtle()
	{
		State = TURTLE;
	}
	//
	void SetSpawnHypergraph()
	{
		State = HYPERGRAPH;
	}
	//
	void SetSpawnMesh()
	{
		State = MESH;
	}
	//
	virtual IPipelineNodeModel *SpawnNode() override
	{
		switch(State)
		{
		case TURTLE:
			return AddTurtleNode();
		case HYPERGRAPH:
			return AddHypergraphNode();
		case MESH:
			return AddMeshNode();
		}
	}
	//
	virtual IPipelineEdgeModel *SpawnEdge(IPipelineNodeModel &begin_model,IPipelineNodeModel &end_model) override;
	//
	void AddListener(IPipelineListener *new_listener);
	//
	TurtleNodePresenter *AddTurtleNode();
	//
	HypergraphNodePresenter *AddHypergraphNode();
	//
	MeshNodePresenter *AddMeshNode();
	//
	AppNodePresenter *AddAppNode();
	//
	PipelineVisualizer &GetVisualizer()
	{
		return Visualizer;
	}
    //
    PipelinePresenter(FuGenGLView *gl_view)
        :GLView(gl_view),Visualizer(gl_view)
    {
		viewRefresher.SetView(GLView);
	}
    //
    virtual ~PipelinePresenter() override;
};

#endif // PIPELINE_PRESENTER_H

