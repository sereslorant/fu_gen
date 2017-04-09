#ifndef GENERATE_HYPERGRAPH_H
#define GENERATE_HYPERGRAPH_H

#include "../Data/TreeSkeleton.h"
#include "../Data/TreeHypergraph.h"

/*
 * Április 14
 */
class GenerateHypergraph : public ITreeVisitor
{
private:

	class Average : public ITreeVisitor
	{
	private:
		vec4 Root;

		vec4 AvgVector = vec4(0.0,0.0,0.0);

	public:

		const vec4 &GetVector(){return AvgVector;}

		virtual void Visit(TrunkNode *node) override
		{AvgVector += node->GetPosition() - Root;}

		virtual void Visit(PolygonNode *node) override
		{}

		Average(const vec4 &root)
			:Root(root)
		{}
		virtual ~Average(){}
	};

	class CountBranches : public ITreeVisitor
	{
	private:
		unsigned int NumBranches = 0;

	public:
		unsigned int GetNumBranches()
		{return NumBranches;}

		virtual void Visit(TrunkNode *node) override
		{NumBranches++;}

		virtual void Visit(PolygonNode *node) override
		{}

		CountBranches()
		{}

		virtual ~CountBranches() override
		{}
	};

	float Radius = 20.0;
	float Weight = 1.0;

	//float Scale = 0.65;
	float Scale = 0.75;

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

	class GenerateSegment
	{
	private:
		TrunkNode *Parent;
		vec4 ParentDir;

		ICurveStrategy *CurveStrategy = nullptr;

		float InitVelocity = 10.0;
		float EndVelocity= 5.0;

		float Displacement = 5.0;

		const float DEF_CORRECTION = 4.0;

		float CorrectionDecay = 0.7;
		float CorrectionLength = DEF_CORRECTION;

		float ParentWeight = 0.7;

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

			Branch->Width = /*JunctionSphere.Radius;*/Radius;

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

					//std::cout << NextDir.x << ";" << NextDir.y << ";" << NextDir.z << "\n";
					//std::cout << ParentDir.x << ";" << ParentDir.y << ";" << ParentDir.z << "\n";

					BeginDir = normalize((1.0f-ParentWeight)*NextDir + ParentWeight*ParentDir);

					//std::cout << BeginDir.x << ";" << BeginDir.y << ";" << BeginDir.z << "\n" << std::endl;
					//vec4 BeginPos = JunctionSphere.Center + JunctionSphere.Radius * BeginDir;
					//CurveStrategy->Reset(BeginPos,BeginDir);
					CurveStrategy->Reset(JunctionSphere.Center + Displacement*BeginDir,InitVelocity*BeginDir);
				}

				BeginSegment = false;
			}
		}

		void AddCtrlPoint(TrunkNode *node)
		{
			InitStrategy(node);

			vec4 Correction = CorrectionLength*BeginDir;
			CurveStrategy->AddControlPoint(node->GetPosition() + Correction);

			CorrectionLength *= CorrectionDecay;
		}

		void AddEnd(TrunkNode *node)
		{
			InitStrategy(node);

			const vec4 &c_pos = node->GetPosition();

			Average Avg(node->GetPosition());
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

			CurveStrategy->Finish(c_pos,EndVelocity*Direction);
		}

		void Reset(TrunkNode *parent,float radius,const Sphere &junction_sphere,bool first)
		{
			Parent = parent;
			First = first;
			Radius = radius;
			JunctionSphere = junction_sphere;
			CorrectionLength = DEF_CORRECTION;

			BeginSegment = true;
			//CurveStrategy->Reset(Parent->GetPosition());
		}

		GenerateSegment(ICurveStrategy *curve_strategy)
			:Parent(nullptr),CurveStrategy(curve_strategy),JunctionSphere(vec4(0.0,0.0,0.0),0.0)//,Radius(0.0),Weight(0.0)//,addCtrlPoint(this),addEnd(this)
		{}

		~GenerateSegment()
		{}
	};

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
			:Root(root),Branch(branch),Radius(radius),BeginTree(begin_tree)
		{
			CountBranches CntBranches;
			Root->ForeachChildrenAccept(&CntBranches);

			NumBranches = CntBranches.GetNumBranches();

			Junction = new TreeHypergraph::Junction;
			Junction->Root = Branch;
			Junction->JunctionSphere.Radius = sphere_radius;
		}
	};

	bool Begin = false;
	bool First = false;

	GenerateSegment Puszcsy;

	std::list<RootState> Roots;

	CatmullRomStrategy CR_Strategy;

	TreeHypergraph *Result = nullptr;

public:

	virtual void Visit(TrunkNode *node) override
	{
		if(First)
		{
			Roots.push_back({node,Radius,Radius,true});
			Begin = true;
		}

		if(Begin)
		{
			Puszcsy.Reset(Roots.back().Root,Roots.back().Radius,Roots.back().Junction->JunctionSphere,Roots.back().BeginTree/*Roots.back().Radius,Weight*/);
			Begin = false;
		}

		CountBranches CntBranches;
		node->ForeachChildrenAccept(&CntBranches);

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

				TreeHypergraph::Branch *Branch = Puszcsy.CreateBranch();
				Result->Branches.push_back(Branch);

				Roots.back().Junction->Children.push_back(Branch);
				Roots.back().BranchesCompleted++;

				float NewRadius = Scale*Roots.back().Radius;
				if(Roots.back().BranchesCompleted == Roots.back().NumBranches)
				{
					Result->Junctions.push_back(Roots.back().Junction);
					Roots.pop_back();
				}

				if(CntBranches.GetNumBranches() != 0)
				{
					Roots.push_back({node,NewRadius,/*Radius*/NewRadius,false,Branch});
					Roots.back().Junction->JunctionSphere.Center = node->GetPosition() + (NewRadius/1.5f)*Puszcsy.GetDirection();
				}

				Begin = true;
			}
			else
			{
				First = false;
			}
		}
	}

	virtual void Visit(PolygonNode *node) override
	{
		for(int i=0;i < node->Size();i++)
		{
			const vec4 &pos1 = node->GetVertex(i);
		}
	}

	void Draw(TreeNode *node,TreeHypergraph *&result)
	{
		result = new TreeHypergraph;

		Result = result;

		std::list<TreeNode *> NodeList;
		NodeList.push_back(node);

		First = true;
		do
		{
			for(auto I = NodeList.begin();I != NodeList.end();)
			{
				TreeNode *Node = *I;
				NodeList.pop_front();

				Node->Accept(this);

				for(auto J = Node->GetChildrenBegin();J != Node->GetChildrenEnd();J++)
				{
					NodeList.push_front(*J);
				}

				I = NodeList.begin();
			}

		} while(NodeList.size() != 0);

		Result->Prepare();
	}

	GenerateHypergraph()
		:Puszcsy(&CR_Strategy)
	{}

	virtual ~GenerateHypergraph()
	{}
};

#endif // GENERATE_HYPERGRAPH_H
