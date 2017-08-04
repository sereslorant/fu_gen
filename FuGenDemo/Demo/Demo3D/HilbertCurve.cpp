
#include "HilbertCurve.h"

#include <Const.h>
#include <Filters/L_Systems/DOL_System.h>

HilbertCurve::HilbertCurve()
{
	DOL_System DolHilbertCurve;

	DolHilbertCurve.AddProduction('A',DOL_Production("B-F+CFC+F-D&F^D-F+&&CFC+F+B//"));
	DolHilbertCurve.AddProduction('B',DOL_Production("A&F^CFB^F^D^^-F-D^|F^B|FC^F^A//"));
	DolHilbertCurve.AddProduction('C',DOL_Production("|D^|F^B-F+C^F^A&&FA&F^C+F+B^F^D//"));
	DolHilbertCurve.AddProduction('D',DOL_Production("|CFB-F+B|FA&F^A&&FB-F+B|FC//"));

	std::string Axiom = "A";

	std::string Str = Axiom;
	for(int i=0;i < 4;i++)
	{
		std::string Tmp;
		DolHilbertCurve.ApplyProductions(Str,Tmp);
		Str = Tmp;
	}

	std::string Command;
	Turtle3DInterpreter.Convert(Str,Command);
	//std::cout << Command << std::endl;

	Turtle.Set_dAngle(PI/2.0);
	Turtle.Set_dDist(2.0);
	Turtle.ExecuteCommands(Command,HilbertCurveSkeleton);
}

HilbertCurve::~HilbertCurve()
{
	delete HilbertCurveSkeleton;
}
