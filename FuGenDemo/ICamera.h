#ifndef ICAMERA_H
#define ICAMERA_H

class ICamera
{
public:
	virtual void Move(float dx,float dy,float dz) = 0;
	virtual void Rotate(float dangle) = 0;
	
	virtual void ApplyProjectionTransform() = 0;
	virtual void ApplyViewTransform() = 0;
	
	ICamera()
	{}
	virtual ~ICamera()
	{}
};

#endif // ICAMERA_H
