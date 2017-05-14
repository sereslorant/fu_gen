#ifndef GENERATE_HYPERGRAPH_H
#define GENERATE_HYPERGRAPH_H

#include <Data/TreeSkeleton.h>
#include <Data/TreeHypergraph.h>

/*
 * Április 14
 */
class GenerateHypergraph// : public ITreeVisitor
{
private:
	float Radius;
	float RadiusDecay;
	float ParentWeight;
	float InitSpeed;
	float EndSpeed;
	//
public:

	void SetRadius(float radius)
	{
		Radius = radius;
	}

	void SetRadiusDecay(float radius_decay)
	{
		RadiusDecay = radius_decay;
	}

	void SetParentWeight(float parent_weight)
	{
		ParentWeight = parent_weight;
	}

	void SetInitSpeed(float init_speed)
	{
		InitSpeed = init_speed;
	}

	void SetEndSpeed(float end_speed)
	{
		EndSpeed = end_speed;
	}
	//
	float GetRadius()
	{
		return Radius;
	}
	//
	float GetRadiusDecay()
	{
		return RadiusDecay;
	}
	//
	float GetParentWeight()
	{
		return ParentWeight;
	}
	//
	float GetInitSpeed()
	{
		return InitSpeed;
	}
	//
	float GetEndSpeed()
	{
		return EndSpeed;
	}

	void Draw(TreeNode *node,TreeHypergraph *&result);

	GenerateHypergraph(float radius,float radius_decay,float parent_weight,float init_speed,float end_speed)
		:Radius(radius),RadiusDecay(radius_decay),ParentWeight(parent_weight),InitSpeed(init_speed),EndSpeed(end_speed)
	{}

	~GenerateHypergraph()
	{}
};

#endif // GENERATE_HYPERGRAPH_H
