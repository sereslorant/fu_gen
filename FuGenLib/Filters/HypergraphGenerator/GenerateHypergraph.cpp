
#include "GenerateHypergraph.h"


class AverageCalculator : public ITreeVisitor
{
private:
	vec4 Root;
	vec4 AvgVector = vec4(0.0,0.0,0.0);
	//
public:
	//
	const vec4 &GetVector()
	{
		return AvgVector;
	}
	//
	virtual void Visit(TrunkNode *node) override
	{
		AvgVector += node->GetPosition() - Root;
	}
	//
	virtual void Visit(PolygonNode *node) override
	{}
	//
	AverageCalculator(const vec4 &root)
		:Root(root)
	{}
	//
	virtual ~AverageCalculator(){}
};

class BranchCounter : public ITreeVisitor
{
private:
	unsigned int NumBranches = 0;
	//
public:
	unsigned int GetNumBranches()
	{return NumBranches;}
	//
	virtual void Visit(TrunkNode *node) override
	{NumBranches++;}
	//
	virtual void Visit(PolygonNode *node) override
	{}
	//
	BranchCounter()
	{}
	//
	virtual ~BranchCounter() override
	{}
};

class ICurveStrategy
{
public:
	virtual float GetBeginParam() const = 0;
	virtual float GetEndParam() const = 0;

	virtual ICurve *GetCurve() = 0;
	virtual ICurve *ConstructCurve() = 0;

	virtual void Reset(const vec4 &begin_point,const vec4 &begin_dir) = 0;
	virtual void AddControlPoint(const vec4 &point) = 0;
	virtual void Finish(const vec4 &end_point,const vec4 &final_dir) = 0;

	ICurveStrategy(){}
	virtual ~ICurveStrategy(){}
};

class CatmullRomStrategy : public ICurveStrategy
{
private:
	CatmullRom Spline;
	float NextParam;

	const float DELTA_NEXT_PARAM = 1.0;

public:

	virtual float GetBeginParam() const override
	{
		return 0.0;
	}

	virtual float GetEndParam() const override
	{
		return NextParam;
	}

	virtual ICurve *GetCurve() override
	{
		return &Spline;
	}

	virtual ICurve *ConstructCurve() override
	{
		return Spline.Clone();
	}

	virtual void Reset(const vec4 &begin_point,const vec4 &begin_dir) override
	{
		NextParam = DELTA_NEXT_PARAM;

		//Spline = CatmullRom(begin_dir,glm::vec3(0.0,0.0,0.0));
		Spline.cps.clear();
		Spline.ts.clear();
		Spline.Velocity.clear();

		//std::cout << begin_dir.x << " " << begin_dir.y << " " << begin_dir.z << std::endl;

		Spline.SetInitVelocity(begin_dir);
		Spline.AddControlPoint(begin_point, -0.25);

		//std::cout << Spline.Velocity[0].x << " " << Spline.Velocity[0].y << " " << Spline.Velocity[0].z << std::endl;
	}

	virtual void AddControlPoint(const vec4 &point) override
	{
		Spline.AddControlPoint(point,NextParam);
		NextParam += DELTA_NEXT_PARAM;
		//std::cout << Spline.Velocity[0].x << " " << Spline.Velocity[0].y << " " << Spline.Velocity[0].z << std::endl;
	}

	virtual void Finish(const vec4 &end_point,const vec4 &final_dir) override
	{
		Spline.SetEndVelocity(final_dir);
		Spline.AddControlPoint(end_point,NextParam + 0.5);
	}

	CatmullRomStrategy()
		:Spline(vec4(0.0,0.0,0.0),vec4(0.0,0.0,0.0))
	{}

	virtual ~CatmullRomStrategy() override
	{}
};

class SegmentGenerator
{
private:
	TrunkNode *Parent;
	vec4 ParentDir;

	ICurveStrategy *CurveStrategy = nullptr;

	float InitSpeed;
	float EndSpeed;

	float ParentWeight;

	bool First = true;
	bool BeginSegment = false;
	float Radius;
	Sphere JunctionSphere;

	vec4 Direction;
	vec4 BeginDir;
public:

	TreeHypergraph::Branch *CreateBranch()
	{
		TreeHypergraph::Branch *Branch = new TreeHypergraph::Branch;

		Branch->Curve = CurveStrategy->ConstructCurve();

		Branch->t_Begin = CurveStrategy->GetBeginParam();
		Branch->t_End = CurveStrategy->GetEndParam();

		Branch->Up = -1.0f*ParentDir;

		Branch->Width = Radius;

		return Branch;
	}

	const vec4 &GetDirection()
	{
		return Direction;
	}

	void InitStrategy(TrunkNode *node)
	{
		if(BeginSegment)
		{
			if(First)
			{
				CurveStrategy->Reset(Parent->GetPosition(),vec4(0.0,0.0,0.0));
				ParentDir = vec4(0.0,-1.0,0.0);
				First = false;
			}
			else
			{
				vec4 NextDir = normalize(node->GetPosition() - JunctionSphere.Center);
				ParentDir = normalize(Parent->GetPosition() - JunctionSphere.Center);
				//
				BeginDir = normalize((1.0f-ParentWeight)*NextDir + ParentWeight*ParentDir);
				//
				CurveStrategy->Reset(JunctionSphere.Center,InitSpeed*BeginDir);
			}

			BeginSegment = false;
		}
	}

