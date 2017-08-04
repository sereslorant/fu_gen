#ifndef TREE_DEMO_H
#define TREE_DEMO_H

#include "Demo3D.h"

#include <Data/TreeHypergraph.h>
#include <Data/MultiMesh.h>

class TreeDemo : public Demo3D
{
protected:
	TreeNode		*TreeSkeleton	= nullptr;
	TreeHypergraph	*Hypergraph		= nullptr;
	MultiMesh		*Mesh			= nullptr;
	
	/*
	 * TODO: Át kell majd írnu GLuintre!
	 */
	unsigned int TextureId = 0;
	
	enum DemoState
	{
		DRAW_SKELETON,
		DRAW_HYPERGRAPH,
		DRAW_MESH,
	};
	
	DemoState State = DRAW_SKELETON;
	
	TreeDemo()
	{}
	
public:

	virtual void ChangeState() override
	{
		if(State == DRAW_SKELETON)
			{State = DRAW_HYPERGRAPH;}
		else if(State == DRAW_HYPERGRAPH)
			{State = DRAW_MESH;}
		else if(State == DRAW_MESH)
			{State = DRAW_SKELETON;}
	}
	
	virtual void Draw() override;
	
	virtual ~TreeDemo() override
	{
		delete TreeSkeleton;
		delete Hypergraph;
		delete Mesh;
	}
};

#endif // TREE_DEMO_H
