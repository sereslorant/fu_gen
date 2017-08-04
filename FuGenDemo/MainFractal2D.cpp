
#include "SDL2DemoFramework.h"

#include "Demo/DemoCollection.h"

#include "Demo/Demo2D/QuadraticKockCurve.h"
#include "Demo/Demo2D/DragonCurve.h"
#include "Demo/Demo2D/CordateLeaf.h"

#include "Camera2D.h"

int main(int argc,char *argv[])
{
	SDL2DemoFramework DemoFramework(800,600,new DemoCollection({new QuadraticKochCurve,new DragonCurve,new CordateLeaf}),new Camera2D);
	
	DemoFramework.Loop();
	
	return 0;
}
