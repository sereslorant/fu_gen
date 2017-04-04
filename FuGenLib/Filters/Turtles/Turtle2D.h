#ifndef TURTLE_2D_H
#define TURTLE_2D_H

#include "TurtleBase.hpp"
#include "Turtle2DState.h"

#include <string>

bool IsTurtle2DCommand(char command);

class Turtle2D : public TurtleBase<double, Turtle2DState>
{
public:
	//
	void ExecuteCommands(const std::string &commands,TreeNode *&tree_skeleton);
	//
	Turtle2D(double d_dist,double d_angle)
		:TurtleBase(d_dist,d_angle,Turtle2DState())
	{
		/*
		 * Üres függvénytörzs
		 */
	}
	//
	~Turtle2D()
	{
		/*
		 * Üres függvénytörzs
		 */
	}
	//
	/*
	 * Class vége
	 */
};

#endif // TURTLE_2D_H
