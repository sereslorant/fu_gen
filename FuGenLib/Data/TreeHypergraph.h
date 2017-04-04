#ifndef TREE_HYPERGRAPH_H
#define TREE_HYPERGRAPH_H

#include "../Utils/CatmullRom.h"

#include <algorithm>

/*
 * Április 28
 */
class TreeHypergraph
{
public:
	//
	struct Branch
	{
		ICurve *Curve;
		float Width;
		//
		float t_Begin;
		float t_End;
		//
		vec4 Up;
		//
		unsigned int Id;
		//
		~Branch()
		{delete Curve;}
	};
	//
	struct Junction
	{
		Branch *Root;
		std::list<Branch *> Children;
		//
		Sphere JunctionSphere;
		//
		unsigned int Id;
		//
		Junction()
			:JunctionSphere(vec4(0.0,0.0,0.0),0.0)
		{}
	};
	//
//private:
	std::list<Branch *> Branches;
	std::list<Junction *> Junctions;
	//
//public:
	//
	void Prepare()
	{
		unsigned int BranchId = 0;
		for(Branch *B : Branches)
		{
			B->Id = BranchId;
			BranchId++;
		}
		//
		unsigned int JunctionId = 0;
		for(Junction *J : Junctions)
		{
			float dt_min = 1.0/10.0;
			//
			Sphere modifiedJunctionSphere(J->JunctionSphere.Center,J->JunctionSphere.Radius * 1.2);
			//
			std::list<float> Roots;
			if(J->Root != nullptr)
			{
				float t0_0 = J->Root->t_Begin;
				float t0_fin = J->Root->t_End;
				//
				//if(BisectionMethod(*J->Root->Curve,t0_0,t0_fin,dt_min,J->JunctionSphere,Roots))
				if(BisectionMethod(*J->Root->Curve,t0_0,t0_fin,dt_min,modifiedJunctionSphere,Roots))
				{
					J->Root->t_End = *std::max_element(std::begin(Roots),std::end(Roots));
				}
				Roots.clear();
			}
			//
			for(Branch *B : J->Children)
			{
				float t0_1 = B->t_Begin;
				float t1_fin = B->t_End;
				//
				//if(BisectionMethod(*B->Curve,t0_1,t1_fin,dt_min,J->JunctionSphere,Roots))
				if(BisectionMethod(*B->Curve,t0_1,t1_fin,dt_min,modifiedJunctionSphere,Roots))
				{
					B->t_Begin = *std::min_element(std::begin(Roots),std::end(Roots));
				}
				Roots.clear();
			}
			//
			J->Id = JunctionId;
			JunctionId++;
		}
	}
	//
	TreeHypergraph()
	{}
	//
	~TreeHypergraph()
	{
		for(auto I : Branches)
		{
			delete I;
		}
		//
		for(auto I : Junctions)
		{
			delete I;
		}
	}
};

#endif // TREE_HYPERGRAPH_H
