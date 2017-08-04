#ifndef CAMERA3D_H
#define CAMERA3D_H

#include "ICamera.h"

#include "DemoUtils/GLInclude.h"

class Camera3D : public ICamera
{
private:
	float X = 20.0;
	float Y = -20.0;
	float Z = 20.0;

	float CameraAngle = 0.0;
	
public:
	
	virtual void Move(float dx,float dy,float dz) override
	{
		X += dx;
		Y += dy;
		Z += dz;
	}
	
	virtual void Rotate(float dangle) override
	{
		CameraAngle += dangle;
	}
	
	virtual void ApplyProjectionTransform() override
	{
		gluPerspective(90,1.0,1.0,-200.0);
	}
	
	virtual void ApplyViewTransform() override
	{
		glTranslatef(X,Y,Z);
		
		glRotatef(CameraAngle,0.0,1.0,0.0);
		glRotatef(-90.0,1.0,0.0,0.0);
	}
	
	Camera3D()
	{}
	
	virtual ~Camera3D() override
	{}
};

#endif // CAMERA3D_H
