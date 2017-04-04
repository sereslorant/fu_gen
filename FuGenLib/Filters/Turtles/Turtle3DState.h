#ifndef TURTLE_3D_STATE_H
#define TURTLE_3D_STATE_H

#include <cmath>

#include <glmath.hpp>

#include "../../Data/TreeSkeleton.h"

struct Turtle3DState
{
	dvec4	Position;
	dvec4	Direction_H;
	dvec4	Direction_L;
	dvec4	Direction_U;
	//
	TreeNode *Node;
	//
	enum TurtleRotation
	{
		ROT_X,
		ROT_Y,
		ROT_Z,
	};
	//
	void Move(double dDist)
	{
		dvec4 Displacement = dDist * Direction_U;
		Position += Displacement;
	}
	//
	void Rotate(TurtleRotation rotation,double angle)
	{
		double Angle = angle;
		/*if(positive_direction)
			{Angle = angle;}
		else
			{Angle = -1.0*angle;}*/
		//
		//dmat4 RotationMatrix(1.0);
		//
		switch(rotation)
		{
		case ROT_X:
			Rotate(Direction_H,Angle);
			break;
			//
		case ROT_Y:
			Rotate(Direction_L,Angle);
			break;
			//
		case ROT_Z:
			Rotate(Direction_U,Angle);
			break;
		}
		//
		/*switch(rotation)
		{
		case ROT_X:
			RotationMatrix = rotate(RotationMatrix,Angle,Direction_H);
			break;
			//
		case ROT_Y:
			RotationMatrix = rotate(RotationMatrix,Angle,Direction_L);
			break;
			//
		case ROT_Z:
			RotationMatrix = rotate(RotationMatrix,Angle,Direction_U);
			break;
		}
		//
		dvec4 Direction;
		//
		Direction = RotationMatrix * dvec4(Direction_H,1.0);
		Direction_H = dvec4(Direction[0],Direction[1],Direction[2]);
		//
		Direction = RotationMatrix * dvec4(Direction_L,1.0);
		Direction_L = dvec4(Direction[0],Direction[1],Direction[2]);
		//
		Direction = RotationMatrix * dvec4(Direction_U,1.0);
		Direction_U = dvec4(Direction[0],Direction[1],Direction[2]);*/
	}
	//
	void Rotate(const dvec4 &axis,double angle)
	{
		dvec4 Direction;
		//
		Direction = rotate(axis,angle,Direction_H);
		Direction_H = dvec4(Direction[0],Direction[1],Direction[2]);
		//
		Direction = rotate(axis,angle,Direction_L);
		Direction_L = dvec4(Direction[0],Direction[1],Direction[2]);
		//
		Direction = rotate(axis,angle,Direction_U);
		Direction_U = dvec4(Direction[0],Direction[1],Direction[2]);
	}
	//
	Turtle3DState(const dvec4 &direction_h,const dvec4 &direction_l)
	{
		Direction_H = normalize(direction_h);
		Direction_L = normalize(direction_l);
		Direction_U = normalize(cross(direction_h,direction_l));
	}
};

#endif // TURTLE_3D_STATE_H
