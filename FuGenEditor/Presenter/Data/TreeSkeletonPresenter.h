#ifndef TREE_SKELETON_PRESENTER_H
#define TREE_SKELETON_PRESENTER_H

#include <Data/TreeSkeleton.h>

#include <View/EdgeVisualizer/GL/GraphRenderer/GLLineStrip.h>

#include "TreeDataPresenter.h"


class TreeSkeletonPresenter : public TreeDataPresenter
{
private:
	//
	TreeNode *wrappedGraph;
	//
	std::list<IGLDrawable *> CreatedDrawables;
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
    TreeNode *GetSkeleton()
    {
        return wrappedGraph;
    }
	//
	void OnChanged(TreeNode *new_graph)
	{
		wrappedGraph = new_graph;
		//
		Changed = true;
		//
		NotifyChanged();
	}
	//
	TreeSkeletonPresenter()
	{}
	//
	~TreeSkeletonPresenter()
	{}
	/*
	 * End of class
	 */
};

#endif // TREE_SKELETON_PRESENTER_H

