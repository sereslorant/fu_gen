#ifndef CONNECTION_VISITOR_H
#define CONNECTION_VISITOR_H

#include "../Data/TreeDataPresenter.h"

#include <View/PipelineEditor/FuGenPipelineNode.h>

class ConnectionVisitor : public ITreeDataVisitor
{
public:
	enum TreeDataType
	{
		TREE_SKELETON,
		TREE_HYPERGRAPH,
		TREE_MESH,
	};
	//
private:
	TreeDataType DataType;
	bool Connectable = false;
	//
public:
	//
	bool IsConnectable()
	{
		return Connectable;
	}
	//
	virtual void Visit(TreeSkeletonPresenter &skeleton_presenter) override
	{
		Connectable = DataType == TREE_SKELETON;
	}
	//
	virtual void Visit(TreeHypergraphPresenter &hypergraph_presenter) override
	{
		Connectable = DataType == TREE_HYPERGRAPH;
	}
	//
	virtual void Visit(TreeMeshPresenter &mesh_presenter) override
	{
		Connectable = DataType == TREE_MESH;
	}
	//
	ConnectionVisitor(TreeDataType data_type)
		:DataType(data_type)
	{}
	//
	virtual ~ConnectionVisitor() override
	{}
};

#endif // CONNECTION_VISITOR_H
