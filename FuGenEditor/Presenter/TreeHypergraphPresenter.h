#ifndef TREE_HYPERGRAPH_PRESENTER_H
#define TREE_HYPERGRAPH_PRESENTER_H

#include <Data/TreeHypergraph.h>

#include <View/EdgeVisualizer/GL/GLDrawableList.h>
#include <View/EdgeVisualizer/GL/HypergraphRenderer/GLHypergraphRenderer.h>

class TreeHypergraphPresenter
{
private:
	//
	struct BranchPresenter
	{
		TreeHypergraph::Branch *wrappedBranch = nullptr;
		GLGeneralizedCylinder *branchRepresentation = nullptr;
		//
		void RefreshBranch()
		{
			std::vector<CR_VertexData> ControlPoints(wrappedBranch->Curve->GetNumControlPoints());
			for(int i=0;i < ControlPoints.size();i++)
			{
				ControlPoints[i].Position = wrappedBranch->Curve->GetCtrlPosition(i);
				ControlPoints[i].Velocity = wrappedBranch->Curve->GetCtrlDerivative(i);
				ControlPoints[i].Time = wrappedBranch->Curve->GetCtrlParameter(i);
			}
			branchRepresentation->Fill(&ControlPoints[0],
									   ControlPoints.size(),
									   sizeof(CR_VertexData)
									  );
			branchRepresentation->SetParams(wrappedBranch->t_Begin,
											wrappedBranch->t_End,
											wrappedBranch->Width
										   );
		}
		//
		BranchPresenter()
		{}
		//
		~BranchPresenter()
		{
			if(branchRepresentation != nullptr)
			{
				delete branchRepresentation;
			}
		}
	};
	//
	TreeHypergraph *wrappedHypergraph = nullptr;
	//
	std::list<BranchPresenter> branchPresenters;
	//
	GLDrawableList DrawableList;
	//
	IGLRenderer *HypergraphRenderer = nullptr;
	IGLShaderProgram *HypergraphShaderProgram = nullptr;
	//
public:
	//
	void SetPrimitiveRenderer(IGLRenderer *hypergraph_renderer,IGLShaderProgram *hypergraph_shader_program)
	{
		HypergraphRenderer = hypergraph_renderer;
		HypergraphShaderProgram = hypergraph_shader_program;
	}
	//
	void OnChanged(TreeHypergraph *new_hypergraph)
	{
		wrappedHypergraph = new_hypergraph;
		//
		if(branchPresenters.size() != wrappedHypergraph->Branches.size())
		{
			branchPresenters.resize(wrappedHypergraph->Branches.size());
		}
		//
		auto branchPresenterIterator = branchPresenters.begin();
		for(TreeHypergraph::Branch *Branch : wrappedHypergraph->Branches)
		{
			BranchPresenter &currentPresenter = *branchPresenterIterator;
			currentPresenter.wrappedBranch = Branch;
			if(currentPresenter.branchRepresentation == nullptr)
			{
				currentPresenter.branchRepresentation = new GLGeneralizedCylinder(nullptr,0,*HypergraphShaderProgram);
				DrawableList.Add(currentPresenter.branchRepresentation);
			}
			currentPresenter.RefreshBranch();
			//
			branchPresenterIterator++;
		}
		//
		HypergraphRenderer->SetDrawable(&DrawableList);
	}
	//
	TreeHypergraphPresenter()
	{}
	//
	~TreeHypergraphPresenter()
	{}
};

#endif // TREE_HYPERGRAPH_PRESENTER_H
