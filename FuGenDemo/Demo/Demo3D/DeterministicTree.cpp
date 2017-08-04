
#include "DeterministicTree.h"

#include <Const.h>
#include <Filters/L_Systems/DOL_System.h>
#include <Filters/HypergraphGenerator/GenerateHypergraph.h>
#include <Filters/MeshGenerator/LowPolyMeshGenerator.h>


DeterministicTree::DeterministicTree(unsigned int Res_X,unsigned int Res_Y,unsigned int texture_id)
{
	TextureId = texture_id;
	
	DOL_System Tree;

	Tree.AddProduction('A',DOL_Production("[&FL!A]/////’[&FL!A]///////’[&FL!A]"));
	Tree.AddProduction('F',DOL_Production("S ///// F"));
	Tree.AddProduction('S',DOL_Production("F L"));
	Tree.AddProduction('L',DOL_Production("[’’’^^{.-f.+f.+f.-|-f.+f.+f.}]"));

	std::string Axiom = "A";

	std::string Str = Axiom;
	for(int i=0;i < 7;i++)
	{
		std::string Tmp;
		Tree.ApplyProductions(Str,Tmp);
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

DeterministicTree::~DeterministicTree()
{
	//
}
