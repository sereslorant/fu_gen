
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

#include "Demo/IDemo.h"

const int screenWidth = 1024;
const int screenHeight = 512;


#include "DemoUtils/DemoTexture.h"

GLuint TextureId = 0;
GLuint BarkTexId = 0;

#include "DemoUtils/DrawSkeleton.h"
#include "DemoUtils/DrawModel.h"
#include "Demo/Demo2D/QuadraticKockCurve.h"
#include "Demo/Demo2D/DragonCurve.h"
#include "Demo/Demo2D/StochasticTree2D.h"
#include "Demo/Demo2D/CordateLeaf.h"
#include "Demo/Demo3D/HilbertCurve.h"
#include "Demo/Demo3D/DeterministicTree.h"
#include "Demo/Demo3D/StochasticTree3D.h"

#include "Camera2D.h"
#include "Camera3D.h"

Camera2D camera2D;
Camera3D camera3D;

ICamera *Camera;

unsigned int DemoId = 0;
std::vector<IDemo *> DemoArray;

// Inicializacio, a program futasanak kezdeten, az OpenGL kontextus letrehozasa utan hivodik meg (ld. main() fv.)
void onInitialization()
{
	BarkTexId = LoadBarkTexture();
	TextureId = CreateTexture();
	
	unsigned int TreeResX = 6;
	unsigned int TreeResY = 6;
	
	DemoArray.push_back(new QuadraticKochCurve);
	DemoArray.push_back(new DragonCurve);
	DemoArray.push_back(new StochasticTree2D(234));
	DemoArray.push_back(new StochasticTree2D(6332));
	DemoArray.push_back(new StochasticTree2D(234236));
	DemoArray.push_back(new StochasticTree2D(2423));
	DemoArray.push_back(new StochasticTree2D(674364));
	DemoArray.push_back(new StochasticTree2D(34554));
	DemoArray.push_back(new CordateLeaf);
	DemoArray.push_back(new HilbertCurve);
	DemoArray.push_back(new DeterministicTree(TreeResX,TreeResY,TextureId));
	DemoArray.push_back(new DeterministicTree(TreeResX,TreeResY,BarkTexId));
	DemoArray.push_back(new StochasticTree3D(0,TreeResX,TreeResY,BarkTexId));
	DemoArray.push_back(new StochasticTree3D(120,TreeResX,TreeResY,BarkTexId));
	DemoArray.push_back(new StochasticTree3D(340,TreeResX,TreeResY,BarkTexId));
	DemoArray.push_back(new StochasticTree3D(6340,TreeResX,TreeResY,BarkTexId));
	DemoArray.push_back(new StochasticTree3D(86645,TreeResX,TreeResY,BarkTexId));
	DemoArray.push_back(new StochasticTree3D(2332,TreeResX,TreeResY,BarkTexId));
	DemoArray.push_back(new StochasticTree3D(3246340,TreeResX,TreeResY,BarkTexId));
	DemoArray.push_back(new StochasticTree3D(23386645,TreeResX,TreeResY,BarkTexId));
	DemoArray.push_back(new StochasticTree3D(1122332,TreeResX,TreeResY,BarkTexId));
}

void onDisplay()
{
    glClearColor(0.975f, 0.975f, 0.975f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glViewport(0, 0, screenWidth, screenHeight);
	
	if(DemoId < 9)
	{
		Camera = &camera2D;
	}
	else
	{
		Camera = &camera3D;
	}
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	Camera->ApplyProjectionTransform();
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	Camera->ApplyViewTransform();
	
	DemoArray[DemoId % DemoArray.size()]->Draw();
	
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
	
	if(DemoId < 9)
	{
		Camera = &camera2D;
	}
	else
	{
		Camera = &camera3D;
	}

	if(tolower(key) == 'q')
	{
		Camera->Rotate(-10.0);
	}
	if(tolower(key) == 'e')
	{
		Camera->Rotate( 10.0);
	}

	if(tolower(key) == 'w')
	{
		Camera->Move(0.0,0.0,-5.0);
	}
	if(tolower(key) == 's')
	{
		Camera->Move(0.0,0.0, 5.0);
	}

	if(tolower(key) == 'a')
	{
		Camera->Move(-5.0,0.0,0.0);
	}
	if(tolower(key) == 'd')
	{
		Camera->Move( 5.0,0.0,0.0);
	}

	if(tolower(key) == 'f')
	{
		Camera->Move(0.0,-5.0,0.0);
	}
	if(tolower(key) == 'r')
	{
		Camera->Move(0.0, 5.0,0.0);
	}
	
	if(tolower(key) == 't')
	{
		DrawBranch = !DrawBranch;
	}
	if(tolower(key) == '9')
	{
		for(IDemo *Demo : DemoArray)
		{
			Demo->ChangeState();
		}
	}
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

    glutKeyboardFunc(onKeyboard);
    glutIdleFunc(onIdle);
    glutDisplayFunc(onDisplay);

    glutMainLoop();

    return 0;
}

