
#if defined(__APPLE__)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#include <iostream>

#include <cmath>

#include <vector>
#include <list>

#include <Filters/L_Systems/DOL_System.h>
#include <Filters/L_Systems/SOL_System.h>

#include <Filters/Turtles/Turtle2D.h>
#include <Filters/Turtles/Turtle3D.h>
#include <Filters/Turtles/TurtleInterpreter.h>

#include <Filters/GenerateHypergraph.h>
#include <Filters/MeshGenerator/LowPolyMeshGenerator.h>

#include <SOIL/SOIL.h>

const int screenWidth = 1024;
const int screenHeight = 512;

struct Color {
   float r, g, b;

   Color( ) {
	r = g = b = 0;
   }
   Color(float r0, float g0, float b0) {
	r = r0; g = g0; b = b0;
   }
   Color operator*(float a) {
	return Color(r * a, g * a, b * a);
   }
   Color operator*(const Color& c) {
	return Color(r * c.r, g * c.g, b * c.b);
   }
   Color operator+(const Color& c) {
 	return Color(r + c.r, g + c.g, b + c.b);
   }
};

GLuint TextureId = 0;
GLuint BarkTexId = 0;

void InitTexture()
{
	const unsigned int TEXTURE_X = 2;
	const unsigned int TEXTURE_Y = 2;

	Color Texture[TEXTURE_X][TEXTURE_Y] = {{Color(0.0,1.0,0.0),Color(0.0,0.8,0.2)},{Color(0.0,0.8,0.0),Color(0.0,1.0,0.2)}};

	glGenTextures(1,&TextureId);
	glBindTexture(GL_TEXTURE_2D,TextureId);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TEXTURE_X, TEXTURE_Y, 0, GL_RGB, GL_FLOAT, &Texture[0][0]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindTexture(GL_TEXTURE_2D,0);
}

#include "Demo/DrawSkeleton.h"
#include "Demo/DrawModel.h"


float X = 20.0;
float Y = -20.0;
float Z = 20.0;

float CameraAngle = 0.0;

class IDemo
{
public:

	IDemo() {}
	virtual ~IDemo() {}

	virtual void Draw() = 0;
};

class DrawCurve : public IDemo
{
protected:
	Turtle2D Turtle = Turtle2D(0.0,0.0);
	TurtleInterpreter Turtle2DInterpreter = TurtleInterpreter(IsTurtle2DCommand);

public:

	DrawCurve()
	{
		char From2D[9]	= {'F','f','+','-','[',']','{','}','.'};
		char To2D[9]	= {'F','f','+','-','[',']','{','}','.'};

		for(int i=0;i < 9;i++)
		{
			Turtle2DInterpreter.AddInterpretation(From2D[i],To2D[i]);
		}
	}

	virtual ~DrawCurve() override
		{}
};

class DrawQuadraticKochCurve : public DrawCurve
{
private:
	TreeNode *QuadraticKochCurveSkeleton;

public:

	DrawQuadraticKochCurve()
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

	virtual ~DrawQuadraticKochCurve() override
	{
		delete QuadraticKochCurveSkeleton;
	}

	virtual void Draw() override
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		gluOrtho2D(-256.0,256.0,-128.0,+128.0);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glTranslatef(0.0,64.0,0.0);
		
		glColor3f(0.0,0.0,0.0);
		DrawSkeleton DrawSkel;
		DrawSkel.Draw(QuadraticKochCurveSkeleton);
	}
};

class DrawDragonCurve : public DrawCurve
{
private:
	TreeNode *DragonCurveSkeleton;

public:

	DrawDragonCurve()
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

	virtual ~DrawDragonCurve() override
	{
		delete DragonCurveSkeleton;
	}

	virtual void Draw() override
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		gluOrtho2D(-256.0,256.0,-128.0,+128.0);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glTranslatef(0.0,0.0,0.0);
		
		glColor3f(0.0,0.0,0.0);
		DrawSkeleton DrawSkel;
		DrawSkel.Draw(DragonCurveSkeleton);
	}
};

