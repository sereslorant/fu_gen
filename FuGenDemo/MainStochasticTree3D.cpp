
#include "SDL2DemoFramework.h"

#include <DemoUtils/DemoTexture.h>

#include <Demo/DemoCollection.h>

#include <Demo/Demo3D/StochasticTree3D.h>

#include "Camera3D.h"

int main(int argc,char *argv[])
{
	unsigned int TreeResX = 6;
	unsigned int TreeResY = 6;
	
	SDL2DemoFramework DemoFramework(800,600,nullptr,new Camera3D);
	
	GLuint BarkTexId = LoadBarkTexture();
	
	DemoFramework.SetDemo(
		new DemoCollection({
			new StochasticTree3D(0,TreeResX,TreeResY,BarkTexId),
			new StochasticTree3D(120,TreeResX,TreeResY,BarkTexId),
			new StochasticTree3D(340,TreeResX,TreeResY,BarkTexId),
			new StochasticTree3D(6340,TreeResX,TreeResY,BarkTexId),
			new StochasticTree3D(86645,TreeResX,TreeResY,BarkTexId),
			new StochasticTree3D(2332,TreeResX,TreeResY,BarkTexId),
			new StochasticTree3D(3246340,TreeResX,TreeResY,BarkTexId),
			new StochasticTree3D(23386645,TreeResX,TreeResY,BarkTexId),
			new StochasticTree3D(1122332,TreeResX,TreeResY,BarkTexId)
		})
	);
	
	DemoFramework.Loop();
	
	glDeleteTextures(1,&BarkTexId);
	
	return 0;
}
