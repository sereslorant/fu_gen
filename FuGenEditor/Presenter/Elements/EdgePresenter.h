#ifndef EDGE_PRESENTER_H
#define EDGE_PRESENTER_H

#include <View/EdgeVisualizer/FuGenGLView.h>

#include "../Data/TreeSkeletonPresenter.h"
#include "../Data/TreeHypergraphPresenter.h"
#include "../Data/TreeMeshPresenter.h"

class PipelineVisualizer : public ITreeDataVisitor, public IGLViewListener
{
private:
	FuGenGLView *GLView;
	TreeDataPresenter *CurrentPresenter = nullptr;
	//
public:
    //
    virtual void Visit(TreeSkeletonPresenter &skeleton_presenter) override
    {
		std::cout << "Draw skeleton" << std::endl;
		if(GLView != nullptr)
		{
			GLView->GetEdgeVisualizer().ChooseSkeleton();
			GLView->GetEdgeVisualizer().GetSkeletonRenderer().SetDrawable(&(skeleton_presenter.GetDrawableList()));
		}
    }
    //
    virtual void Visit(TreeHypergraphPresenter &hypergraph_presenter) override
    {
		std::cout << "Draw hypergraph" << std::endl;
		if(GLView != nullptr)
		{
			GLView->GetEdgeVisualizer().ChooseHypergraph();
			GLView->GetEdgeVisualizer().GetHypergraphRenderer().SetDrawable(&(hypergraph_presenter.GetDrawableList()));
		}
    }
    //
    virtual void Visit(TreeMeshPresenter &mesh_presenter) override
    {
		std::cout << "Draw mesh" << std::endl;
		if(GLView != nullptr)
		{
			GLView->GetEdgeVisualizer().ChooseMesh();
			GLView->GetEdgeVisualizer().GetMeshRenderer().SetDrawable(&(mesh_presenter.GetDrawableList()));
		}
    }
	//
	void SetCurrentPresenter(TreeDataPresenter *current_presenter)
	{
		CurrentPresenter = current_presenter;
		GLView->update();
	}
	//
	virtual void OnInitialization() override
	{}
	//
	virtual void OnDraw() override
	{
		if(CurrentPresenter != nullptr)
		{
			CurrentPresenter->Accept(*this);
		}
	}
    //
    PipelineVisualizer(FuGenGLView *gl_view)
        :GLView(gl_view)
    {
		if(GLView != nullptr)
		{
			GLView->AddListener(this);
		}
	}
    //
    virtual ~PipelineVisualizer()
	{}
};

#include <View/PipelineEditor/FuGenPipelineEdge.h>

class EdgePresenter : public IPipelineEdgeModel, public IPipelineEdgeListener
{
private:
	PipelineVisualizer *pipelineVisualizer;
	//
	FuGenPipelineEdge *PipelineEdge = nullptr;
	TreeDataPresenter &DataPresenter;
	//
public:
	//
	virtual void SetPipelineEdge(FuGenPipelineEdge *pipeline_edge) override
	{
		PipelineEdge = pipeline_edge;
		PipelineEdge->AddListener(this);
	}
	//
	virtual void OnClicked() override
	{
		pipelineVisualizer->SetCurrentPresenter(&DataPresenter);
	}
	//
	virtual void OnEndpointDeleted() override
	{}
	//
	virtual void OnDeleted() override
	{}
	//
	EdgePresenter(PipelineVisualizer *pipeline_visualizer,TreeDataPresenter &data_presenter)
		:pipelineVisualizer(pipeline_visualizer),DataPresenter(data_presenter)
	{}
	//
	virtual ~EdgePresenter() override
	{
		if(PipelineEdge != nullptr)
		{
			//PipelineEdge->RemoveModel(this);
			PipelineEdge->RemoveListener(this);
		}
	}
};

#endif // EDGE_PRESENTER_H
