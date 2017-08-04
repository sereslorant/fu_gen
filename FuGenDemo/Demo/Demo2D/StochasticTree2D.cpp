
#include "StochasticTree2D.h"

#include <Const.h>
#include <Filters/L_Systems/SOL_System.h>

StochasticTree2D::StochasticTree2D(unsigned int random_seed)
{
	SOL_System RandomPlant; //Node rewriting
	SOL_Production F_Production;
	F_Production.AddNextSuccessor(0.33,"F[+F]F[-F]F");
	F_Production.AddNextSuccessor(0.66,"F[+F]F");
	F_Production.AddNextSuccessor(1.0,"F[-F]F");
	RandomPlant.AddProduction('F',F_Production);

	std::string Axiom = "+++F";

	std::string Str = Axiom;
	for(int i=0;i < 5;i++)
	{
		std::string Tmp;
		RandomPlant.ApplyProductions(Str,random_seed,Tmp);
		Str = Tmp;
	}

	std::string Command;
	Turtle2DInterpreter.Convert(Str,Command);

	Turtle.Set_dAngle(PI/6.0);
	Turtle.Set_dDist(2.5);
	Turtle.ExecuteCommands(Command,RandomPlantSkeleton);
}

StochasticTree2D::~StochasticTree2D()
{
	delete RandomPlantSkeleton;
}
