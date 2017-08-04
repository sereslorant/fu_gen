#ifndef CAMERA2D_H
#define CAMERA2D_H

#include "ICamera.h"

#include "DemoUtils/GLInclude.h"

class Camera2D : public ICamera
{
private:
	float X = 20.0;
	float Y = -20.0;
	
public:
	
	virtual void Move(float dx,float dy,float dz) override
	{
		X += dx;
		Y += dy;
	}
	
	virtual void Rotate(float dangle) override
	{
		//Üres
	}
	
	virtual void ApplyProjectionTransform() override
	{
		gluOrtho2D(-256.0,256.0,-128.0,+128.0);
	}
	
	virtual void ApplyViewTransform() override
	{
		glTranslatef(X,Y,0.0);
	}
	
	Camera2D()
	{}
	
	virtual ~Camera2D() override
	{}
};

#endif // CAMERA2D_H
