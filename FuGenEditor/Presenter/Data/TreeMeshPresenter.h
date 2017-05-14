#ifndef TREE_MESH_PRESENTER_H
#define TREE_MESH_PRESENTER_H

#include <Data/MultiMesh.h>

#include <View/EdgeVisualizer/GL/MeshRenderer/GLTriangleList.h>

#include "TreeDataPresenter.h"

class TreeMeshPresenter : public TreeDataPresenter
{
private:
	//
	struct BranchPresenter
	{
		Mesh<vec4>  *wrappedBranch;
		GLTriangleList *branchRepresentation = nullptr;
		//
		void RefreshBranch();
		//
		BranchPresenter()
		{}
		//
		~BranchPresenter()
		{
			if(branchRepresentation != nullptr)
				{delete branchRepresentation;}
		}
	};
	//
	struct JunctionPresenter
	{
		MyMesh  *wrappedJunction;
		GLTriangleList *junctionRepresentation = nullptr;
		//
		void RefreshBranch();
		//
		JunctionPresenter()
		{}
		//
		~JunctionPresenter()
		{
			if(junctionRepresentation != nullptr)
				{delete junctionRepresentation;}
		}
	};
	//
	MultiMesh *wrappedMultiMesh;
	std::list<BranchPresenter> branchPresenters;
	std::list<JunctionPresenter> junctionPresenters;
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
	void OnChanged(MultiMesh *new_multi_mesh)
	{
		wrappedMultiMesh = new_multi_mesh;
		//
		Changed = true;
		//
		NotifyChanged();
	}
	//
	TreeMeshPresenter()
	{}
	//
	~TreeMeshPresenter()
	{}
};

#endif // TREE_MESH_PRESENTER_H
