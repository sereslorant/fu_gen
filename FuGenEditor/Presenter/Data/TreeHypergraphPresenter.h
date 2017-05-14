#ifndef TREE_HYPERGRAPH_PRESENTER_H
#define TREE_HYPERGRAPH_PRESENTER_H

#include <Data/TreeHypergraph.h>

#include <View/EdgeVisualizer/GL/HypergraphRenderer/GLHypergraphRenderer.h>

#include "TreeDataPresenter.h"

class TreeHypergraphPresenter : public TreeDataPresenter
{
private:
	//
	struct BranchPresenter
	{
		TreeHypergraph::Branch *wrappedBranch = nullptr;
		GLGeneralizedCylinder *branchRepresentation = nullptr;
		//
		void RefreshBranch();
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
	std::list<BranchPresenter> branchPresenters;
	//
	virtual void Refresh() override;
	//
public:
    //
    virtual void Accept(ITreeDataVisitor &visitor) override
    {
        visitor.Visit(*this);
    }
    //
    TreeHypergraph *GetHypergraph()
	{
		return wrappedHypergraph;
	}
	//
	void OnChanged(TreeHypergraph *new_hypergraph)
	{
		wrappedHypergraph = new_hypergraph;
		//
		Changed = true;
		//
		NotifyChanged();
	}
	//
	TreeHypergraphPresenter()
	{}
	//
	~TreeHypergraphPresenter()
	{}
};

#endif // TREE_HYPERGRAPH_PRESENTER_H
