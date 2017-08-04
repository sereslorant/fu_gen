
#include "QuadraticKockCurve.h"

#include <Const.h>
#include <Filters/L_Systems/DOL_System.h>

QuadraticKochCurve::QuadraticKochCurve()
{
	DOL_System QuadraticKochIsland; //Edge rewriting
	QuadraticKochIsland.AddProduction('F',DOL_Production("F - F + F + FF - F - F + F"));

	std::string Axiom = "F-F-F-F";

	std::string Str = Axiom;
	for(int i=0;i < 3;i++)
	{
		std::string Tmp;
		QuadraticKochIsland.ApplyProductions(Str,Tmp);
		Str = Tmp;
	}

	std::string Command;
	Turtle2DInterpreter.Convert(Str,Command);

	Turtle.Set_dAngle(PI/2.0);
	Turtle.Set_dDist(2.0);

	Turtle.ExecuteCommands(Command,QuadraticKochCurveSkeleton);
}

QuadraticKochCurve::~QuadraticKochCurve()
{
	delete QuadraticKochCurveSkeleton;
}
