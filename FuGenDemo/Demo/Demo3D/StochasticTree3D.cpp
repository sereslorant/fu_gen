
#include <Demo/Demo3D/StochasticTree3D.h>

#include <Const.h>
#include <Filters/L_Systems/SOL_System.h>
#include <Filters/HypergraphGenerator/GenerateHypergraph.h>
#include <Filters/MeshGenerator/LowPolyMeshGenerator.h>

StochasticTree3D::StochasticTree3D(unsigned int random_seed,unsigned int Res_X,unsigned int Res_Y,unsigned int texture_id)
{
	TextureId = texture_id;
	
	SOL_System Tree;
	//
	SOL_Production A_Production;
	A_Production.AddNextSuccessor(0.75,"[&FL!A]/////’[&FL!A]///////’[&FL!A]");
	A_Production.AddNextSuccessor(0.85,"[&FL!A]///’[&FL!A]////’[&FL!A]///’[&FL!A]");
	A_Production.AddNextSuccessor(1.0,"[&FL!A]///’[&FL!A]////’[&FL!A]///’[&FL!A]////’[&FL!A]");
	Tree.AddProduction('A',A_Production);
	SOL_Production F_Production;
	F_Production.AddNextSuccessor(1.0,"S ///// F");
	Tree.AddProduction('F',F_Production);
	SOL_Production S_Production;
	S_Production.AddNextSuccessor(1.0,"F L");
	Tree.AddProduction('S',S_Production);
	SOL_Production L_Production;
	L_Production.AddNextSuccessor(1.0,"[’’’^^{.-f.+f.+f.-|-f.+f.+f.}]");
	Tree.AddProduction('L',L_Production);

	std::string Axiom = "A";

	std::string Str = Axiom;
	for(int i=0;i < 7;i++)
	{
		std::string Tmp;
		Tree.ApplyProductions(Str,random_seed,Tmp);
		Str = Tmp;
	}

	Turtle.Set_dAngle(PI/2.0*0.25);
	//Turtle.Set_dAngle((PI/2.0)*0.45);
	Turtle.Set_dDist(35.0);

	std::string Command;
	//std::cout << Str << std::endl;
	Turtle3DInterpreter.Convert(Str,Command);
	//std::cout << Command << std::endl;

	Turtle.ExecuteCommands(Command,TreeSkeleton);

	GenerateHypergraph DrawSkel(20.0,0.75,0.75,10.0,5.0);
	DrawSkel.Draw(TreeSkeleton,Hypergraph);
	
	LowPolyMeshGenerator GenerateMesh(Res_X,Res_Y);
	GenerateMesh.Generate(Hypergraph,Mesh);
}

StochasticTree3D::~StochasticTree3D()
{
	//
}
