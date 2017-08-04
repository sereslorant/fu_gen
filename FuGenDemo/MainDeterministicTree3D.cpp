
#include "SDL2DemoFramework.h"

#include <DemoUtils/DemoTexture.h>

#include <Demo/DemoCollection.h>

#include <Demo/Demo3D/DeterministicTree.h>

#include "Camera3D.h"

int main(int argc,char *argv[])
{
	unsigned int TreeResX = 6;
	unsigned int TreeResY = 6;
	
	SDL2DemoFramework DemoFramework(800,600,nullptr,new Camera3D);
	
	GLuint DummyTexture = CreateTexture();
	GLuint BarkTexId = LoadBarkTexture();
	
	DemoFramework.SetDemo(
		new DemoCollection({
			new DeterministicTree(TreeResX,TreeResY,DummyTexture),
			new DeterministicTree(TreeResX,TreeResY,BarkTexId)
		})
	);
	
	DemoFramework.Loop();
	
	glDeleteTextures(1,&DummyTexture);
	glDeleteTextures(1,&BarkTexId);
	
	return 0;
}
