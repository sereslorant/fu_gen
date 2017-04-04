#ifndef TURTLE_3D_H
#define TURTLE_3D_H

#include "TurtleBase.hpp"
#include "Turtle3DState.h"

#include <string>

bool IsTurtle3DCommand(char command);

class Turtle3D : public TurtleBase<double, Turtle3DState>
{
public:
	//
	void ExecuteCommands(const std::string &commands,TreeNode *&tree_skeleton);
	//
	Turtle3D(const dvec4 &direction_h,const dvec4 &direction_l,double d_dist,double d_angle);
	//
	~Turtle3D()
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


#endif // TURTLE_3D_H
