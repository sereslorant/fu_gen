
#include "../ConnectionVisitor.h"

#include "TurtleNodePresenter.h"

const std::string TurtleNodePresenter::TurtleNodeName = "Turtle";

void TurtleNodePresenter::Refresh()
{
	auto OldSkeleton = Skeleton;
	//
	std::string Str = Axiom;
	for(int i=0;i < RecursionDepth;i++)
	{
		std::string Tmp;
		Tree.ApplyProductions(Str,Tmp);
		Str = Tmp;
	}
	//
	std::string Command;
	Turtle3DInterpreter.Convert(Str,Command);
	//
	Turtle.ExecuteCommands(Command,Skeleton);
	//
	SkeletonPresenter.OnChanged(Skeleton);
	//
	if(OldSkeleton != nullptr)
		{delete OldSkeleton;}
}

void TurtleNodePresenter::SetDeltaDistance(double delta_distance)
{
	Turtle.Set_dDist(delta_distance);
	Refresh();
}

double TurtleNodePresenter::GetDeltaDistance()
{
	return Turtle.Get_dDist();
}

void TurtleNodePresenter::SetDeltaAngle(double delta_angle)
{
	Turtle.Set_dAngle(delta_angle);
	Refresh();
}

double TurtleNodePresenter::GetDeltaAngle()
{
	return Turtle.Get_dAngle();
}

void TurtleNodePresenter::SetAxiom(const std::string &axiom)
{
	Axiom = axiom;
	Refresh();
}

const std::string &TurtleNodePresenter::GetAxiom()
{
	return Axiom;
}
//
void TurtleNodePresenter::SetRecursionDepth(unsigned int recursion_depth)
{
	RecursionDepth = recursion_depth;
	Refresh();
}

unsigned int TurtleNodePresenter::GetRecursionDepth()
{
	return RecursionDepth;
}

void TurtleNodePresenter::AddProduction(char predecessor,const std::string &successor)
{
	Tree.AddProduction(predecessor,DOL_Production(successor));
	Refresh();
}

bool TurtleNodePresenter::HasProduction(char predecessor)
{
	return Tree.HasProduction(predecessor);
}

void TurtleNodePresenter::DeleteProduction(char predecessor)
{
	Tree.DeleteProduction(predecessor);
	Refresh();
}

const std::map<char,DOL_Production> &TurtleNodePresenter::GetProductions()
{
	return Tree.GetProductions();
}

const std::string &TurtleNodePresenter::GetName()
{
	return TurtleNodeName;
}

bool TurtleNodePresenter::IsConnectable(IPipelineNodeModel *other_model)
{
	return false;
}

TreeDataPresenter &TurtleNodePresenter::GetDataPresenter()
{
	return SkeletonPresenter;
}

bool TurtleNodePresenter::ConnectInput(TreeDataPresenter &input_data_presenter)
{
	return false;
}

TurtleNodePresenter::TurtleNodePresenter(FuGenGLView *gl_view)
	:Turtle3DInterpreter(IsTurtle3DCommand),
	Turtle(vec4(0.0,0.0,0.0),vec4(0.0,0.0,1.0),vec4(1.0,0.0,0.0),0.0,0.0)
{
	char From3D[14]	= {'F','f','^','&','+','-','\\','/','|','[',']','{','}','.'};
	char To3D[14]	= {'F','f','(',')','<','>','+' ,'-','|','[',']','{','}','.'};
	//
	for(int i=0;i < 14;i++)
	{
		Turtle3DInterpreter.AddInterpretation(From3D[i],To3D[i]);
	}
	//
	if(gl_view != nullptr)
	{
		SkeletonPresenter.SetShaderProgram(
			&(gl_view->GetEdgeVisualizer().GetSkeletonShaderProgram())
		);
	}
	//
	Refresh();
}

TurtleNodePresenter::~TurtleNodePresenter()
{
	delete Skeleton;
}
