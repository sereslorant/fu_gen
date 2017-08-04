#ifndef SDL2_DEMO_FRAMEWORK_H
#define SDL2_DEMO_FRAMEWORK_H

#include <SDL2/SDL.h>

#include "DemoUtils/GLInclude.h"

#include "Demo/IDemo.h"
#include "ICamera.h"

class SDL2DemoFramework
{
private:
	SDL_Window *Window;
    SDL_GLContext GLContext;
	
	unsigned int ScreenWidth = 0;
	unsigned int ScreenHeight = 0;
	
	bool Running = true;
	
	bool CameraForward = false;
	bool CameraBack = false;
	bool CameraLeft = false;
	bool CameraRight = false;
	bool CameraUp = false;
	bool CameraDown = false;
	bool CameraRotLeft = false;
	bool CameraRotRight = false;
	
	bool SetNextDemo = false;
	bool SetPreviousDemo = false;
	
	bool ChangeState = false;
	
	bool SwitchDrawCso = false;
	bool SwitchDrawJunction = false;
	bool SwitchDrawSpline = false;
	
	IDemo *Demo = nullptr;
	ICamera *Camera = nullptr;
	
	void Input();
	
	void Logic();
	
	void Rendering();
	
public:
	
	void SetDemo(IDemo *demo)
	{
		Demo = demo;
	}
	
	void Loop();
	
	SDL2DemoFramework(int width,int height,IDemo *demo,ICamera *camera);
	
	~SDL2DemoFramework();
};

#endif // SDL2_DEMO_FRAMEWORK_H
