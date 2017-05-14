
#include "TreeSkeletonPresenter.h"


class GraphVisitorBase : public ITreeVisitor
{
public:
    //
    virtual void Visit(TrunkNode *node) override
    {
        //
    }
    //
    virtual void Visit(PolygonNode *node) override
    {
        //
    }
    //
    GraphVisitorBase()
    {}
    //
    virtual ~GraphVisitorBase() override
    {}
    /*
     * End of class
     */
};

class GraphBfsBase : public GraphVisitorBase
{
public:
    //
    void Search(TreeNode *node)
    {
        std::list<TreeNode *> NodeList;
        NodeList.push_back(node);

        for(auto I = NodeList.begin();I != NodeList.end();)
        {
            (*I)->Accept(this);

            for(auto J = (*I)->GetChildrenBegin();J != (*I)->GetChildrenEnd();J++)
            {
                NodeList.push_back(*J);
            }

            I++;
            NodeList.pop_front();
        }
    }
    //
    GraphBfsBase()
    {}
    //
    virtual ~GraphBfsBase() override
    {}
    /*
     * End of class
     */
};

class EdgeCounter : public GraphBfsBase
{
private:
	//
	class LineVertexCounter : public GraphVisitorBase
	{
	public:
		unsigned int NumVertices = 0;
		//
		virtual void Visit(TrunkNode *node) override
		{
			NumVertices += 2;
		}
		//
		LineVertexCounter()
		{}
		//
		virtual ~LineVertexCounter() override {}
	};
	//
	LineVertexCounter VertexCounter;
	//
public:
	//
	unsigned int NumVertices()
	{
		return VertexCounter.NumVertices;
	}
	//
	virtual void Visit(TrunkNode *node) override
	{
		for(auto I = node->GetChildrenBegin();I != node->GetChildrenEnd();I++)
		{
			(*I)->Accept(&VertexCounter);
		}
	}
	//
	virtual void Visit(PolygonNode *node) override
	{
		for(int i=0;i < node->Size();i++)
		{
			const vec4 &pos1 = node->GetVertex(i);
		}
	}
	//
	EdgeCounter()
	{}
	//
	virtual ~EdgeCounter() override
	{}
};

class GraphSampler : public GraphBfsBase
{
private:
	//
	class LineSampler : public GraphVisitorBase
	{
	private:
		TrunkNode *Parent;
		unsigned int &Counter;
		std::vector<vec4> &Vertices;
		//
	public:
		//
		virtual void Visit(TrunkNode *node) override
		{
			const vec4 &p_pos = Parent->GetPosition();
			const vec4 &c_pos = node->GetPosition();
			//
			Vertices[Counter] = p_pos;
			Counter++;
			Vertices[Counter] = c_pos;
			Counter++;
		}
		//
		LineSampler(TrunkNode *parent,unsigned int &counter,std::vector<vec4> &vertices)
			:Parent(parent),Counter(counter),Vertices(vertices)
		{}
		//
		virtual ~LineSampler() override
		{}
	};
	//
	unsigned int Counter = 0;
	std::vector<vec4> &Vertices;
	//
	IGLShaderProgram *SkeletonShaderProgram;
	std::list<IGLDrawable *> &CreatedDrawables;
	GLDrawableList &DrawableList;
	//
public:
	//
	virtual void Visit(TrunkNode *node) override
	{
		LineSampler Puszcsy(node,Counter,Vertices);
		//
		for(auto I = node->GetChildrenBegin();I != node->GetChildrenEnd();I++)
		{
			(*I)->Accept(&Puszcsy);
		}
	}
	//
	virtual void Visit(PolygonNode *node) override
	{
		std::vector<vec4> Vertices(node->Size());
		//
		for(int i=0;i < node->Size();i++)
		{
			Vertices[i] = node->GetVertex(i);
		}
		//
		GLTriangleFan *NewPolygon = new GLTriangleFan(nullptr,0,*SkeletonShaderProgram);
		NewPolygon->Fill(&Vertices[0],Vertices.size(),sizeof(vec4));
		CreatedDrawables.push_back(NewPolygon);
		DrawableList.Add(NewPolygon);
	}
	//
	GraphSampler(std::vector<vec4> &vertices,IGLShaderProgram *skeleton_shader_program,std::list<IGLDrawable *> &created_drawables,GLDrawableList &drawable_list)
		:Vertices(vertices),SkeletonShaderProgram(skeleton_shader_program),CreatedDrawables(created_drawables),DrawableList(drawable_list)
	{}
	//
	virtual ~GraphSampler() override
	{}
};

void TreeSkeletonPresenter::Refresh()
{
	if(ShaderProgram != nullptr)
	{
		DrawableList.Clear();
		//
		for(IGLDrawable *Drawable : CreatedDrawables)
		{
			delete Drawable;
		}
		CreatedDrawables.clear();
		//
		EdgeCounter edgeCounter;
		edgeCounter.Search(wrappedGraph);
		//
		std::vector<vec4> Vertices(edgeCounter.NumVertices());
		//
		GraphSampler graphSampler(Vertices,ShaderProgram,CreatedDrawables,DrawableList);
		graphSampler.Search(wrappedGraph);
		//
		GLLineList *LineList = new GLLineList(nullptr,0,*ShaderProgram);
		LineList->Fill(&Vertices[0],Vertices.size(),sizeof(vec4));
		CreatedDrawables.push_back(LineList);
		DrawableList.Add(LineList);
	}
}