class DrawRandomPlant : public DrawCurve
{
private:
	TreeNode *RandomPlantSkeleton;

public:

	DrawRandomPlant(unsigned int random_seed)
	{
		SOL_System RandomPlant; //Node rewriting
		SOL_Production F_Production;
		F_Production.AddNextSuccessor(0.33,"F[+F]F[-F]F");
		F_Production.AddNextSuccessor(0.66,"F[+F]F");
		F_Production.AddNextSuccessor(1.0,"F[-F]F");
		RandomPlant.AddProduction('F',F_Production);

		std::string Axiom = "+++F";

		std::string Str = Axiom;
		for(int i=0;i < 8;i++)
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

	virtual ~DrawRandomPlant() override
	{
		delete RandomPlantSkeleton;
	}

	virtual void Draw() override
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		gluOrtho2D(-256.0,256.0,-128.0,+128.0);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glTranslatef(0.0,-100.0,0.0);
		
		glColor3f(0.0,0.0,0.0);
		DrawSkeleton DrawSkel;
		DrawSkel.Draw(RandomPlantSkeleton);
	}
};

class DrawCordateLeaf : public DrawCurve
{
private:
	TreeNode *CurveSkeleton;
	
public:

	DrawCordateLeaf()
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

	virtual ~DrawCordateLeaf() override
	{}

	virtual void Draw() override
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		gluOrtho2D(-256.0,256.0,-128.0,+128.0);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glTranslatef(0.0,0.0,0.0);
		
		glColor3f(0.0,0.0,0.0);
		DrawSkeleton DrawSkel;
		DrawSkel.Draw(CurveSkeleton);
	}
};

class Demo3D : public IDemo
{
protected:
	Turtle3D Turtle;// = Turtle3D(vec4(1.0,0.0,0.0),vec4(0.0,1.0,0.0),2.0,PI/2.0);
	TurtleInterpreter Turtle3DInterpreter;

public:

	Demo3D()
		:Turtle(vec4(1.0,0.0,0.0),vec4(0.0,1.0,0.0),0.0,0.0),Turtle3DInterpreter(IsTurtle3DCommand)
	{
		char From3D[14]	= {'F','f','^','&','+','-','\\','/','|','[',']','{','}','.'};
		char To3D[14]	= {'F','f','(',')','<','>','+' ,'-','|','[',']','{','}','.'};

		for(int i=0;i < 14;i++)
		{
			Turtle3DInterpreter.AddInterpretation(From3D[i],To3D[i]);

			//std::cout << From3D[i] << ";" << To3D[i] << std::endl;
		}
	}

	virtual ~Demo3D() override
	{}
};

class DrawHilbertCurve : public Demo3D
{
private:
	TreeNode *HilbertCurveSkeleton;

public:

	DrawHilbertCurve()
	{
		DOL_System HilbertCurve;

		HilbertCurve.AddProduction('A',DOL_Production("B-F+CFC+F-D&F^D-F+&&CFC+F+B//"));
		HilbertCurve.AddProduction('B',DOL_Production("A&F^CFB^F^D^^-F-D^|F^B|FC^F^A//"));
		HilbertCurve.AddProduction('C',DOL_Production("|D^|F^B-F+C^F^A&&FA&F^C+F+B^F^D//"));
		HilbertCurve.AddProduction('D',DOL_Production("|CFB-F+B|FA&F^A&&FB-F+B|FC//"));

		std::string Axiom = "A";

		std::string Str = Axiom;
		for(int i=0;i < 4;i++)
		{
			std::string Tmp;
			HilbertCurve.ApplyProductions(Str,Tmp);
			Str = Tmp;
		}

		std::string Command;
		Turtle3DInterpreter.Convert(Str,Command);
		//std::cout << Command << std::endl;

		Turtle.Set_dAngle(PI/2.0);
		Turtle.Set_dDist(2.0);
		Turtle.ExecuteCommands(Command,HilbertCurveSkeleton);
	}

	virtual ~DrawHilbertCurve() override
	{
		delete HilbertCurveSkeleton;
	}

