#ifndef TURTLE_2D_STATE_H
#define TURTLE_2D_STATE_H

#include <cmath>

//#include <glm/glm.hpp>

#include <glmath.hpp>

#include "../../Data/TreeSkeleton.h"

struct Turtle2DState
{
	dvec4 Position;
	double Orientation;
	//
	TreeNode *Node;
	//
	void Move(double dDist)
	{
		dvec4 Displacement = dDist * dvec4(cos(Orientation),sin(Orientation));
		Position += Displacement;
	}
	//
	void Rotate(double dAngle)
	{
		Orientation += dAngle;
	}
};

#endif // TURTLE_2D_STATE_H