	void AddCtrlPoint(TrunkNode *node)
	{
		InitStrategy(node);

		//vec4 Correction = CorrectionLength*BeginDir;
		CurveStrategy->AddControlPoint(node->GetPosition() /*+ Correction*/);

		//CorrectionLength *= CorrectionDecay;
	}

	void AddEnd(TrunkNode *node)
	{
		InitStrategy(node);

		const vec4 &c_pos = node->GetPosition();

		AverageCalculator Avg(node->GetPosition());
		for(auto I = node->GetChildrenBegin();I != node->GetChildrenEnd();I++)
		{
			(*I)->Accept(&Avg);
		}

		Direction = Avg.GetVector();
		if(length(Direction) < 1e-4)
		{
			Direction = vec4(0.0,1.0,0.0);
		}
		else
		{
			Direction = normalize(Direction);
		}

		CurveStrategy->Finish(c_pos,EndSpeed*Direction);
	}

	void Reset(TrunkNode *parent,float radius,const Sphere &junction_sphere,bool first)
	{
		Parent = parent;
		First = first;
		Radius = radius;
		JunctionSphere = junction_sphere;

		BeginSegment = true;
	}

	SegmentGenerator(ICurveStrategy *curve_strategy,float init_speed,float end_speed,float parent_weight)
		:Parent(nullptr),CurveStrategy(curve_strategy),InitSpeed(init_speed),EndSpeed(end_speed),ParentWeight(parent_weight),JunctionSphere(vec4(0.0,0.0,0.0),0.0)
	{}

	~SegmentGenerator()
	{}
};

#include <iostream>

class HypergraphGeneratorState : public ITreeVisitor
{
private:

	struct RootState
	{
		TrunkNode *Root;
		unsigned int NumBranches;
		unsigned int BranchesCompleted = 0;
		float Radius;
		bool BeginTree;

		TreeHypergraph::Branch *Branch;
		TreeHypergraph::Junction *Junction;

		RootState(TrunkNode *root,float radius,float sphere_radius,bool begin_tree,TreeHypergraph::Branch *branch = nullptr)
			:Root(root),Radius(radius),BeginTree(begin_tree),Branch(branch)
		{
			BranchCounter CntBranches;
			Root->ForeachChildrenAccept(&CntBranches);

			NumBranches = CntBranches.GetNumBranches();

			Junction = new TreeHypergraph::Junction;
			Junction->Root = Branch;
			Junction->JunctionSphere.Radius = sphere_radius;
		}
	};
	//
	float Radius;
	float RadiusDecay;
	//
	bool Begin = false;
	bool First = true;
	//
	SegmentGenerator Puszcsy;
	//
	std::list<RootState> Roots;
	//
	CatmullRomStrategy CR_Strategy;
	TreeHypergraph *Result = nullptr;
	//
public:
	//
	virtual void Visit(TrunkNode *node) override
	{
		if(First)
		{
			Roots.push_back({node,Radius,Radius,true});
			Begin = true;
		}
		//
		if(Begin)
		{
			Puszcsy.Reset(Roots.back().Root,Roots.back().Radius,Roots.back().Junction->JunctionSphere,Roots.back().BeginTree);
			Begin = false;
		}
		//
		BranchCounter CntBranches;
		node->ForeachChildrenAccept(&CntBranches);
		//
		if(CntBranches.GetNumBranches() == 1)
		{
			if(!First)
			{
				Puszcsy.AddCtrlPoint(node);
			}
			else
			{
				First = false;
			}
		}
		else
		{
			if(!First)
			{
				Puszcsy.AddEnd(node);
				//
				TreeHypergraph::Branch *Branch = Puszcsy.CreateBranch();
				Result->Branches.push_back(Branch);
				//
				Roots.back().Junction->Children.push_back(Branch);
				Roots.back().BranchesCompleted++;
				//
				float NewRadius = RadiusDecay*Roots.back().Radius;
				if(Roots.back().BranchesCompleted == Roots.back().NumBranches)
				{
					Result->Junctions.push_back(Roots.back().Junction);
					Roots.pop_back();
				}
				//
				if(CntBranches.GetNumBranches() != 0)
				{
					Roots.push_back({node,NewRadius,NewRadius,false,Branch});
					Roots.back().Junction->JunctionSphere.Center = node->GetPosition();
				}
				//
				Begin = true;
			}
			else
			{
				First = false;
			}
		}
	}
	//
	virtual void Visit(PolygonNode *node) override
	{}
	//
	TreeHypergraph *GetResult()
	{
		return Result;
	}
	//
	HypergraphGeneratorState(float radius,float radius_decay,float init_speed,float end_speed,float parent_weight)
		:Radius(radius),RadiusDecay(radius_decay),Puszcsy(&CR_Strategy,init_speed,end_speed,parent_weight)
	{
		Result = new TreeHypergraph;
	}
	//
	virtual ~HypergraphGeneratorState() override
	{}
};

void GenerateHypergraph::Draw(TreeNode *node,TreeHypergraph *&result)
{
	HypergraphGeneratorState State(Radius,RadiusDecay,InitSpeed,EndSpeed,ParentWeight);
	
    result = State.GetResult();

    std::list<TreeNode *> NodeList;
    NodeList.push_back(node);
    do
    {
        for(auto I = NodeList.begin();I != NodeList.end();)
        {
            TreeNode *Node = *I;
            NodeList.pop_front();

            Node->Accept(&State);

            for(auto J = Node->GetChildrenBegin();J != Node->GetChildrenEnd();J++)
            {
                NodeList.push_front(*J);
            }

            I = NodeList.begin();
        }

    } while(NodeList.size() != 0);

    result->Prepare();
}
