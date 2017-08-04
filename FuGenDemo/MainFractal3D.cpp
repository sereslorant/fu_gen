
#include "SDL2DemoFramework.h"

#include "Demo/Demo3D/HilbertCurve.h"

#include "Camera3D.h"

int main(int argc,char *argv[])
{
	SDL2DemoFramework DemoFramework(800,600,new HilbertCurve,new Camera3D);
	
	DemoFramework.Loop();
	
	return 0;
}

