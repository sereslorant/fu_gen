
#include "TreeHypergraphPresenter.h"


void TreeHypergraphPresenter::BranchPresenter::RefreshBranch()
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

void TreeHypergraphPresenter::Refresh()
{
	if(ShaderProgram != nullptr)
	{
		DrawableList.Clear();
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
				currentPresenter.branchRepresentation = new GLGeneralizedCylinder(nullptr,0,*ShaderProgram);
			}
			DrawableList.Add(currentPresenter.branchRepresentation);
			currentPresenter.RefreshBranch();
			//
			branchPresenterIterator++;
		}
	}
}
