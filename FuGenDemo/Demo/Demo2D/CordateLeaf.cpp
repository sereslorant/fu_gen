
#include "CordateLeaf.h"

#include <Const.h>
#include <Filters/L_Systems/DOL_System.h>

CordateLeaf::CordateLeaf()
{
	Turtle2DInterpreter.AddInterpretation('G','f');
	//
	DOL_System CordateLeaf; //Node rewriting
	CordateLeaf.AddProduction('A',DOL_Production("[+A{.].C.}"));
	CordateLeaf.AddProduction('B',DOL_Production("[-B{.].C.}"));
	CordateLeaf.AddProduction('C',DOL_Production("GC"));

	std::string Axiom = "[A][B]";

	std::string Str = Axiom;
	for(int i=0;i < 10;i++)
	{
		std::string Tmp;
		CordateLeaf.ApplyProductions(Str,Tmp);
		Str = Tmp;
	}

	//std::cout << Str << std::endl;

	std::string Command;
	Turtle2DInterpreter.Convert(Str,Command);

	//std::cout << Command << std::endl;

	Turtle.Set_dAngle(PI/8.0);
	Turtle.Set_dDist(10.0);
	Turtle.ExecuteCommands(Command,CurveSkeleton);
}

CordateLeaf::~CordateLeaf()
{}
