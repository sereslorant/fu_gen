
#include "GLViewTest.h"

#include "ui_GLViewTest.h"

#include <Filters/L_Systems/DOL_System.h>
#include <Filters/Turtles/TurtleInterpreter.h>
#include <Filters/Turtles/Turtle3D.h>

#include <Filters/MeshGenerator/LowPolyMeshGenerator.h>

void GLViewTest::CreateTestSkeleton()
{
	DOL_System Tree;
	//
	Tree.AddProduction('A',DOL_Production("[&FL!A]/////’[&FL!A]///////’[&FL!A]"));
	Tree.AddProduction('F',DOL_Production("S ///// F"));
	Tree.AddProduction('S',DOL_Production("F L"));
	Tree.AddProduction('L',DOL_Production("[’’’^^{.-f.+f.+f.-|-f.+f.+f.}]"));
	//
	std::string Axiom = "A";
	//
	std::string Str = Axiom;
	for(int i=0;i < 5;i++)
	{
		std::string Tmp;
		Tree.ApplyProductions(Str,Tmp);
		Str = Tmp;
	}
	//
	Turtle3D Turtle(vec4(5.0,0.0,0.0),vec4(0.0,0.0,1.0),vec4(1.0,0.0,0.0),0.0,0.0);
	TurtleInterpreter Turtle3DInterpreter(IsTurtle3DCommand);
	char From3D[14]	= {'F','f','^','&','+','-','\\','/','|','[',']','{','}','.'};
	char To3D[14]	= {'F','f','(',')','<','>','+' ,'-','|','[',']','{','}','.'};
	//
	for(int i=0;i < 14;i++)
	{
		Turtle3DInterpreter.AddInterpretation(From3D[i],To3D[i]);
	}
	//
	constexpr double PI = 3.14159265359;
	Turtle.Set_dAngle(PI/2.0*0.25);
	Turtle.Set_dDist(1.0);
	//
	std::string Command;
	Turtle3DInterpreter.Convert(Str,Command);
	//
	Turtle.ExecuteCommands(Command,TestSkeleton);
}

void GLViewTest::CreateTestHypergraph()
{
	vec4 JunctionPoint(6.0,6.0);
	CatmullRom TestParentCR(vec4(0.0,1.0),vec4(0.0,1.0));
	TestParentCR.AddControlPoint(vec4(3.0,0.0),0.0);
	TestParentCR.AddControlPoint(vec4(5.0,2.0),0.5);
	TestParentCR.AddControlPoint(JunctionPoint,1.0);
	TreeHypergraph::Branch *TestParent = new TreeHypergraph::Branch;
	TestParent->Curve = TestParentCR.Clone();
	TestParent->t_Begin = 0.0;
	TestParent->t_End = 0.95;
	TestParent->Up = vec4(-1.0,1.0,0.0);
	TestParent->Width = 0.75;
	//
	CatmullRom TestChild1CR(vec4(0.0,1.0),vec4(0.0,1.0));
	TestChild1CR.AddControlPoint(JunctionPoint,0.0);
	TestChild1CR.AddControlPoint(vec4(3.0,9.0),0.5);
	TestChild1CR.AddControlPoint(vec4(2.0,12.0),1.0);
	TreeHypergraph::Branch *TestChild1 = new TreeHypergraph::Branch;
	TestChild1->Curve = TestChild1CR.Clone();
	TestChild1->t_Begin = 0.05;
	TestChild1->t_End = 1.0;
	TestChild1->Up = vec4(-1.0,1.0,0.0);
	TestChild1->Width = 0.5;
	//
	CatmullRom TestChild2CR(vec4(0.0,1.0),vec4(0.0,1.0));
	TestChild2CR.AddControlPoint(JunctionPoint,0.0);
	TestChild2CR.AddControlPoint(vec4(8.0,9.0),0.25);
	TestChild2CR.AddControlPoint(vec4(10.0,13.0),1.0);
	TreeHypergraph::Branch *TestChild2 = new TreeHypergraph::Branch;
	TestChild2->Curve = TestChild2CR.Clone();
	TestChild2->t_Begin = 0.05;
	TestChild2->t_End = 1.0;
	TestChild2->Up = vec4(-1.0,1.0,0.0);
	TestChild2->Width = 0.5;
	//
	CatmullRom TestChild3CR(vec4(0.0,1.0),vec4(0.0,1.0));
	TestChild3CR.AddControlPoint(JunctionPoint,0.0);
	TestChild3CR.AddControlPoint(vec4(10.0,8.0),0.5);
	TestChild3CR.AddControlPoint(vec4(10.8,8.2),0.75);
	TestChild3CR.AddControlPoint(vec4(11.0,9.0),1.0);
	TreeHypergraph::Branch *TestChild3 = new TreeHypergraph::Branch;
	TestChild3->Curve = TestChild3CR.Clone();
	TestChild3->t_Begin = 0.05;
	TestChild3->t_End = 1.0;
	TestChild3->Up = vec4(-1.0,1.0,0.0);
	TestChild3->Width = 0.5;
	//
	CatmullRom TestChild4CR(vec4(0.0,1.0),vec4(0.0,1.0));
	TestChild4CR.AddControlPoint(JunctionPoint,0.0);
	TestChild4CR.AddControlPoint(vec4(4.0,10.0,2.5),0.5);
	TestChild4CR.AddControlPoint(vec4(4.0,13.0,5.0),1.0);
	TreeHypergraph::Branch *TestChild4 = new TreeHypergraph::Branch;
	TestChild4->Curve = TestChild4CR.Clone();
	TestChild4->t_Begin = 0.05;
	TestChild4->t_End = 1.0;
	TestChild4->Up = vec4(-1.0,1.0,0.0);
	TestChild4->Width = 0.5;
	//
	TestHypergraph.Branches.push_back(TestParent);
	TestHypergraph.Branches.push_back(TestChild1);
	TestHypergraph.Branches.push_back(TestChild2);
	TestHypergraph.Branches.push_back(TestChild3);
	TestHypergraph.Branches.push_back(TestChild4);
	//
	TreeHypergraph::Junction *TestJunction = new TreeHypergraph::Junction;
	TestJunction->Root = TestParent;
	TestJunction->Children.push_back(TestChild1);
	TestJunction->Children.push_back(TestChild2);
	TestJunction->Children.push_back(TestChild3);
	TestJunction->Children.push_back(TestChild4);
	TestJunction->JunctionSphere = Sphere(JunctionPoint,1.0);
	//
	TestHypergraph.Junctions.push_back(TestJunction);
	//
	TestHypergraph.Prepare();
}
//
void GLViewTest::CreateTestMesh()
{
	LowPolyMeshGenerator MeshGenerator(10,10);
	MeshGenerator.Generate(&TestHypergraph,TestMesh);
}

GLViewTest::GLViewTest()
	:ViewListener(*this)
{
	Ui::GLViewTest Ui;
	Ui.setupUi(this);
	//
	GLView = Ui.centralwidget;
	GLView->AddListener(&ViewListener);
}

GLViewTest::~GLViewTest()
{
	delete TestSkeleton;
	delete TestMesh;
}

#include "GLViewTest.moc"

/*
 * Main test
 */

#include <QtWidgets/QApplication>

int main(int argc,char *argv[])
{
	QApplication Application(argc, argv);
	//
    GLViewTest Window;
    Window.show();
	//
    return Application.exec();
}
