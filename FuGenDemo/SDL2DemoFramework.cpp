
#include "SDL2DemoFramework.h"

#include "DemoUtils/DrawModel.h"

void SDL2DemoFramework::Input()
{
	SDL_Event Event;
	while(SDL_PollEvent(&Event))
	{
		if(Event.type == SDL_QUIT)
		{
			Running = false;
		}
		
		if(Event.type == SDL_KEYDOWN)
		{
			if(Event.key.keysym.sym == SDLK_w)
			{CameraForward = true;}
			if(Event.key.keysym.sym == SDLK_s)
			{CameraBack = true;}
			if(Event.key.keysym.sym == SDLK_a)
			{CameraLeft = true;}
			if(Event.key.keysym.sym == SDLK_d)
			{CameraRight = true;}
			if(Event.key.keysym.sym == SDLK_r)
			{CameraUp = true;}
			if(Event.key.keysym.sym == SDLK_f)
			{CameraDown = true;}
			
			if(Event.key.keysym.sym == SDLK_q)
			{CameraRotLeft = true;}
			if(Event.key.keysym.sym == SDLK_e)
			{CameraRotRight = true;}
			
			if(Event.key.keysym.sym == SDLK_3)
			{SwitchDrawCso = true;}
			if(Event.key.keysym.sym == SDLK_4)
			{SwitchDrawJunction = true;}
			if(Event.key.keysym.sym == SDLK_5)
			{SwitchDrawSpline = true;}
			
			if(Event.key.keysym.sym == SDLK_1)
			{SetPreviousDemo = true;}
			if(Event.key.keysym.sym == SDLK_2)
			{SetNextDemo = true;}
			
			if(Event.key.keysym.sym == SDLK_9)
			{ChangeState = true;}
		}
		
		if(Event.type == SDL_KEYUP)
		{
			if(Event.key.keysym.sym == SDLK_w)
			{CameraForward = false;}
			if(Event.key.keysym.sym == SDLK_s)
			{CameraBack = false;}
			if(Event.key.keysym.sym == SDLK_a)
			{CameraLeft = false;}
			if(Event.key.keysym.sym == SDLK_d)
			{CameraRight = false;}
			if(Event.key.keysym.sym == SDLK_r)
			{CameraUp = false;}
			if(Event.key.keysym.sym == SDLK_f)
			{CameraDown = false;}
			
			if(Event.key.keysym.sym == SDLK_q)
			{CameraRotLeft = false;}
			if(Event.key.keysym.sym == SDLK_e)
			{CameraRotRight = false;}
			
			if(Event.key.keysym.sym == SDLK_3)
			{SwitchDrawCso = false;}
			if(Event.key.keysym.sym == SDLK_4)
			{SwitchDrawJunction = false;}
			if(Event.key.keysym.sym == SDLK_5)
			{SwitchDrawSpline = false;}
			
			if(Event.key.keysym.sym == SDLK_1)
			{SetPreviousDemo = false;}
			if(Event.key.keysym.sym == SDLK_2)
			{SetNextDemo = false;}
			
			if(Event.key.keysym.sym == SDLK_9)
			{ChangeState = false;}
		}
	}
}

void SDL2DemoFramework::Logic()
{
	if(CameraForward)
		{Camera->Move(0.0,0.0,-5.0);}
	if(CameraBack)
		{Camera->Move(0.0,0.0, 5.0);}
	if(CameraLeft)
		{Camera->Move(-5.0,0.0,0.0);}
	if(CameraRight)
		{Camera->Move( 5.0,0.0,0.0);}
	if(CameraUp)
		{Camera->Move(0.0,-5.0,0.0);}
	if(CameraDown)
		{Camera->Move(0.0, 5.0,0.0);}
	
	if(CameraRotLeft)
		{Camera->Rotate(-10.0);}
	if(CameraRotRight)
		{Camera->Rotate( 10.0);}
	
	if(SwitchDrawCso)
	{
		DRAW_CSO = !DRAW_CSO;
		SDL_Delay(100);
	}
	if(SwitchDrawJunction)
	{
		DRAW_JUNCTION = !DRAW_JUNCTION;
		SDL_Delay(100);
	}
	if(SwitchDrawSpline)
	{
		DRAW_SPLINE = !DRAW_SPLINE;
		SDL_Delay(100);
	}
	
	if(SetPreviousDemo)
	{
		Demo->SetPreviousDemo();
		SDL_Delay(100);
	}
	
	if(SetNextDemo)
	{
		Demo->SetNextDemo();
		SDL_Delay(100);
	}
	
	if(ChangeState)
	{
		Demo->ChangeState();
		SDL_Delay(100);
	}
}

void SDL2DemoFramework::Rendering()
{
	glClearColor(0.975f, 0.975f, 0.975f, 1.0f);		// torlesi szin beallitasa
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // kepernyo torles

	glViewport(0, 0, ScreenWidth, ScreenHeight);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	Camera->ApplyProjectionTransform();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	Camera->ApplyViewTransform();
	
	Demo->Draw();
	
	SDL_GL_SwapWindow(Window);
}

void SDL2DemoFramework::Loop()
{
	while(Running)
	{
		Input();
		Logic();
		Rendering();
	}
}

SDL2DemoFramework::SDL2DemoFramework(int width,int height,IDemo *demo,ICamera *camera)
	:ScreenWidth(width),ScreenHeight(height),Demo(demo),Camera(camera)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	
	Window = SDL_CreateWindow("FuGenDemo",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,SDL_WINDOW_OPENGL);
	if(Window == nullptr)
	{
		return;
	}
	
	GLContext = SDL_GL_CreateContext(Window);
	if(GLContext == nullptr)
	{
		return;
	}
	
	SDL_ShowWindow(Window);
}

SDL2DemoFramework::~SDL2DemoFramework()
{
	delete Demo;
	delete Camera;
	
	SDL_GL_DeleteContext(GLContext);
	SDL_DestroyWindow(Window);
	
	SDL_Quit();
}