	virtual void Draw() override
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		gluPerspective(90,1.0,1.0,-200.0);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glTranslatef(X,Y,Z);

		glRotatef(CameraAngle,0.0,1.0,0.0);
		glRotatef(-90.0,1.0,0.0,0.0);
		
		glColor3f(0.0,0.0,0.0);
		DrawSkeleton HilbertDraw;
		HilbertDraw.Draw(HilbertCurveSkeleton);
	}
};

class DrawTree : public Demo3D
{
protected:
	TreeNode *TreeSkeleton;
	TreeHypergraph *Hypergraph;

public:

	DrawTree()
	{
		DOL_System Tree;

		Tree.AddProduction('A',DOL_Production("[&FL!A]/////’[&FL!A]///////’[&FL!A]"));
		//Tree.AddProduction('A',DOL_System::Production("[&FL!A]///’[&FL!A]////’[&FL!A]///’[&FL!A]"));
		//Tree.AddProduction('A',DOL_System::Production("[&FL!A]///’[&FL!A]////’[&FL!A]///’[&FL!A]////’[&FL!A]"));
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

		GenerateHypergraph DrawSkel;
		DrawSkel.Draw(TreeSkeleton,Hypergraph);
	}

	virtual ~DrawTree() override
	{
		delete TreeSkeleton;
		delete Hypergraph;
	}
};

class DrawDeterministicTree : public DrawTree
{
public:

	DrawDeterministicTree()
	{
		DOL_System Tree;

		Tree.AddProduction('A',DOL_Production("[&FL!A]/////’[&FL!A]///////’[&FL!A]"));
		//Tree.AddProduction('A',DOL_System::Production("[&FL!A]///’[&FL!A]////’[&FL!A]///’[&FL!A]"));
		//Tree.AddProduction('A',DOL_System::Production("[&FL!A]///’[&FL!A]////’[&FL!A]///’[&FL!A]////’[&FL!A]"));
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

		GenerateHypergraph DrawSkel;
		DrawSkel.Draw(TreeSkeleton,Hypergraph);
	}

	virtual ~DrawDeterministicTree() override
	{
		//
	}
};


class DrawStochasticTree : public DrawTree
{
public:

	DrawStochasticTree(unsigned int random_seed)
	{
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

		GenerateHypergraph DrawSkel;
		DrawSkel.Draw(TreeSkeleton,Hypergraph);
	}

	virtual ~DrawStochasticTree() override
	{
		//
	}
};

class DrawTreeSkeleton : public DrawDeterministicTree
{
public:

	DrawTreeSkeleton() {}
	virtual ~DrawTreeSkeleton() override {}

	virtual void Draw() override
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		gluPerspective(90,1.0,1.0,-200.0);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glTranslatef(X,Y,Z);

		glRotatef(CameraAngle,0.0,1.0,0.0);
		glRotatef(-90.0,1.0,0.0,0.0);

		//DrawSkeleton HilbertDraw;
		//HilbertDraw.Draw(HilbertCurveSkeleton);

		//GenerateHypergraph DrawSkel;
		//DrawSkel.Draw(TreeSkeleton,Hypergraph);

		glEnable(GL_DEPTH_TEST);
		//glEnable(GL_CULL_FACE);
		//glCullFace(GL_BACK);
		//glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
		
		glColor3f(0.0,0.0,0.0);
		DrawSkeleton DrawSkel;
		DrawSkel.Draw(TreeSkeleton);
	}
};

class DrawTreeHalfDone : public DrawDeterministicTree
{
public:

	DrawTreeHalfDone() {}
	virtual ~DrawTreeHalfDone() override {}

	virtual void Draw() override
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		gluPerspective(90,1.0,1.0,-200.0);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glTranslatef(X,Y,Z);

		glRotatef(CameraAngle,0.0,1.0,0.0);
		glRotatef(-90.0,1.0,0.0,0.0);

		//DrawSkeleton HilbertDraw;
		//HilbertDraw.Draw(HilbertCurveSkeleton);

		//GenerateHypergraph DrawSkel;
		//DrawSkel.Draw(TreeSkeleton,Hypergraph);

