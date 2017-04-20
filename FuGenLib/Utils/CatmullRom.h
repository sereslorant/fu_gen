#ifndef CATMULL_ROM_H
#define CATMULL_ROM_H

#include "ICurve.h"

#include <cmath>

class IScalarField
{
public:
	virtual float GetValue(const vec4 &point) const = 0;

	IScalarField(){}
	virtual ~IScalarField(){}
};

class Sphere : public IScalarField
{
public:
	vec4 Center;
	float Radius;

	virtual float GetValue(const vec4 &point) const override
	{
		return dot((point - Center),(point - Center)) - Radius*Radius;
	}

	Sphere(vec4 center,float radius)
		:Center(center),Radius(radius)
	{}
	virtual ~Sphere(){}
};

vec4 Hermite(const vec4 &p0,const vec4 &p1,const vec4 &v0,const vec4 &v1,float t0,float t1,float t);
vec4 HermiteDerivative(const vec4 &p0,const vec4 &p1,const vec4 &v0,const vec4 &v1,float t0,float t1,float t);
vec4 HermiteSecondDerivative(const vec4 &p0,const vec4 &p1,const vec4 &v0,const vec4 &v1,float t0,float t1,float t);

vec4 AverageVelocity(const vec4 &p0,const vec4 &p1,float t0,float t1);

#include <vector>

//#include <iostream>

class CatmullRom : public ICurve
{
public:
	std::vector<vec4> cps;	// control points
	std::vector<vec4> Velocity; //A kontroll pontok sebességvektora
	std::vector<float>  ts;	// parameter (knot) values

	vec4 InitVelocity;
	vec4 EndVelocity;

	CatmullRom *Clone()
	{
		CatmullRom *NewSpline = new CatmullRom(InitVelocity,EndVelocity);

		NewSpline->cps.resize(cps.size());
		NewSpline->Velocity.resize(Velocity.size());
		NewSpline->ts.resize(ts.size());

		for(unsigned int i=0;i < cps.size();i++)
		{
			NewSpline->cps[i] = cps[i];
			NewSpline->Velocity[i] = Velocity[i];
			NewSpline->ts[i] = ts[i];
		}

		NewSpline->SetInitVelocity(InitVelocity);
		//NewSpline->SetEndVelocity(EndVelocity);

		return NewSpline;
	}

	void SetInitVelocity(const vec4 &init_velocity)
	{
		InitVelocity = init_velocity;
		if(Velocity.size() > 0)
		{
			Velocity[0] = InitVelocity;
			//JAVÍTANI KELL!
		}
	}

	void SetEndVelocity(const vec4 &end_velocity)
	{
		EndVelocity = end_velocity;
		if(Velocity.size() > 0)
		{
			Velocity[Velocity.size()-1] = EndVelocity;
			//JAVÍTANI KELL!
		}
	}

	void AddControlPoint(const vec4 &cp,float t)
	{
		cps.push_back(cp);
		ts.push_back(t);
		Velocity.push_back(EndVelocity);

		if(cps.size() == 1)
		{
			Velocity[0] = InitVelocity;
		}
		else if(cps.size() > 2)
		{
			const vec4 &Pprev2 = cps[cps.size() - 3]; float tprev2 = ts[ts.size() - 3];
			const vec4 &Pprev1 = cps[cps.size() - 2]; float tprev1 = ts[ts.size() - 2];
			const vec4 &Pfin   = cps[cps.size() - 1]; float tfin   = ts[ts.size() - 1];

			Velocity[Velocity.size()-2] = (AverageVelocity(Pprev2,Pprev1,tprev2,tprev1) + AverageVelocity(Pprev1,Pfin,tprev1,tfin)) / 2.0f;
		}
	}
	
	virtual unsigned int GetNumControlPoints() const override
	{
		return cps.size();
	}
	
	virtual const vec4 &GetCtrlPosition(unsigned int id) const override
	{
		return cps[id];
	}

	virtual const vec4 &GetCtrlDerivative(unsigned int id) const override
	{
		return Velocity[id];
	}

	virtual float GetCtrlParameter(unsigned int id) const override
	{
		return ts[id];
	}

	virtual vec4 GetPoint(float t) const override
	{
		for(unsigned int i = 0; i < cps.size() - 1; i++)
		{
			if (ts[i] <= t && t <= ts[i+1])
			{
				return Hermite(cps[i],cps[i+1],Velocity[i],Velocity[i+1],ts[i],ts[i+1],t);
			}
		}

		return vec4(0.0,0.0,0.0);
	}

	virtual vec4 GetDerivative(float t) const override
	{
		for(unsigned int i = 0; i < cps.size() - 1; i++)
		{
			if (ts[i] <= t && t <= ts[i+1])
			{
				return HermiteDerivative(cps[i],cps[i+1],Velocity[i],Velocity[i+1],ts[i],ts[i+1],t);
			}
		}

		return vec4(0.0,0.0,0.0);
	}

	virtual vec4 GetSecondDerivative(float t) const override
	{
		for(unsigned int i = 0; i < cps.size() - 1; i++)
		{
			if (ts[i] <= t && t <= ts[i+1])
			{
				return HermiteSecondDerivative(cps[i],cps[i+1],Velocity[i],Velocity[i+1],ts[i],ts[i+1],t);
			}
		}

		return vec4(0.0,0.0,0.0);
	}

	virtual vec4 GetSegment(float t,float dt) const override
	{
		return GetPoint(t+dt) - GetPoint(t);
	}

	CatmullRom(const vec4 &init_velocity,const vec4 &end_velocity)
		:InitVelocity(init_velocity),EndVelocity(end_velocity)
	{}

	virtual ~CatmullRom() override
	{}
};

#include <list>

bool BisectionMethod(const ICurve &curve,float t_begin,float t_end,float dt_min,const IScalarField &scalar_field,std::list<float> &roots);

#endif // CATMULL_ROM_H
