#ifndef GENERALIZED_CYLINDER_H
#define GENERALIZED_CYLINDER_H

#include "ICurve.h"

class GeneralizedCylinder
{
public:
	bool TEST_FrenetFrame = false;

	ICurve &Spine;
	vec4 Up;
	float Radius;

	vec4 GetPoint(float spine_param,float angle) const
	{
		vec4 i,j,k;

		if(TEST_FrenetFrame)
		{
			ICurve::GetFrenetFrame(Spine,spine_param,&i,&j,&k,true);
		}
		else
		{
			ICurve::GetExplicitUpFrame(Spine,Up,spine_param,1.0/30.0,&i,&j,&k,true);
		}

		vec4 DiskPoint = std::cos(angle)*i + std::sin(angle)*k;

		return Spine.GetPoint(spine_param) + Radius * DiskPoint;
	}

	GeneralizedCylinder(ICurve &spine,vec4 up,float radius)
		:Spine(spine),Up(up),Radius(radius)
	{}

	~GeneralizedCylinder()
	{}
};

#endif // GENERALIZED_CYLINDER_H