		glEnable(GL_DEPTH_TEST);
		//glEnable(GL_CULL_FACE);
		//glCullFace(GL_BACK);
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

		DrawHypergraph(Hypergraph);
	}
};

void DrawTreeMesh(TreeNode *skeleton,MultiMesh &mesh,GLuint texture)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(90,1.0,1.0,-200.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(X,Y,Z);

	glRotatef(CameraAngle,0.0,1.0,0.0);
	glRotatef(-90.0,1.0,0.0,0.0);

	//DrawSkeleton HilbertDraw;
	//HilbertDraw.Draw(HilbertCurveSkeleton);

	//GenerateHypergraph DrawSkel;
	//DrawSkel.Draw(TreeSkeleton,Hypergraph);

	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	//glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,texture);
	//
	glColor3f(1.0,1.0,1.0);
	DrawMultiMesh(mesh);
	//
	glColor3f(0.0,1.0,0.0);
	DrawSkeleton DrawSkel;
	DrawSkel.Draw(skeleton);
	//
	glDisable(GL_TEXTURE_2D);
}

class DrawTreeFinished : public DrawDeterministicTree
{
private:
	MultiMesh Mesh;
	GLuint Texture;
	//
public:

	DrawTreeFinished(unsigned int Res_X,unsigned int Res_Y,GLuint texture)
		:Texture(texture)
	{
		LowPolyMeshGenerator GenerateMesh(Res_X,Res_Y);
		GenerateMesh.Generate(Hypergraph,Mesh);
	}
	virtual ~DrawTreeFinished() override {}

	virtual void Draw() override
	{
		DrawTreeMesh(TreeSkeleton,Mesh,Texture);
	}
};

class DrawStochasticTreeFinished : public DrawStochasticTree
{
private:
	MultiMesh Mesh;
	GLuint Texture;
	//
public:
	//
	DrawStochasticTreeFinished(unsigned int random_seed,unsigned int Res_X,unsigned int Res_Y,GLuint texture)
		:DrawStochasticTree(random_seed),Texture(texture)
	{
		LowPolyMeshGenerator GenerateMesh(Res_X,Res_Y);
		GenerateMesh.Generate(Hypergraph,Mesh);
	}
	virtual ~DrawStochasticTreeFinished() override {}

	virtual void Draw() override
	{
		DrawTreeMesh(TreeSkeleton,Mesh,Texture);
	}
};


TreeNode *TreeSkeleton;

TreeHypergraph *Hypergraph;

unsigned int DemoId = 0;
std::vector<IDemo *> DemoArray;

