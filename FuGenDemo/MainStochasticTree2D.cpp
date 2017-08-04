
#include "SDL2DemoFramework.h"

#include "Demo/DemoCollection.h"

#include "Demo/Demo2D/StochasticTree2D.h"

#include "Camera2D.h"

int main(int argc,char *argv[])
{
	SDL2DemoFramework DemoFramework(800,600,
									new DemoCollection({
										new StochasticTree2D(234),
										new StochasticTree2D(6332),
										new StochasticTree2D(234236),
										new StochasticTree2D(2423),
										new StochasticTree2D(674364),
										new StochasticTree2D(34554)
									}),
									new Camera2D);
	
	DemoFramework.Loop();
	
	return 0;
}
