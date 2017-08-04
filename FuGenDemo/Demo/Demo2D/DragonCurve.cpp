
#include "DragonCurve.h"

#include <Const.h>
#include <Filters/L_Systems/DOL_System.h>

DragonCurve::DragonCurve()
{
	DOL_System DragonCurve; //Node rewriting
	DragonCurve.AddProduction('l',DOL_Production("l+rF+"));
	DragonCurve.AddProduction('r',DOL_Production("-Fl-r"));

	std::string Axiom = "Fl";

	std::string Str = Axiom;
	for(int i=0;i < 11;i++)
	{
		std::string Tmp;
		DragonCurve.ApplyProductions(Str,Tmp);
		Str = Tmp;
	}

	std::string Command;
	Turtle2DInterpreter.Convert(Str,Command);

	Turtle.Set_dAngle(PI/2.0);
	Turtle.Set_dDist(2.5);
	Turtle.ExecuteCommands(Command,DragonCurveSkeleton);
}

DragonCurve::~DragonCurve()
{
	delete DragonCurveSkeleton;
}
