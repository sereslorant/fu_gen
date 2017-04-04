#ifndef TREE_SKELETON_H
#define TREE_SKELETON_H

class TrunkNode;
class PolygonNode;

class ITreeVisitor
{
public:
	//
	virtual void Visit(TrunkNode *node) = 0;
	virtual void Visit(PolygonNode *node) = 0;
	//
	ITreeVisitor(){}
	virtual ~ITreeVisitor(){}
};

#include <list>
#include <vector>

/*
 * Március 24
 */
class TreeNode
{
private:
	int Id = -1;
	TreeNode *Parent = nullptr;
	std::list<TreeNode *> Children;
	//
public:
	//
	virtual void Accept(ITreeVisitor *visitor) = 0;
	//
	void ForeachChildrenAccept(ITreeVisitor *visitor)
	{
		for(TreeNode *I : Children)
		{I->Accept(visitor);}
	}
	//
	TreeNode *GetParent()
	{
		return Parent;
	}
	//
	unsigned int GetNumChildren()
	{
		return Children.size();
	}
	//
	std::list<TreeNode *>::iterator GetChildrenBegin()
	{
		return Children.begin();
	}
	//
	std::list<TreeNode *>::iterator GetChildrenEnd()
	{
		return Children.end();
	}
	//
	void AddChild(TreeNode *child)
	{
		child->Id = Children.size();
		child->Parent = this;
		//
		Children.push_back(child);
	}
	//
	TreeNode()
	{}
	//
	virtual ~TreeNode()
	{
		for(auto I : Children)
		{
			delete I;
		}
	}
};

#include <glmath.hpp>

/*
 * Március 24
 */
class TrunkNode : public TreeNode
{
private:
	dvec4 Position;
	//float Width = 0;
	//
public:
	//
	virtual void Accept(ITreeVisitor *visitor) override
	{
		visitor->Visit(this);
	}
	//
	const dvec4 &GetPosition()
	{
		return Position;
	}
	/*
	float GetWidth()
	{
		return Width;
	}
	*/
	TrunkNode(const dvec4 &position/*,float width*/)
		:Position(position)//,Width(width)
	{}
	//
	virtual ~TrunkNode() override
	{}
};

/*
 * Március 24
 */
class PolygonNode : public TreeNode
{
private:
	std::vector<dvec4> VertexArray;

	template<class Iterator>
	PolygonNode(Iterator array_begin,Iterator array_end,unsigned int array_size)
		:VertexArray(array_size)
	{
		auto I = array_begin;
		for(unsigned int i=0;i < VertexArray.size() && I != array_end;i++,I++)
		{
			VertexArray[i] = *I;
		}
	}

public:

	virtual void Accept(ITreeVisitor *visitor) override
	{
		visitor->Visit(this);
	}

	unsigned int Size() const {return VertexArray.size();}
	const dvec4 &GetVertex(unsigned int i) const {return VertexArray[i];}
	const dvec4 *GetArray() const {return &VertexArray[0];}

	class PolygonNodeBuilder
	{
	private:
		std::list<dvec4> VertexList;
		TreeNode *Parent;
		//
	public:
		//
		PolygonNodeBuilder &AddVertex(const dvec4 &vertex)
		{
			VertexList.push_back(vertex);
			return *this;
		}
		//
		void Construct(TreeNode *&dest)
		{
			dest = new PolygonNode(VertexList.begin(),VertexList.end(),VertexList.size());
			//
			Parent->AddChild(dest);
		}
		//
		PolygonNodeBuilder(TreeNode *parent)
			:Parent(parent)
		{}
		//
		~PolygonNodeBuilder()
		{}
	};

	virtual ~PolygonNode() override
	{}
};

#endif // TREE_SKELETON_H