// Inicializacio, a program futasanak kezdeten, az OpenGL kontextus letrehozasa utan hivodik meg (ld. main() fv.)
void onInitialization()
{

	//std::string TurtleCommand = "++fffffffffffff--[F+F--F+F----]+FfFf-FfF--fffffffffffffff--ffffffffffffffffffffffffff++++fffffffffffffff--fffff";
	//Turtle.ExecuteCommands(TurtleCommand,TreeSkeleton);

	//Turtle2D Turtle(8.0,PI/4.0);

	TurtleInterpreter Turtle2DInterpreter(IsTurtle2DCommand);
	TurtleInterpreter Turtle3DInterpreter(IsTurtle3DCommand);

	Turtle2D Turtle(0.0,0.0);

	Turtle.Set_dAngle(PI/2.0);
	Turtle.Set_dDist(2.0);
	std::string Axiom = "F-F-F-F";

	DOL_System QuadraticKochIsland; //Edge rewriting
	QuadraticKochIsland.AddProduction('F',DOL_Production("F - F + F + FF - F - F + F"));

	std::string Str = Axiom;
	for(int i=0;i < 3;i++)
	{
		std::string Tmp;
		QuadraticKochIsland.ApplyProductions(Str,Tmp);
		Str = Tmp;
	}

	char From2D[6]	= {'F','f','+','-','[',']'};
	char To2D[6]	= {'F','f','+','-','[',']'};

	char From3D[11]	= {'F','f','^','&','+','-','\\','/','|','[',']'};
	char To3D[11]	= {'F','f','(',')','<','>','+' ,'-','|','[',']'};

	for(int i=0;i < 6;i++)
	{
		Turtle2DInterpreter.AddInterpretation(From2D[i],To2D[i]);
	}

	for(int i=0;i < 11;i++)
	{
		Turtle3DInterpreter.AddInterpretation(From3D[i],To3D[i]);
	}

	std::string Command;
	Turtle2DInterpreter.Convert(Str,Command);
	//std::cout << Command << std::endl;

	Command += "ffffffffffffffffffffffffffff";

	//Turtle.ExecuteCommands(Command,QuadraticKochCurveSkeleton);

	DOL_System DragonCurve; //Node rewriting
	DragonCurve.AddProduction('l',DOL_Production("l+rF+"));
	DragonCurve.AddProduction('r',DOL_Production("-Fl-r"));

	//Turtle = Turtle2D(0.0,0.0);

	Turtle.Set_dAngle(PI/2.0);
	Turtle.Set_dDist(2.5);

	Axiom = "Fl";
	Str = Axiom;
	for(int i=0;i < 11;i++)
	{
		std::string Tmp;
		DragonCurve.ApplyProductions(Str,Tmp);
		Str = Tmp;
	}

	Turtle2DInterpreter.Convert(Str,Command);
	//std::cout << Command << std::endl;
	//Turtle.ExecuteCommands(Command,DragonCurveSkeleton);

	Turtle3D Turtle3(vec4(1.0,0.0,0.0),vec4(0.0,1.0,0.0),2.0,PI/2.0);

	DOL_System HilbertCurve;

	HilbertCurve.AddProduction('A',DOL_Production("B-F+CFC+F-D&F^D-F+&&CFC+F+B//"));
	HilbertCurve.AddProduction('B',DOL_Production("A&F^CFB^F^D^^-F-D^|F^B|FC^F^A//"));
	HilbertCurve.AddProduction('C',DOL_Production("|D^|F^B-F+C^F^A&&FA&F^C+F+B^F^D//"));
	HilbertCurve.AddProduction('D',DOL_Production("|CFB-F+B|FA&F^A&&FB-F+B|FC//"));

	Axiom = "A";
	Str = Axiom;
	for(int i=0;i < 3;i++)
	{
		std::string Tmp;
		HilbertCurve.ApplyProductions(Str,Tmp);
		Str = Tmp;
	}

	Command.clear();
	Turtle3DInterpreter.Convert(Str,Command);
	//std::cout << Command << std::endl;
	//Turtle3.ExecuteCommands(Command,HilbertCurveSkeleton);

	Turtle3 = Turtle3D(vec4(1.0,0.0,0.0),vec4(0.0,1.0,0.0),2.0,PI/2.0);

	DOL_System Tree;

	Tree.AddProduction('A',DOL_Production("[&FL!A]/////’[&FL!A]///////’[&FL!A]"));
	//Tree.AddProduction('A',DOL_System::Production("[&FL!A]///’[&FL!A]////’[&FL!A]///’[&FL!A]"));
	//Tree.AddProduction('A',DOL_System::Production("[&FL!A]///’[&FL!A]////’[&FL!A]///’[&FL!A]////’[&FL!A]"));
	Tree.AddProduction('F',DOL_Production("S ///// F"));
	Tree.AddProduction('S',DOL_Production("F L"));
	Tree.AddProduction('L',DOL_Production("[’’’^^{-f+f+f-|-f+f+f}]"));

	Axiom = "A";
	Str = Axiom;
	for(int i=0;i < 3;i++)
	{
		std::string Tmp;
		Tree.ApplyProductions(Str,Tmp);
		Str = Tmp;
	}

	Turtle3.Set_dAngle(PI/2.0*0.25);
	//Turtle3.Set_dAngle((PI/2.0)*0.45);
	Turtle3.Set_dDist(35.0);


	Command.clear();
	//std::cout << Str << std::endl;
	Turtle3DInterpreter.Convert(Str,Command);
	//std::cout << Command << std::endl;

	Turtle3.ExecuteCommands(Command,TreeSkeleton);

	GenerateHypergraph DrawSkel;
	DrawSkel.Draw(TreeSkeleton,Hypergraph);

	BarkTexId = SOIL_load_OGL_texture("SeamlessBark2.jpg",
										SOIL_LOAD_AUTO,
										SOIL_CREATE_NEW_ID,
										/*SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT*/
										SOIL_FLAG_DDS_LOAD_DIRECT);
	//
	glBindTexture(GL_TEXTURE_2D,BarkTexId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindTexture(GL_TEXTURE_2D,0);

	InitTexture();
	
	unsigned int TreeResX = 6;
	unsigned int TreeResY = 6;
	
	DemoArray.push_back(new DrawQuadraticKochCurve);
	DemoArray.push_back(new DrawDragonCurve);
	DemoArray.push_back(new DrawRandomPlant(234));
	DemoArray.push_back(new DrawRandomPlant(6332));
	DemoArray.push_back(new DrawRandomPlant(234236));
	DemoArray.push_back(new DrawRandomPlant(2423));
	DemoArray.push_back(new DrawRandomPlant(674364));
	DemoArray.push_back(new DrawRandomPlant(34554));
	DemoArray.push_back(new DrawCordateLeaf);
	DemoArray.push_back(new DrawHilbertCurve);
	DemoArray.push_back(new DrawTreeSkeleton);
	DemoArray.push_back(new DrawTreeHalfDone);
	DemoArray.push_back(new DrawTreeFinished(TreeResX,TreeResY,TextureId));
	DemoArray.push_back(new DrawTreeFinished(TreeResX,TreeResY,BarkTexId));
	DemoArray.push_back(new DrawStochasticTreeFinished(0,TreeResX,TreeResY,BarkTexId));
	DemoArray.push_back(new DrawStochasticTreeFinished(120,TreeResX,TreeResY,BarkTexId));
	DemoArray.push_back(new DrawStochasticTreeFinished(340,TreeResX,TreeResY,BarkTexId));
	DemoArray.push_back(new DrawStochasticTreeFinished(6340,TreeResX,TreeResY,BarkTexId));
	DemoArray.push_back(new DrawStochasticTreeFinished(86645,TreeResX,TreeResY,BarkTexId));
	DemoArray.push_back(new DrawStochasticTreeFinished(2332,TreeResX,TreeResY,BarkTexId));
	DemoArray.push_back(new DrawStochasticTreeFinished(3246340,TreeResX,TreeResY,BarkTexId));
	DemoArray.push_back(new DrawStochasticTreeFinished(23386645,TreeResX,TreeResY,BarkTexId));
	DemoArray.push_back(new DrawStochasticTreeFinished(1122332,TreeResX,TreeResY,BarkTexId));
	//
	//GenerateLowPolyMesh::Anyad--;
	//QuickhullNumSteps--;
}

bool TartalekDemo = false;

void Draw3D()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(90,1.0,1.0,-200.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    glTranslatef(X,Y,Z);

	glRotatef(CameraAngle,0.0,1.0,0.0);
    glRotatef(-90.0,1.0,0.0,0.0);

	//DrawSkeleton HilbertDraw;
	//HilbertDraw.Draw(HilbertCurveSkeleton);

	//GenerateHypergraph DrawSkel;
	//DrawSkel.Draw(TreeSkeleton,Hypergraph);

	if(TartalekDemo)
	{
		glEnable(GL_DEPTH_TEST);
		//glEnable(GL_CULL_FACE);
		//glCullFace(GL_BACK);
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

		DrawHypergraph(Hypergraph);
	}
	else
	{
		unsigned int Res_X = 10;
		unsigned int Res_Y = 10;
		LowPolyMeshGenerator MeshCreator(Res_X,Res_Y);

		glEnable(GL_DEPTH_TEST);
		//glEnable(GL_CULL_FACE);
		//glCullFace(GL_BACK);
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

		//DrawHypergraph(Hypergraph);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,BarkTexId);

		//MeshCreator.Generate(Hypergraph);
		/*
		glBegin(GL_QUADS);

		glVertex3f( 10.0, 10.0,-30.0);
		glTexCoord2f(0.0,0.0);
		glVertex3f( 10.0,-10.0,-30.0);
		glTexCoord2f(0.0,1.0);
		glVertex3f(-10.0,-10.0,-30.0);
		glTexCoord2f(1.0,1.0);
		glVertex3f(-10.0, 10.0,-30.0);
		glTexCoord2f(1.0,0.0);

		glEnd();
		*/
		glDisable(GL_TEXTURE_2D);
	}

	//delete Hypergraph;
}

void onDisplay()
{
    glClearColor(0.7f, 0.7f, 0.7f, 1.0f);		// torlesi szin beallitasa
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // kepernyo torles

	glViewport(0, 0, screenWidth, screenHeight);

	if(DemoId < DemoArray.size())
	{
		DemoArray[DemoId]->Draw();
	}
	else
	{
		Draw3D();
	}

    glutSwapBuffers();     				// Buffercsere: rajzolas vege

}

void onKeyboard(unsigned char key, int x, int y)
{
	if(tolower(key) == '1')
	{
		DemoId--;
	}
	if(tolower(key) == '2')
	{
		DemoId++;
	}

	if(tolower(key) == '3')
	{
		DRAW_CSO = !DRAW_CSO;
	}
	if(tolower(key) == '4')
	{
		DRAW_JUNCTION = !DRAW_JUNCTION;
	}
	if(tolower(key) == '5')
	{
		DRAW_SPLINE = !DRAW_SPLINE;
	}

	if(tolower(key) == 'q')
	{
		CameraAngle -= 10.0;
	}
	if(tolower(key) == 'e')
	{
		CameraAngle += 10.0;
	}

	if(tolower(key) == 'w')
	{
		Z -= 5.0;
	}
	if(tolower(key) == 's')
	{
		Z += 5.0;
	}

	if(tolower(key) == 'a')
	{
		X -= 5.0;
	}
	if(tolower(key) == 'd')
	{
		X += 5.0;
	}

	if(tolower(key) == 'f')
	{
		Y -= 5.0;
	}
	if(tolower(key) == 'r')
	{
		Y += 5.0;
	}
	/*
	if(tolower(key) == 't')
	{
		GenerateLowPolyMesh::Anyad++;
	}
	if(tolower(key) == 'g')
	{
		GenerateLowPolyMesh::Anyad--;
	}
	*/
	if(tolower(key) == 't')
	{
		DrawBranch = !DrawBranch;
	}
	/*
	if(tolower(key) == 'u')
	{
		QuickhullNumSteps++;
	}
	if(tolower(key) == 'j')
	{
		QuickhullNumSteps--;
	}
	*/
	/*
	if(tolower(key) == 'z')
	{
		GenerateLowPolyMesh::Apad = !GenerateLowPolyMesh::Apad;
	}

	if(tolower(key) == 'h')
	{
		GenerateLowPolyMesh::Apucid = !GenerateLowPolyMesh::Apucid;
	}

	if(tolower(key) == 'o')
	{
		GenerateLowPolyMesh::BlackJunction = !GenerateLowPolyMesh::BlackJunction;
	}
	*/
	if(tolower(key) == 'l')
	{
		TartalekDemo = !TartalekDemo;
	}
}

void onKeyboardUp(unsigned char key, int x, int y)
{

}

void onMouse(int button, int state, int x, int y)
{

}

void onMouseMotion(int x, int y)
{

}

void onIdle( )
{
	glutPostRedisplay( );
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv); 
    glutInitWindowSize(screenWidth, screenHeight);
    glutInitWindowPosition(100, 100);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Demo");

    onInitialization();

    glutDisplayFunc(onDisplay);
    glutMouseFunc(onMouse);
    glutIdleFunc(onIdle);
    glutKeyboardFunc(onKeyboard);
    glutKeyboardUpFunc(onKeyboardUp);
    glutMotionFunc(onMouseMotion);

    glutMainLoop();

    return 0;
}

